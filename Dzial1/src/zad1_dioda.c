#include <util/delay.h>

#include "../include/Gpio.h"
#include "../include/zad1_dioda.h"

#define PD2_WLACZ (1 << BIT_PD2)
#define PD2_WYLACZ (~(1 << BIT_PD2))

// Zadanie1: Miganie diody na pinie 2
void zad1_dioda(void) {
  KIERUNEK_PORTU_D |= (1 << KIERUNEK_PD2);

  while (1) {
    STAN_PORTU_D |= PD2_WLACZ;
    _delay_ms(10000);

    STAN_PORTU_D &= PD2_WYLACZ;
    _delay_ms(10000);
  }
}
