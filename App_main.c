
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "App_definitions.h"


#pragma CODE_SECTION(Eternal_loop, ".TI.ramfunc");
#pragma CODE_SECTION(EPWM1_ISR, ".TI.ramfunc");



struct Cancomm CANCOMM;
struct Globals GLOBALS;
struct Adc ADC;
struct Offsets OFFSETS;
struct Conversion_factors CONVERSION_FACTORS;
struct Control_const CONTROL_CONST;
struct Target_values TARGET_VALUES;






void main(void)
{
  DINT;                      // Globale Interrupts aus

  Init_system();

  GLOBALS.antibrick = 0;


  EALLOW; // Enable access to protected registers

  if(EPwm1Regs.TZFLG.bit.OST == 0)
  {
      CpuSysRegs.PCLKCR2.bit.EPWM1=1;     // Enable PWM1 |S.198|
      CpuSysRegs.PCLKCR2.bit.EPWM4=1;     // Enable PWM4 |S.198|
  }




  IER = 0x0000;         // Interrupts deaktivieren
  IFR = 0x0000;         // Interrupts Flag


  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; //When set, it synchronizes all enabled ePWM modules to the time-base clock (TBCLK). |S.195
  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; //When set, it synchronizes all enabled ePWM modules to the time-base clock (TBCLK). |S.195

  IER |= M_INT3;                        // Enable EPWM1 INT
  PieCtrlRegs.PIEIER3.bit.INTx1 = 1;    // Enable EPWM INTn in the PIE


  EDIS; // Disable access to protected registers




//  WdRegs.WDCR.all = 0x0128;           // Watchdog, 10MHz/1024, Ãœberlauf bei 256 -> Watchdog nach ca. 26ms
//  WdRegs.WDKEY.all = 0x55;
//  WdRegs.WDKEY.all = 0xAA;              // reset watchdog

  DELAY_US(10000);

  ADC_calibration();


  EINT;                                 // Globale Interrupts an
  //ERTM;                                 // Debugmode Interrupt an



  Eternal_loop();                       // Start der Dauerschleife

}



// Funktion, die in dem RAM ausgefÃ¼hrt wird

interrupt void EPWM1_ISR(void)                  // Timer Interrupt alle 1ms (1kHz)
{
    EALLOW;



//  WdRegs.WDKEY.all = 0x55;
//  WdRegs.WDKEY.all = 0xAA;                    // reset watchdog
    EINT;                                         // andere Interrupts zulassen
    ERTM;                                         // Debugmode Interrupt an

    Read_adc();                                     // Einlesen der Analogeingänge mit Filterung





    EPwm1Regs.ETCLR.bit.INT = 1;                // Clear INT flag for this timer
    EPwm1Regs.ETCLR.bit.SOCA = 1;               // Clear INT flag for this ADC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;     // Is set when interrupt propagates from the ePIE to the CPU the interrupt group's PIEACK bit is set.

    EINT;

}

//interrupt void cpuTimer1ISR(void)           // Timer Interrupt alle 10ms
//{
//  EINT;                                     // andere Interrupts zulassen
//  //EALLOW;
//
//  if (GLOBALS.timer_250) GLOBALS.timer_250--;
//  else
//  {
//      GpioDataRegs.GPATOGGLE.bit.GPIO23 = 1;         // Orange LED aussen blinkt im Bootloader
//      GLOBALS.timer_250 = 250;
//  }
//}



void Eternal_loop(void)
{



    while(1)
    {

        if(EPwm1Regs.TZFLG.bit.OST == 0 && !GLOBALS.timer_250)
        {
            GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

            // Vor einschalten Verhältniss von DC++/DC+ berechen
            // Diesen wert an Target Values übergeben
            // Erst wenn Richtiger Duty Cycle erreicht darf wieder eingeschaltet werden
            // Beispiel DC++=50V, DC+=100V  -> Duty Cycle MUSS =  0.5 sein da sonst MOSFETS zerstört werden


            if(EPwm1Regs.CMPA.bit.CMPA == 0 && EPwm1Regs.TBCTR == 0x0000)
            {   EALLOW;
                EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
            }   EDIS;

        }
        else if(EPwm1Regs.TZFLG.bit.OST == 1 && TARGET_VALUES.VO_DC_PLUS_PLUS > 0)      // Sperrung der Spannungseinstellung solage Fehler aktiv
        {
            TARGET_VALUES.VO_DC_PLUS_PLUS = 0;
        }




        if (GLOBALS.timer_250) GLOBALS.timer_250--;             // Globaler Timer wird runter gezählt
          else
          {
              GpioDataRegs.GPATOGGLE.bit.GPIO23 = 1;            // Rote LED auf Dev-Board blinkt langsam in der APP
              GLOBALS.timer_250 = 60000;                        // Timer auf Startwert zurücksetzen
          }



        // STEP 1

        // STEP 2

        // STEP 3

            //#
            // Filterung der Analogwerte
            //#

            // Berechnung Filterkoeffitient a

            //T_s: is the sample time of the IIR Filter block
            //f_c: is the cutoff frequency of the IIR filter.
            //a: is the filter coefficient in the range (0, 1].

            // a = (2*pi*T_s*f_c) / (2*pi*T_s*f_c + 1)

            //        GLOBALS.vo_dc_minus = IIR_filter(ADC.IN1, 0.07, &ADC.IN1_old);
            //        GLOBALS.vo_dc_plus_plus = IIR_filter(ADC.IN2, 0.07, &ADC.IN2_old);
            //        GLOBALS.vo_dc_plus = IIR_filter(ADC.IN3, 0.07, &ADC.IN3_old);

            GLOBALS.cur_buck = IIR_filter(ADC.IN4, 0.1, &ADC.IN4_old);
            GLOBALS.cur_out = IIR_filter(ADC.IN5, 0.1, &ADC.IN5_old);

            GLOBALS.vo_out = IIR_filter(ADC.IN6, 0.1, &ADC.IN6_old);
            GLOBALS.vo_2V4 = IIR_filter(ADC.IN7, 0.1, &ADC.IN7_old);

            // STEP 4

            // STEP 5

            Ramp(&TARGET_VALUES.VO_DC_PLUS_PLUS, &GLOBALS.vo_buck_instant_value);



            // STEP 6

            GLOBALS.epwm1_duty = Duty_cycle(&GLOBALS.vo_buck_instant_value);
            EPwm1Regs.CMPA.bit.CMPA = EPwm1_cmp_calc(&GLOBALS.epwm1_duty);
            //pwm_value =

    }
}


//
// End of file
//
