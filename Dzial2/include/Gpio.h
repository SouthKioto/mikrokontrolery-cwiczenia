#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

/* ---------- rejestry portu D ---------- */
#define KIERUNEK_PORTU_D DDRD // bit = 1: pin jest wyjsciem, 0: wejsciem
#define STAN_PORTU_D PORTD    // bit = 1: HIGH, 0: LOW (dla pinow wyjsciowych)
#define KIERUNEK_PD2 DDD2     // numer bitu pinu PD2 w DDRD
#define BIT_PD2 PORTD2        // numer bitu pinu PD2 w PORTD
#define BIT_PD3 PORTD3
#define BIT_PD4 PORTD4
#define BIT_PD5 PORTD5

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

// TODO: nowe mapowania portow dla Dzial2/

#endif
