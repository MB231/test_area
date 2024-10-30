#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    double green_min = 999.0;
    double green_max = 1001.0;
    double yellow_min = 99.0;
    double yellow_max = 101.0;
    double red_min = 0;
    double red_max = 11;
    double checkValue = 0;
    std::string s = "\"1000\"";
    try {
        checkValue = std::stod(s);
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }

    std::cout << "checkValue: " << checkValue << '\n';
    
    if (checkValue > green_min && checkValue < green_max) {
        std::cout << "\ngreen\n";
    } else if (checkValue > yellow_min && checkValue < yellow_max) {
        std::cout << "\nyellow\n";
    } else if (checkValue > red_min && checkValue < red_max) {
        std::cout << "\nred\n";
    } else {
        std::cout << "\nunk\n";
    }

    return 0;
}
