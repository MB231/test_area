#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    int test = 1;
    if (test){
        std::cout << "\n 1 True";
    } else {
        std::cout << "\n 1 false";
    }

    test = -1;
    if (test){
        std::cout << "\n -1 True";
    } else {
        std::cout << "\n -1 false";
    }

    test = 0;
    if (test){
        std::cout << "\n 0 True";
    } else {
        std::cout << "\n 0 false";
    }


    if (std::string::npos){
        std::cout << "\n npos true";
    } else {
        std::cout << "\n npos false";
    }

    
    if (-1 == true){
        std::cout << "\n -1 == True";
    } else {
        std::cout << "\n -1 =! True";
    }

    if (-1 == false){
        std::cout << "\n -1 == false";
    } else {
        std::cout << "\n -1 =! false";
    }

    std::cout << "\n static cast -1 to bool: " << static_cast<bool>(-1) << "\n";
    std::cout << "\n c cast -1 to bool: " << bool(-1) << "\n";

    std::cout << "\n static cast 0 to bool: " << static_cast<bool>(0) << "\n";
    std::cout << "\n c cast 0 to bool: " << bool(0) << "\n";

    std::cout << "\n static cast 1 to bool: " << static_cast<bool>(1) << "\n";
    std::cout << "\n c cast 1 to bool: " << bool(-1) << "\n";

    test = -1;
    std::cout << "\n static cast int -1 to bool: " << static_cast<bool>(test) << "\n";
    std::cout << "\n c cast int -1 to bool: " << bool(test) << "\n";

    test = 0;
    std::cout << "\n static cast int 0 to bool: " << static_cast<bool>(test) << "\n";
    std::cout << "\n c cast int 0 to bool: " << bool(test) << "\n";

    test = 1;
    std::cout << "\n static cast int 1 to bool: " << static_cast<bool>(test) << "\n";
    std::cout << "\n c cast int 1 to bool: " << bool(test) << "\n";

    // string find vs compare tests
    std::string test_string = "test1234";
    std::string full_match = test_string;
    std::string partial_match = "stuff_here_test1234_stuff_here";
    std::string no_match = "no_match";
    std::string empty = "";

    std::cout << "\n test_string ="<< test_string;
    std::cout << "\n full_match = " << full_match;
    std::cout << "\n partial_match = " << partial_match;
    std::cout << "\n no_match = " << no_match;
    std::cout << "\n empty = \"\"\n";

    std::cout << "\n begin find string tests\n";
    int res = test_string.find(full_match);
    if (res){
        std::cout << "\n find full match: true res = " << res;
    } else {
        std::cout << "\n find full match: false res = " << res;
    }

    res = test_string.find(partial_match);
    if (res){
        std::cout << "\n find partial match: true res = " << res;
    } else {
        std::cout << "\n find partial match: false res = " << res;
    }

    res = test_string.find(no_match);
    if (res){
        std::cout << "\n find no match: true res = " << res;
    } else {
        std::cout << "\n find no match: false res = " << res;
    }
    res = test_string.find(empty);
    if (res){
        std::cout << "\n find empty: true res = " << res;
    } else {
        std::cout << "\n find empty: false res = " << res;
    }

    res = full_match.find(test_string);
    if (res){
        std::cout << "\n reverse find full match: true res = " << res;
    } else {
        std::cout << "\n reverse find full match: false res = "<< res;
    }

    res = partial_match.find(test_string);
    if (res){
        std::cout << "\n reverse find partial match: true res = " << res;
    } else {
        std::cout << "\n reverse find partial match: false res = " << res;
    }

    res = no_match.find(test_string);
    if (res){
        std::cout << "\n reverse find no match: true res = " << res;
    } else {
        std::cout << "\n reverse find no match: false res = " << res;
    }

    res = empty.find(test_string);
    if (res){
        std::cout << "\n reverse find empty: true res = " << res;
    } else {
        std::cout << "\n reverse find empty: false res = " << res;
    }

    if (test_string.compare(full_match)){
        std::cout << "\n compare full match: true";
        int res = test_string.compare(full_match);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n compare full match: false";
    }

    if (test_string.compare(partial_match)){
        std::cout << "\n compare partial match: true";
        int res = test_string.compare(partial_match);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n compare partial match: false";
    }
    if (test_string.compare(no_match)){
        std::cout << "\n compare no match: true";
        int res = test_string.compare(no_match);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n compare no match: false";
    }
    if (test_string.compare(empty)){
        std::cout << "\n compare empty: true";
        int res = test_string.compare(empty);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n compare empty: false";
    }

    if (full_match.compare(test_string)){
        std::cout << "\n reverse compare full match: true";
        int res = full_match.compare(test_string);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n reverse compare full match: false";
    }

    if (partial_match.compare(test_string)){
        std::cout << "\n  reverse compare partial match: true";
        int res = partial_match.compare(test_string);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n reverse compare partial match: false";
    }
    if (no_match.compare(test_string)){
        std::cout << "\n reverse compare no match: true";
        int res = no_match.compare(test_string);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n reverse compare no match: false";
    }
    if (empty.compare(test_string)){
        std::cout << "\n compare empty: true";
        int res = empty.compare(test_string);
        if (res < 0){
            std::cout << "\n negative val";
        } else if (res > 0) {
            std::cout << "\n negative val";
        }
    } else {
        std::cout << "\n compare empty: false";
    }

    if (test_string == full_match){
        std::cout << "\n simple compare full match: true";
    } else {
        std::cout << "\n simple compare full match: false";
    }
    if (test_string == partial_match){
        std::cout << "\n simple compare partial match: true";
    } else {
        std::cout << "\n simple compare partial match: false";
    }
    if (test_string == no_match){
        std::cout << "\n simple compare no match: true";
    } else {
        std::cout << "\n simple compare no match: false";
    }
    if (test_string == empty){
        std::cout << "\n simple compare empty: true";
    } else {
        std::cout << "\n simple compare empty: false";
    }

    std::cout << "\n end find/compare string tests\n\n";

    std::cout << "\n npos value" << std::string::npos << "\n";
    std::cout << "\n static cast npos to int " << static_cast<int>(std::string::npos) << "\n";
    std::cout << "\n c cast npos to int " << int(std::string::npos) << "\n";
    size_t t = std::string::npos;
    std::cout << "\n c cast size_t of value npos " << int(t) << "\n";
    return 0;
}
