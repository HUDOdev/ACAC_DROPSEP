#include "App_definitions.h"

#pragma CODE_SECTION(Read_adc, ".TI.ramfunc");      // Im RAM ausführen




void Read_adc(void)
{

//#
// Umrechnung AD-Werte in Physikalische Werte, schnelle Werte ohne Filterung
//#
    EALLOW;

    // Überstromabschaltung
    if(AdccResultRegs.ADCRESULT1 > CU_BUCK_POSITIV_LIMIT)// || AdccResultRegs.ADCRESULT1 < CU_BUCK_NEGATIV_LIMIT)
    {
        EPwm1Regs.TZFRC.bit.OST = 1;                // Flag für TZ one-shot event, manueller Rest nur über: EPwm1Regs.TZCLR.bit.OST = 1;
        EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;    // Stoppen des PWM Counter Modes -> PWM zählt nicht weiter
        EPwm1Regs.TBCTR = 0x0000;                   // Counter wird aud 0 gesetzt

        GpioDataRegs.GPBSET.bit.GPIO34 = 1;      // grüne LED auf DEV Board ausschalte

    }

    EDIS;



        ADC.IN1 = (AdcaResultRegs.ADCRESULT0);
        ADC.IN2 = (AdcbResultRegs.ADCRESULT0);
        ADC.IN3 = (AdccResultRegs.ADCRESULT0);

        GLOBALS.vo_dc_plus = ADC.IN1 - ADC.IN3;

        ADC.IN4 = (AdccResultRegs.ADCRESULT1 - OFFSETS.CUR_BUCK) * CONVERSION_FACTORS.CUR_SENSOR;

        ADC.IN5 = (AdcaResultRegs.ADCRESULT1 - OFFSETS.CUR_OUT) * CONVERSION_FACTORS.CUR_SENSOR;

        ADC.IN6 = (AdcbResultRegs.ADCRESULT2 - OFFSETS.VO_OUT) * CONVERSION_FACTORS.VO_OUT;
        ADC.IN7 = (AdccResultRegs.ADCRESULT2 * 0.000798); // 3.27/4096


}






