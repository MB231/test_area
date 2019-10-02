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
            cout << "GPIO_ALL PASS" << endl;
        } else {
            cout << "GPIO_ALL FAIL";
        }

    cout << "\n\n\nstruct testing" << endl;
    u_int8_t setBuffer[16] = { 0 };
    u_int8_t cmdBuffer[16] = { 0 };

    // ALWAYS ZERO BUFFERS

    volatile SET_CLEAR_CMD *const set    = ( SET_CLEAR_CMD * )setBuffer;
    volatile CONFIG_CMD *const    config = ( CONFIG_CMD * )cmdBuffer;

    setBuffer[11] = 0x80;
    setBuffer[12] = 0x08;
    // write to setBuffer using struct as map
    set->HEADER   = 0x80;
    set->SETPIN   = (GPIO00 | GPIO01);
    set->CLEARPIN = (GPIO02 | GPIO03);
    // check if written correctly
    if (setBuffer[11] != 0x03) {
        cout << "buffer 11 write FAIL" << endl;
    }
    if (setBuffer[12] != 0x0c) {
        cout << "buffer 12 write FAIL" << endl;
    }

    cout << "read from setBuffer[11] 0x03 expected " << hex << ( int )setBuffer[11] << endl;
    cout << "read from struct->SETPIN 0x03 expected " << hex << ( int )set->SETPIN << endl;
    cout << "read from setBuffer[12] 0x0c expected " << hex << ( int )setBuffer[12] << endl;
    cout << "read from struct->CLEARPIN 0x0c expected " << hex << ( int )set->CLEARPIN << endl;
    cout << "read from setbuffer[0] 0x80 expected " << hex << ( int )setBuffer[0] << endl;
    cout << "dump buffer" << endl;
    for (int i = 0; i < 15; i++) {
        cout << hex << ( int )setBuffer[i] << ": is element " << dec << i << endl;
    }
    return 0;
}
