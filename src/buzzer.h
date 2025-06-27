#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/flash.h>
#include <ti/grlib/grlib.h>

void beep(float tone, int duration_ms);
void playWeAreTheChampion();
// Note define

#define NOTE_C4 122
#define NOTE_CS4 116
#define NOTE_D4 109
#define NOTE_DS4 103
#define NOTE_E4 97
#define NOTE_F4 92
#define NOTE_FS4 87
#define NOTE_G4 82
#define NOTE_GS4 77
#define NOTE_A4 73
#define NOTE_AS4 69
#define NOTE_B4 65
#define NOTE_C5 61
#define NOTE_CS5 58
#define NOTE_D5 54
#define NOTE_DS5 51
#define NOTE_E5 48
#define NOTE_F5 46
#define NOTE_FS5 43
#define NOTE_G5 41
#define NOTE_GS5 39
#define NOTE_A5 36
#define NOTE_AS5 34
#define NOTE_B5 32
#define NOTE_C3 244
#define NOTE_CS3 230
#define NOTE_D3 218
#define NOTE_DS3 205
#define NOTE_E3 194
#define NOTE_F3 183
#define NOTE_FS3 173
#define NOTE_G3 163
#define NOTE_GS3 154
#define NOTE_A3 146
#define NOTE_AS3 137
#define NOTE_B3 130

#define QUARTER_NOTE_DURATION 652
#define SIZE 59

// 60/BPM = quater note duration in second
// Melody notes



#endif
