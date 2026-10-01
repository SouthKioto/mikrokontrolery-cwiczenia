#define F_CPU 16000000UL // procesor 16 MHz

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/* ---------- rejestry portu D ---------- */
#define KIERUNEK_PORTU_D DDRD // bit = 1: pin jest wyjsciem, 0: wejsciem
#define STAN_PORTU_D PORTD    // bit = 1: HIGH, 0: LOW (dla pinow wyjsciowych)
#define KIERUNEK_PD2 DDD2     // numer bitu pinu PD2 w DDRD
#define BIT_PD2 PORTD2        // numer bitu pinu PD2 w PORTD
#define BIT_PD3 PORTD3
#define BIT_PD4 PORTD4
#define BIT_PD5 PORTD5

/* ---------- maski ---------- */
// 1 na bitach 2-5: piny z diodami (D2-D5), uzywana do ustawienia wyjsc
#define MASKA_DIOD_D2_D5 0b00111100
// 1 na bitach 0-3: zostawia w liczniku tylko 4 najmlodsze bity (zakres 0-15)
#define MASKA_LICZNIKA_4BIT 0b1111
// 0 na bitach 2-5 (gasi diody), 1 na reszcie (chroni D0, D1, D6, D7)
#define MASKA_OCHRONY_PORTU_D 0b11000011

/* ---------- pojedyncza dioda na PD2 (zadanie 1) ---------- */
#define PD2_WLACZ (1 << BIT_PD2)
#define PD2_WYLACZ (~(1 << BIT_PD2))

/**
 * Dokumentacja
 * Diody sa podlaczone pod port D, ktory ma trzy rejestry:
 * - DDRD  (Data Direction Register): kierunek pinow, 1 = wyjscie, 0 = wejscie
 * - PORTD (Data Register): stan wyjsc, 1 = HIGH (dioda swieci), 0 = LOW
 * - PIND  (Input Pins): odczyt stanu pinow wejsciowych
 *
 * KIERUNEK_PORTU_D -> DDRD
 * STAN_PORTU_D     -> PORTD
 * PD2              -> pin portu D, do ktorego podlaczona jest dioda
 * KIERUNEK_PD2     -> bit w DDRD odpowiadajacy PD2
 * BIT_PD2          -> bit w PORTD odpowiadajacy PD2
 */

// INFO: DDRD  = 0b00000000 po resecie (wszystkie piny jako wejscia)
// INFO: PORTD = 0b00000000 po resecie

int main(void) {
  // z1: KIERUNEK_PORTU_D |= (1 << KIERUNEK_PD2);

  /* z2:
  KIERUNEK_PORTU_D |= 0b00000001;
  STAN_PORTU_D |= 0b00000001;
  */

  KIERUNEK_PORTU_D |= MASKA_DIOD_D2_D5; // piny D2-D5 jako wyjscia

  while (1) {
    /* Zadanie1: Miganie diody na pinie 2
    STAN_PORTU_D |= PD2_WLACZ;
    _delay_ms(10000);

    STAN_PORTU_D &= PD2_WYLACZ;
    _delay_ms(10000);
    */

    /* Zadanie2: Biegnace swiatlo, dodatkowa funkcjonalnosc: swiatlo powraca
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
    }*/

    // Zadanie3: licznik binarny 0-15 na diodach D2-D5
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
}
