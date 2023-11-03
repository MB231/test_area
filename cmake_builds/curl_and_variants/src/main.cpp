#include <iostream>
#include <cstdint>
#include <string>
#include <string_view>
#include <variant>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <algorithm>

using JSON = nlohmann::json;
// helper constant for the visitor #3
//template<class>
//inline constexpr bool always_false_v = false;
 
// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct testresp1 {
    testresp1(std::string retVal) : retVal(retVal){}
    std::string s = "test resp 1";
    std::string retVal;
};
struct testresp2 {
    testresp2(std::string retVal) : retVal(retVal){}
    std::string s = "test resp 2";
    std::string retVal;
};
using ReplyMsg = std::variant<testresp1, testresp2>;

size_t StringCallback(char *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t VectorCallback(char *contents, size_t size, size_t nmemb, void *userp) {
    std::vector<uint8_t>* vec = static_cast<std::vector<uint8_t>*>(userp);
    for (int i = 0; i < size * nmemb; i++) {
        std::cout << contents[i] << std::endl;
        vec->emplace_back(contents[i]);
    }
    std::cout << "vector size: " << vec->size() << "  copied size: " << size*nmemb << std::endl;
    return size * nmemb;
}
void curlcmd(std::string url, std::vector<ReplyMsg> &reply) {
    curl_global_init(CURL_GLOBAL_ALL);

    CURL* easyhandle = curl_easy_init();
    std::string readBuffer;
    // char writeBuffer[1024]; DOESNT WORK, HAS ODD VALUES IN STRING
    uint8_t writeBuffer[1024];
    std::vector<uint8_t> buffer;
    buffer.reserve(1024);

    curl_easy_setopt(easyhandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easyhandle, CURLOPT_CUSTOMREQUEST, "GET"); //set http method

    //curl_easy_setopt(easyhandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(easyhandle, CURLOPT_PROXYPORT, 8000L);

    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, StringCallback);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

    // Vector option
    //curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &buffer); // requires different callback
    //curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, VectorCallback);



    std::cout << "sending CURL \n";
    CURLcode retVal = curl_easy_perform(easyhandle);
    //clean up
    curl_easy_cleanup(easyhandle);
    if(retVal == CURLE_OK) {
        // tried to use regular buffer here and simply right to a std ::string
        //readBuffer = writeBuffer;
        std::cout << "CURL Success \n";
        // tried to add backslashes to starting double quotes in case those needed escaping as well
        //readBuffer.insert(readBuffer.begin(), '\\');
        //readBuffer.insert(readBuffer.end()-1, '\\');

        // This worked by removing all back slashes AND the starting and ending double quotes. Brackets removed since I
        // happened to wrap all of my json objects in an array.
        readBuffer.erase(readBuffer.end()-1); readBuffer.erase(readBuffer.begin());
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\\'), readBuffer.end());
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '['), readBuffer.end());
        readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), ']'), readBuffer.end());

        // ouput c strings from string in case to compare
        std::cout <<"\n\n"<< readBuffer.c_str()  <<"\n\n retVal: "<< retVal<< std::endl;
        std::cout <<"\n\n"<< readBuffer <<"\n\n";

        std::cout <<"\n\n"<< buffer.size() <<"\n\n retVal: "<< retVal<< std::endl;

        // check if it's a parsable before attempting so no exception
        // if (JSON::accept(readBuffer.c_str())) { // c string also works
        // Same issue with std::vector<uint8_t>
        //if (JSON::accept(buffer)) {
        //    JSON j = JSON::parse(buffer);

        if (JSON::accept(readBuffer)) {
            JSON j = JSON::parse(readBuffer);
            std::cout << "CURL GOT THIS JSON: " << j << "\n";
            using namespace std::string_view_literals;
            // call find
            auto it_two = j.find("temperature"sv);
            auto it_three = j.find("variant"sv);

            // print values
            std::cout << std::boolalpha;
            std::cout << "\"temperature\" was found: " << (it_two != j.end()) << '\n';
            std::cout << "\"variant\" was found: " << (it_three != j.end()) << '\n';
            for (auto& item :j.items()) {
                std::cout << "\n\nKEY: " << item.key();
                std::cout << "  VALUE: " << item.value() << "\n\n";
            }
        } else {
            std::cout << "\n\ncurl return is not JSON parseable\n\n";
        }
    } else{ 
        std::cout << "Failed. CURLcode: " << retVal << std::endl;
    }
    reply.emplace_back(testresp1{readBuffer});
}

int main(int argc, char * argv[])
{
    std::string url1 = "http://10.39.200.86:8000/version";
    std::string url2 = "http://10.39.200.86:8000/temp";
    std::string url3 = "http://10.39.200.86:8000/card_info";
    std::vector<ReplyMsg> reply;
    std::cout << "\n\nvector size before: " << reply.size();
    //std::cout << "\n\ngetting version";
    //curlcmd(url1, reply);
    std::cout << "\n\ngetting temp \n";
    curlcmd(url2, reply);
    std::cout << "\n\ngetting card_info \n";
    curlcmd(url3, reply);
    std::cout << "\n\nvector size after: " << reply.size();
    for(auto&& i : reply) {
        std::visit(overloaded{
            [](auto& arg) { std::cout << "default hit " << arg.s << " retVal= " << arg.retVal; },
            [](testresp1& arg) { std::cout << "\n\ntestresp1 got output" << arg.retVal << "\n\n"; },
            [](testresp2& arg) { std::cout << "\n\ntestresp2 got output" << arg.retVal << "\n\n"; },
        }, i);
    }
}
