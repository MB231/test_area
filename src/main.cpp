#include <sys/types.h>

#include <iostream>

#include "enum.hpp"
#include "structs.hpp"

using namespace std;
int main() {

    cout << "enum testing" << endl;
    cout << "c style global testing" << endl;
    cout << "GPIO00: " << hex << GPIO00 << endl;
    cout << "should be 0x01" << endl;
    cout << "GPIO07: " << hex << GPIO07 << endl;
    cout << "should be 0x80" << endl;
    cout << "GPIO_ALL: " << hex << GPIO_ALL << endl;

    cout << "c style with namespace" << endl;
    cout << "GPIO00: " << hex << ns_GPIO::GPIO00 << endl;
    cout << "should be 0xF0" << endl;
    cout << "GPIO07: " << hex << ns_GPIO::GPIO07 << endl;
    cout << "should be 0x0F" << endl;
    cout << "GPIO_ALL: " << hex << ns_GPIO::GPIO_ALL << endl;

    cout << "cpp enum class/struct" << endl;
    // must use if as GPIOCLASS is now a type that can't natively used or compared
    if (GPIOCLASS::GPIO00 == ( GPIOCLASS )0x7F) {
        cout << "GPIO00 PASS" << endl;
        } else {
            cout << "GPIO00 FAIL";
        }
        if (GPIOCLASS::GPIO07 == ( GPIOCLASS )0xF7) {
            cout << "GPIO07 PASS" << endl;
        } else {
            cout << "GPIO07 FAIL";
        }
        if (GPIOCLASS::GPIO_ALL == ( GPIOCLASS )0xFF) {
            cout << "GPIOIALL PASS" << endl;
        } else {
            cout << "GPIO_ALL FAIL";
        }
    cout << "struct testing" << endl;
    u_int8_t setBuffer[15];
    u_int8_t cmdBuffer[15];

    volatile SET_CLEAR_CMD *const set    = ( SET_CLEAR_CMD * )&setBuffer[0];
    volatile CONFIG_CMD *const    config = ( CONFIG_CMD * )cmdBuffer;

    set->SETPIN = (GPIO01 | GPIO02);
    set->CLEARPIN = (GPIO03 | GPIO04);

    cout << "setpin(0x03): " << hex << setBuffer[11] << endl;
    cout << "clearpin(0x0C): " << hex << setBuffer[12] << endl;
    return 0;
}
