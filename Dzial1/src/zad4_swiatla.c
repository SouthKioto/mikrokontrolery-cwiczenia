#include "../include/zad4_swiatla.h"
#include "../include/Gpio.h"
#include <stddef.h>
#include <stdint.h>
#include <util/delay.h>

/*
 * Działanie:
 * Swiatlo: 1.red, 2.orange, 3.green
 * DDRD (KIERUNEK_PORTU_D): ustawione na 0b00011100
 * PORTD (STAN_PORTU_D): ustawione na 0b00010000 (default czerwone)
 *
 * Podpiecia (nazwa w gpio.h oraz bit na płytce):
 *    BIT_PD2 -> bit 4
 *    BIT_PD3 -> bit 5
 *    BIT_PD4 -> bit 6
 */

// 1 na bitach 2-7: piny z diodami (D2-D7), uzywana do ustawienia wyjsc
#define MASKA_DIOD_D2_D7 0b11111100
// 1 na bitach 0-5: zostawia w liczniku tylko 6 najmlodsze bity
#define MASKA_LICZNIKA_6BIT 0b111111
#define MASKA_OCHRONY_PORTU_D 0b00000011 // swiatla na pinach 2-7

struct swiatla {
  uint8_t maska;
  int czas_ms;
};

void swiatla_init() {
  struct swiatla swiatlaArr[3] = {
      {0b10000100, 5000}, {0b01001000, 2000}, {0b00110000, 6000}};

  size_t swiatlaArrLenght = sizeof(swiatlaArr) / sizeof(swiatlaArr[0]);

  uint8_t licznik = 0;
  while (1) {
    if (licznik % swiatlaArrLenght == 0) {
      licznik = 0;
    }

    uint8_t pbd = STAN_PORTU_D & MASKA_OCHRONY_PORTU_D;

    STAN_PORTU_D = pbd | swiatlaArr[licznik].maska;

    for (int i = 0; i <= swiatlaArr[licznik].czas_ms - 1; i++) {
      _delay_ms(1);
    }

    licznik++;
  }
}
