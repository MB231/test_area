#ifndef REGISTER_TEST_HPP
#define REGISTER_TEST_HPP
#include <sys/types.h>

//c style enum no namespace
typedef enum GPIO: uint8_t {  //types are fixed and can list of types corresponding to order in enum
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
namespace GPIO{
typedef enum GPIO: uint8_t {
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
enum class GPIOCLASS: uint8_t {
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

//MEMORY MAPPING W/ STRUCT
/*
*The offset of the first struct member is always 0x0 from the objects address (this is not 
*   guaranteed in C++ but usually is the case).
*The compiler cannot reorder the members, so OTYPER will always come at a higher address 
*   in memory than MODER and at a lower than OSPEEDR.
*However, we cannot guarantee that the compiler will not introduce padding between members,
*   as the standard states:
*There may be unnamed padding within a structure object, but not at its beginning.
*/
//C11 compile time check of size of struct to prevent packing
//  static_assert(sizeof(GPIO_t) == 40, "padding in GPIO_t present");

//older methods
//with pointer, relies on compiler to make better than defines
volatile uint32_t* const portd_moder   = (uint32_t*) 0x40020C00;
volatile uint32_t* const portd_odr     = (uint32_t*) 0x40020C14;

extern void sleep(uint32_t ms); // use systick to busy-wait

int main(void)
{
  uint32_t moder = *portd_moder;
  moder |= (1 << 16);
  moder &= ~(1 << 17);
  *portd_moder = moder;

  while(1) {
    *portd_odr |= (1 << 8);   // led-on
    sleep(500);
    *portd_odr &= ~(1 << 8);  // led-off
    sleep(500);
  }
}

//with define
#define PORTD_MODER   (*((volatile uint32_t*) 0x40020C00))
#define PORTD_ODR     (*((volatile uint32_t*) 0x40020C14))

extern void sleep(uint32_t ms); // use systick to busy-wait

int main(void)
{
  uint32_t moder = PORTD_MODER;
  moder |= (1 << 16);
  moder &= ~(1 << 17);
  PORTD_MODER = moder;

  while(1) {
    PORTD_ODR |= (1 << 8);  // led-on
    sleep(500);
    PORTD_ODR &= ~(1 << 8); // led-off
    sleep(500);
  }
}

typedef struct
{
  uint32_t MODER;   // mode register,                     offset: 0x00
  uint32_t OTYPER;  // output type register,              offset: 0x04
  uint32_t OSPEEDR; // output speed register,             offset: 0x08
  uint32_t PUPDR;   // pull-up/pull-down register,        offset: 0x0C
  uint32_t IDR;     // input data register,               offset: 0x10
  uint32_t ODR;     // output data register,              offset: 0x14
  uint32_t BSRR;    // bit set/reset register,            offset: 0x18
  uint32_t LCKR;    // configuration lock register,       offset: 0x1C
  uint32_t AFRL;    // GPIO alternate function registers, offset: 0x20
  uint32_t AFRH;    // GPIO alternate function registers, offset: 0x24
} GPIO_t;
//} __attribute__((packed)) GPIO_t; use this or compiler flags to prevent packing ruining offset

volatile GPIO_t* const   porta       = (GPIO_t*)0x40020000;
volatile GPIO_t* const   portb       = (GPIO_t*)0x40020400;
volatile GPIO_t* const   portc       = (GPIO_t*)0x40020800;
volatile GPIO_t* const   portd       = (GPIO_t*)0x40020C00;
volatile GPIO_t* const   porte       = (GPIO_t*)0x40021000;

PORTD->ODR |= (1 << 8);     // led-on

#define PORTD       (*((volatile GPIO_t) 0x40020C00))<Paste>
PORTD.ODR |= (1 << 8);  // led-on

int main(void)
{
  *rcc_ahb1enr |= (1 << 3); // enable PortD's clock

  uint32_t moder = portd->MODER;
  moder |= (1 << 16);
  moder &= ~(1 << 17);
  portd->MODER = moder;

  while (1) {
    portd->ODR |= (1 << 8);  // led-on
    sleep(500);
    portd->ODR &= ~(1 << 8); // led-off
    sleep(500);
  }
}













#endif REGISTER_TEST_HPP

