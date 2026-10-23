#include "../include/zad2_push_button_licznik.h"
#include "../include/Gpio.h"

#include <avr/io.h>
#include <util/delay.h>

#define LEDY 0b11110000
#define BUTTON 0b00001000
#define BUTTON_STATE (PIND & BUTTON)
#define PORT_D_MAST 0b00001111
#define COUNTER_BITS 0b1111

void zad2_push_button_licznik() {

  uint8_t counter = 0;
  uint8_t poprzedni_stan = 0;
  while (1) {

    KIERUNEK_PORTU_D |= LEDY;
    // 0b00000000
    // 0b11110000 |
    // 0b11110000 kierunek portu
    KIERUNEK_PORTU_D &= ~BUTTON;
    // 0b11110000
    // 0b11110111 &
    // 0b11110000 kierunek portu
    STAN_PORTU_D |= BUTTON;

    uint8_t stan = !BUTTON_STATE;

    if (stan & !poprzedni_stan) {
      counter++;

      uint8_t licznikBit = COUNTER_BITS & counter;
      // 0 = 0b0000
      // 1 = 0b0001
      // 2 = 0b0010

      licznikBit = (licznikBit << 4);

      uint8_t stan_bez_diod = STAN_PORTU_D & PORT_D_MAST;

      STAN_PORTU_D = stan_bez_diod | licznikBit;
      _delay_ms(250);
    }
    poprzedni_stan = stan;
  }
}
