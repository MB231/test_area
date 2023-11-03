#include <sys/types.h>

#include <bitset>
#include <iostream>
#include <sstream>

int main() {
    // NOTE::REMEMBER BIT SHIFT WITH 0 AS FIRST BIT 1UL 1U and 0x01 can be used interchangeably execept by type (uLong,
    // uint, int)
    u_int8_t reg = 0b01010101;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;
    std::cout << "\n\n\nSet and Clear Examples" << std::endl;
    // setting 8th bit use or
    reg |= (1UL << 7);
    std::cout << "set 8th bit" << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // clearing 8th bit use and
    reg &= ~(0x01 << 7);
    std::cout << "clear 8th bit" << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // Toggle example with checking example with bitset use example
    // checkbit is used to see if bit is a 1 or 0 should give all 0(false) if correct
    // bitset is just to see if it can be used similiarly
    std::bitset<8> bitExp;
    u_int8_t checkBit = 0;

    std::cout << "\n\n\nToggle and Checkbit Examples" << std::endl;
    // toggle 8th bit use xor
    reg ^= (0x01 << 7);
    std::cout << "\ntoggle 8th bit" << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // check  8th bit use xor
    checkBit = (reg >> 7) & 1UL;
    bitExp   = reg;
    std::cout << "\n\ncheck 8th bit" << std::endl;
    std::cout << "checkBit Value if ** 1 **: " << std::bitset<8>(checkBit) << std::endl;
    std::cout << "bitset test of 7th bit: " << bitExp.test(7) << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // toggle 8th bit use xor
    reg ^= (0x01 << 7);
    std::cout << "\ntoggle 8th bit" << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // check  8th bit use xor
    checkBit = (reg >> 7) & 1UL;
    bitExp   = reg;
    std::cout << "\n\ncheck 8th bit" << std::endl;
    std::cout << "checkBit Value if ** 1 **: " << std::bitset<8>(checkBit) << std::endl;
    std::cout << "bitset test of 7th bit: " << bitExp.test(7) << std::endl;    // bitset still 0 as start
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // CHANGING Nth BIT TECHNIQUES
    //
    // Algorithm number ^= (-x ^ number) & (1UL << n);
    // bit n will be set if x is 1 or cleared if 0. If x is some other value UB.
    // Use x = !!x to booleanize to 0 or 1
    // 8th bit set to 1
    std::cout << "\n\n\n Nth Bit Value Set Techniques" << std::endl;
    reg ^= (-0x01 ^ reg) & (1UL << 7);
    std::cout << "change 8th bit to 1" << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;
    std::cout << "current reg state" << std::bitset<8>(reg) << std::endl;

    // 8th bit set to 0
    reg ^= (-0x00 ^ reg) & (1UL << 7);
    std::cout << "change 8th bit to 0" << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;
    // 8th bit set with booleanizations
    std::cout << "booleanizations: -1=" << !!(-1) << "  +200=" << !!(200) << "  0=" << !!(0) << std::endl;
    int other = -220;
    reg ^= (-(!!other) ^ reg) & (1UL << 7);
    std::cout << "change 8th bit to int non 0 or 1 set to !!-220: " << !!other << std::endl;
    std::cout << "current reg state: " << std::bitset<8>(reg) << std::endl;

    // Algorithm: number ^= (-(unsigned long)x ^ number) & (1UL <<n);
    // independent of 2s compliment negation behavior(-1 has all bits set unlike 1's compliment
    // or sign/magnitude C++ implementations)

    // Algorithm:(use of unsigned types for portable bit manipulation
    //      unsigned long newbit = !!x; //booleanizxe to force 0 or 1
    //      number ^= (-newbit ^ number) & (1UL << n);

    // Algorithm: number = (number * ~(1UL << n)) | (x << n);
    //(number & ~(1UL << n)) will cleat the nth bit and (x << n) will set the nth to x

    // BITSET USE EXAMPLEs
    std::cout << "\n\n\n Bitset Examples" << std::endl;
    std::bitset<8> bitExp1;
    bitExp1 = 0b01010101;    // can assign but not reliably use methods!!
    std::cout << "use of assign 01010101: " << bitExp1 << std::endl;
    bitExp1.set();    // set all high
    std::cout << "use of set for all high: " << bitExp1 << std::endl;
    bitExp1.reset();    // set all low
    std::cout << "use of reset: " << bitExp1 << std::endl;
    bitExp1.set(7, true);    // set only 7th bit high
    std::cout << "use of set for single bit: " << bitExp1 << std::endl;
    // show if all any or none bits are set and how may are high
    std::cout << "\n\nmethod examples" << std::endl;
    std::cout << "see if any bits high: " << bitExp1.all() << "  see if any are set: " << bitExp1.any()
              << "  see if all are low: " << bitExp1.none() << "  # of bits high: " << bitExp1.count() << std::endl;

    //&= (AND), |= (OR), ^= (XOR), ~ (NOT), <<=, >>= (shift left and right) all work
    // == != << >> | & ^ all work as well
    std::cout << "flip with flip() all bits(ones complement): " << bitExp1.flip() << std::endl;
    std::cout << "after flip it reads: " << bitExp1 << std::endl;
    std::cout << "get size of this bitset value: " << bitExp1.size() << std::endl;

    // Stream tests
    std::string bit_string = "00010001";    // create a string to initialize stream with
    std::istringstream bit_stream(bit_string);     // create a stream with above string in it
    // bitExp1 << std::bitset<8>inbit(0x081) cannot stream in to or out to an std::bitset

    std::cout << "\n\nsteam examples" << std::endl;
    std::cout << "use of stream << operator:\n std::cout << bitExp1 = " << bitExp1 << std::endl;

    int outbit = 0;
    std::cout << "use of stream >> operator:\n bitExp1 >> outBit; int type outBit=" << bitExp1 << std::endl;
    bit_stream >> bitExp1;
    std::cout << "use of stream >> operator bit_stream loaded with 00010001 string:\n  bit_stream >> bitExp1; ="
              << bitExp1 << std::endl;

    // use of index examples
    std::cout << "\n\nuse of index bitExp1[0]=" << bitExp1[0] << std::endl;
    std::cout << "use of index bitExp1[3]=" << bitExp1[3] << std::endl;

    // conversion examples
    std::cout << "\n\nConversion Example" << std::endl;
    std::cout << "to string:" << bitExp1.to_string() << "  to ulong: " << bitExp1.to_ulong()
              << "  to ullong: " << bitExp1.to_ullong() << std::endl;
}
