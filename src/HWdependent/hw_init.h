#ifndef _HW_INIT_H_
#define _HW_INIT_H_

//HW and graphic context initialization
void HW_Init();
void graphic_init();
void init_button();
void ADC_config();

/*
    Timer_A setup

    Nomenclature Note
    TAxn 
        x --> TimerA HW instance
        n --> capture/compare instance

    maybe in combination with a Real-Time Clock no beacuse it has second precision
*/


void timerInit();


//Override Interrup

void ADC14_IRQHandler();
void TA0_0_IRQHandler(); // Timer CCR0 

#endif
