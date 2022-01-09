#include <iostream>
#include <string>

int main() {
    using NndbPair = std::pair<std::string, std::string>;
    using Response = std::pair<int, NndbPair>;

    std::string field = std::string("field");
    std::string data = std::string("data");
    Response test = Response(1, std::make_pair(field, data));
    std::cout << test.first << std::endl;
    std::cout << test.second.first << std::endl;
    std::cout << test.second.second << std::endl;
}

