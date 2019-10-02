#ifndef REGISTER_TEST_HPP
#define REGISTER_TEST_HPP
#include <sys/types.h>

//c style enum no namespace
typedef enum GPIO: u_int8_t {  //types are fixed and can list of types corresponding to order in enum
    GPIO_NONE =0x00,
    GPIO00 =(0x01 <<0),
    GPIO01 =(0x01 <<1),
    GPIO02 =(0x01 <<2),
    GPIO03 =(0x01 <<3),
    GPIO04 =(0x01 <<4),
    GPIO05 =(0x01 <<5),
    GPIO06 =(0x01 <<6),
    GPIO07 =(0x01 <<7),
    GPIO_ALL = 0xFF
}GPIO;
//c style enum with namespace
namespace ns_GPIO {
typedef enum GPIO: u_int8_t {
    GPIO_NONE =0x00,
    GPIO00 = 0xF0,
    GPIO01 =(0x01 <<1),
    GPIO02 =(0x01 <<2),
    GPIO03 =(0x01 <<3),
    GPIO04 =(0x01 <<4),
    GPIO05 =(0x01 <<5),
    GPIO06 =(0x01 <<6),
    GPIO07 =0x0F,
    GPIO_ALL = 0xFF
}GPIO;
}
//cpp class style enum aka strongly typed enum
/*
 * RULES
 * The enumerators can only be accessed in the scope of the enumeration.
 * The enumerators don't implicitly convert to int.(must static_cast it)
 * The enumerators aren't imported in the enclosing scope.
 * The type of the enumerators is by default int. Therefore, you can forward the enumeration.
 * class == struct
 */
enum class GPIOCLASS: u_int8_t {
    GPIO_NONE =0x00,
    GPIO00 =  0xF0,
    GPIO01 =(0x01 <<1),
    GPIO02 =(0x01 <<2),
    GPIO03 =(0x01 <<3),
    GPIO04 =(0x01 <<4),
    GPIO05 =(0x01 <<5),
    GPIO06 =(0x01 <<6),
    GPIO07 =0x0F,
    GPIO_ALL = 0xFF
};
//Example enum use with struct instead of namespace
struct X
{
    enum direction { left = 'l', right = 'r' };
};
X x;
X* p = &x;
 
int a = X::direction::left; // allowed only in C++11 and later
int b = X::left;
int c = x.left;
int d = p->left;

#endif    // REGISTER_TEST_HPP
