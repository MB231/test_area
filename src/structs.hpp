// MEMORY MAPPING W/ STRUCT
/*
 *The offset of the first struct member is always 0x0 from the objects address (this is not
 *   guaranteed in C++ but usually is the case).
 *The compiler cannot reorder the members, so OTYPER will always come at a higher address
 *   in memory than MODER and at a lower than OSPEEDR.
 *However, we cannot guarantee that the compiler will not introduce padding between members,
 *   as the standard states:
 *There may be unnamed padding within a structure object, but not at its beginning.
 */
// C11 compile time check of size of struct to prevent packing
//  static_assert(sizeof(GPIO_t) == 40, "padding in GPIO_t present");

// older methods

// WITH POINTER, relies on compiler to make better than defines
/*

volatile u_int32_t *const portd_moder = ( u_int32_t * )0x40020C00;
volatile u_int32_t *const portd_odr   = ( u_int32_t * )0x40020C14;

extern void sleep(u_int32_t ms);    // use systick to busy-wait

int main(void) {
    u_int32_t moder = *portd_moder;
    moder |= (1 << 16);
    moder &= ~(1 << 17);
    *portd_moder = moder;

    while (1) {
        *portd_odr |= (1 << 8);    // led-on
        sleep(500);
        *portd_odr &= ~(1 << 8);    // led-off
        sleep(500);
    }
}
*/
// WITH DEFINE
/*
#define PORTD_MODER (*(( volatile u_int32_t * )0x40020C00))
#define PORTD_ODR (*(( volatile u_int32_t * )0x40020C14))

extern void sleep(u_int32_t ms);    // use systick to busy-wait

int main(void) {
    u_int32_t moder = PORTD_MODER;
    moder |= (1 << 16);
    moder &= ~(1 << 17);
    PORTD_MODER = moder;

    while (1) {
        PORTD_ODR |= (1 << 8);    // led-on
        sleep(500);
        PORTD_ODR &= ~(1 << 8);    // led-off
        sleep(500);
    }
}
*/

#include <sys/types.h>//for type sized ints
#include <chrono>//for sleep()

typedef struct {
    u_int32_t MODER;      // mode register,                     offset: 0x00
    u_int32_t OTYPER;     // output type register,              offset: 0x04
    u_int32_t OSPEEDR;    // output speed register,             offset: 0x08
    u_int32_t PUPDR;      // pull-up/pull-down register,        offset: 0x0C
    u_int32_t IDR;        // input data register,               offset: 0x10
    u_int32_t ODR;        // output data register,              offset: 0x14
    u_int32_t BSRR;       // bit set/reset register,            offset: 0x18
    u_int32_t LCKR;       // configuration lock register,       offset: 0x1C
    u_int32_t AFRL;       // GPIO alternate function registers, offset: 0x20
    u_int32_t AFRH;       // GPIO alternate function registers, offset: 0x24
} GPIO_t;
//} __attribute__((packed)) GPIO_t; use this or compiler flags to prevent packing ruining offset

// using pointers with the struct to define the map
volatile GPIO_t *const porta = ( GPIO_t * )0x40020000;
volatile GPIO_t *const portb = ( GPIO_t * )0x40020400;
volatile GPIO_t *const portc = ( GPIO_t * )0x40020800;
volatile GPIO_t *const portd = ( GPIO_t * )0x40020C00;
volatile GPIO_t *const porte = ( GPIO_t * )0x40021000;
// to access a pointer initialized struct
porta->ODR |= (1 << 8);    // led-on

// using define to make make struct at that location
#define PORTD (*(( volatile GPIO_t )0x40020C00))
PORTD.ODR |= (1 << 8);    // led-on

// pointer version with Struct
/*
int main(void) {
    *rcc_ahb1enr |= (1 << 3);    // enable PortD's clock

    u_int32_t moder = portd->MODER;
    moder |= (1 << 16);
    moder &= ~(1 << 17);
    portd->MODER = moder;

    while (1) {
        portd->ODR |= (1 << 8);    // led-on
        sleep(500);
        portd->ODR &= ~(1 << 8);    // led-off
        sleep(500);
    }
}
*/
