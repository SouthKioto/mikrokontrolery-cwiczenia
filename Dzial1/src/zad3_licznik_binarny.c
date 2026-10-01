#include <stdint.h>
#include <util/delay.h>

#include "../include/Gpio.h"
#include "../include/zad3_licznik_binarny.h"

// 1 na bitach 2-5: piny z diodami (D2-D5), uzywana do ustawienia wyjsc
#define MASKA_DIOD_D2_D5 0b00111100
// 1 na bitach 0-3: zostawia w liczniku tylko 4 najmlodsze bity (zakres 0-15)
#define MASKA_LICZNIKA_4BIT 0b1111
// 0 na bitach 2-5 (gasi diody), 1 na reszcie (chroni D0, D1, D6, D7)
#define MASKA_OCHRONY_PORTU_D 0b11000011

// Zadanie3: licznik binarny 0-15 na diodach D2-D5
void zad3_licznik_binarny(void) {
  KIERUNEK_PORTU_D |= MASKA_DIOD_D2_D5; // piny D2-D5 jako wyjscia

  uint8_t licznik = 0;
  while (1) {
    uint8_t licznik_na_pinach =
        MASKA_LICZNIKA_4BIT & licznik;            // obciecie do 4 bitow
    licznik_na_pinach = (licznik_na_pinach << 2); // bit 0 -> D2, bit 3 -> D5
    uint8_t port_bez_diod =
        STAN_PORTU_D &
        MASKA_OCHRONY_PORTU_D; // zgaszone D2-D5, reszta bez zmian
    STAN_PORTU_D = port_bez_diod | licznik_na_pinach; // nowy stan portu
    _delay_ms(500);

    licznik++;
  }
}
