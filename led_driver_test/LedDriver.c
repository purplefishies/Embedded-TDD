#include <stdint.h>
#include <stdio.h>

#include "LedDriver.h"

enum {ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~0};

static uint16_t * ledsAddress;
static uint16_t ledsImage;

void LedDriver_Create(uint16_t * address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    *ledsAddress = ledsImage;
}

void LedDriver_Destroy(void)
{
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
    return 1 << (ledNumber - 1);
}

void LedDriver_TurnOn(int ledNumber)
{
    *ledsAddress |= convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOff(int ledNumber)
{
    *ledsAddress = 0;
}



static BOOL IsLedOutOfBounds(int ledNumber)
{
    if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED)) {
        fprintf(stderr,"LED Driver: out-of-bounds LED %d ", ledNumber);
        return TRUE;
    }
    return FALSE;
}



