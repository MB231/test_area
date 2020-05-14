#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void getNumberFromString(string s) {
   stringstream str_strm;
   str_strm << s; //convert the string s into stringstream
   string temp_str;
   int temp_int;
   while(!str_strm.eof()) {
      str_strm >> temp_str; //take words into temp_str one by one
      if(stringstream(temp_str) >> temp_int) { //try to convert string to int
         cout << temp_int << " ";
      }
      temp_str = ""; //clear temp string
   }
}

vector<uint8_t> parseCommas(string s) {
    //vector<string> result; use for keeping strings
    vector<uint8_t> result;
    stringstream ss;
    ss << s;

    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        std::cout << substr << endl;
        //result.push_back( substr ); for string vector
        result.push_back( std::stoi(substr) );
    }
    cout << "size to be returned: " << result.size() <<endl;
    return result;
}
int main()
{
    vector<int> v;
    v.push_back(12);
    v.push_back(32);
    v.push_back(42);
    v.push_back(84);
    std::cout << v.size() << std::endl;

    stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<int>(ss, ","));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space

    cout << "'" << s << "'" << endl;
    //take in string and parse
    std::cout << "test of words comma sep string to uint8_t vector" << std::endl; 
    string wordSepString = "1,2,3,4 must be seperate words 23";
    getNumberFromString(wordSepString); //fails if not whitspacew delimited words. Only returns 1 not 1 2 3 4

    std::cout << "test of comma sep string to uint8_t vector" << std::endl; 
    string my_str = "[1,2,3,4]";
    std::vector<uint8_t> returnedVecor = parseCommas(my_str);
    std::cout << "returned vector of size" << returnedVecor.size() << std::endl; 
    std::vector<uint8_t> compareVector{1,2,3,4};
    if (compareVector == parseCommas(my_str)) { 
        std::cout << "can succuesfully compare a returned vector" << endl;
    }

    std::cout << "test to create a vector and to print the whole thing" << std::endl; 
    for (uint j = 0; j <= 15; j++){ 
        std::vector<uint> test{14,15,0}; //should be uint8_t but that is char and it prints as char
        test.push_back(j);
        /* Older than C++11 version
        for (std::vector<uint>::const_iterator i = test.begin(); i != test.end(); ++i){
            std::cout << *i << ' ';
        }
        */
        for (auto i = test.begin(); i != test.end(); ++i){
            std::cout << *i << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
