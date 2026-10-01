#include <util/delay.h>

#include "../include/Gpio.h"
#include "../include/zad2_biegnace_swiatlo.h"

// Zadanie2: Biegnace swiatlo, dodatkowa funkcjonalnosc: swiatlo powraca
void zad2_biegnace_swiatlo(void) {
  int licznik = 0;
  while (1) {
    if (licznik % 4 == 0) {
      KIERUNEK_PORTU_D |= 0b00000001;
      STAN_PORTU_D |= 0b00000001;
    }

    KIERUNEK_PORTU_D = (KIERUNEK_PORTU_D << 1);

    STAN_PORTU_D = (STAN_PORTU_D << 1);
    _delay_ms(1000);

    licznik++;
  }
}
