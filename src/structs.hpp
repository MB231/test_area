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

#include <sys/types.h>    //for type sized ints
#include <unistd.h>       //for sleep()

volatile u_int32_t *const portd_moder = ( u_int32_t * )0x40020C00;
volatile u_int32_t *const portd_odr   = ( u_int32_t * )0x40020C14;

int withpointer(void) {
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
// WITH DEFINE
#define PORTD_MODER (*(( volatile u_int32_t * )0x40020C00))
#define PORTD_ODR (*(( volatile u_int32_t * )0x40020C14))

int withDefine(void) {
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

// no name here is needed only last instantiation for anonymous struct
// typedef struct {
typedef struct GPIO_t {
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
//#pragma pack(1) is gcc flag for no packing

// using pointers with the struct to define the map Ex of 5 ports with same map
volatile GPIO_t *const porta = ( GPIO_t * )0x40020000;
volatile GPIO_t *const portb = ( GPIO_t * )0x40020400;
volatile GPIO_t *const portc = ( GPIO_t * )0x40020800;
volatile GPIO_t *const portd = ( GPIO_t * )0x40020C00;
volatile GPIO_t *const porte = ( GPIO_t * )0x40021000;

/* using define to make make struct at that location. C ONLY
#define portx (*(( volatile GPIO_t )0x40020C00))
portx.ODR |= (1 << 8);    // led-on
*/

// pointer version with Struct
int LEDonOFF(void) {
    //*rcc_ahb1enr |= (1 << 3);    // enable PortD's clock. Needs header for STM32 to be defined

    u_int32_t moder = portd->MODER;    // get current value of register
    moder |= (1 << 16);                // set bit if not. unset if it is. TOGGLE LED
    moder &= ~(1 << 17);               // bitmask applied
    portd->MODER = moder;              // write to register

    while (1) {
        portd->ODR |= (1 << 8);    // led-on
        sleep(500);
        portd->ODR &= ~(1 << 8);    // led-off
        sleep(500);
    }
}

// MY EXAMPLE
//
typedef struct {
    u_int8_t HEADER = 0x08;                 // SET_CLEAR_CMD
    u_int8_t BLANK1[10];                    // blank indexes
    u_int8_t SETPIN;                        // Pins to set
    u_int8_t CLEARPIN;                      // Pins to clear
    u_int8_t BLANK2[3];                     // blank indexes
} __attribute__((packed)) SET_CLEAR_CMD;    // use this or compiler flags to prevent packing ruining offset

typedef struct {
    u_int8_t HEADER = 0x10;              // SET_CLEAR_CMD
    u_int8_t BLANK1[3];                  // blank indexes
    u_int8_t IO_BMAP;                    // Pins to set
    u_int8_t ALT_SET;                    // Pins to clear
    u_int8_t IO_DFLT;                    // Pins to clear
    u_int8_t ALT_CONFIG;                 // Pins to clear
    u_int8_t BAUD_H;                     // Pins to clear
    u_int8_t BAUD_L;                     // Pins to clear
    u_int8_t BLANK2[6];                  // blank indexes
} __attribute__((packed)) CONFIG_CMD;    // use this or compiler flags to prevent packing ruining offset
