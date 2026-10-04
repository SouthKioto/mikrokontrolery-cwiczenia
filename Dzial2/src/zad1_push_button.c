#define F_CPU 16000000UL

#include "../include/zad1_push_button.h"
#include "../include/Gpio.h"

#include <util/delay.h>

#define LED 0b00010000
#define BUTTON 0b00001000
#define DELAY_500 500
#define STAN_PRZYC (PIND & BUTTON)
#define DEBOUNCE_TIME 25

uint8_t poprzedni_stan = 0;
uint8_t stan_led = 0;
void zad1_push_button() {
  KIERUNEK_PORTU_D |= LED;     // pin 4 led jako wyjscie
  KIERUNEK_PORTU_D &= ~BUTTON; // pin 3 button jako wejscie
  STAN_PORTU_D |= BUTTON;      // ustawienie

  _delay_ms(DEBOUNCE_TIME);
  uint8_t stan = !STAN_PRZYC;
  if (stan && !poprzedni_stan) {
    stan_led = !stan_led;

    if (stan_led) {
      STAN_PORTU_D |= LED;
    } else {
      STAN_PORTU_D &= ~LED;
    }
  }

  poprzedni_stan = stan;
}
