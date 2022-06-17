#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED


#include "f28004x_cla_typedefs.h"   // f28004x CLA Type definitions
#include "f28004x_device.h"         // f28004x Headerfile Include File

#include "App_structs.h"
#include "App_bootloader.h"
#include "App_functions.h"




// The following pointer to a function call calibrates the ADC reference, DAC offset, and internal oscillators
#define Device_cal (void   (*)(void))0x070282

// The following pointers to functions calibrate the ADC linearity.  Use this in the AdcSetMode(...) function only
#define CalAdcaINL (void   (*)(void))0x0703B4
#define CalAdcbINL (void   (*)(void))0x0703B2
#define CalAdccINL (void   (*)(void))0x0703B0
#define CalAdcdINL (void   (*)(void))0x0703AE

// The following pointer to a function call looks up the ADC offset trim for a given condition. Use this in the AdcSetMode(...) function only.
#define GetAdcOffsetTrimOTP (Uint16 (*)(Uint16 OTPoffset))0x0703AC

//
// Include Example Header Files:
//

#include "f28004x_globalprototypes.h"  //Prototypes for global functions
                                       //within the .c files.
#include "f28004x_adc_defines.h"
#include "f28004x_cputimervars.h"
#include "f28004x_epwm_defines.h"
#include "f28004x_gpio_defines.h"       // Macros used for GPIO support code
#include "f28004x_pie_defines.h"        // Macros used for PIE examples
#include "f28004x_sysctrl_defines.h"    // Macros used for LPM support code
#include "f28004x_dma_defines.h"        // Macros used for DMA support code
#include "f28004x_cla_defines.h"        //Macros used for CLA support code
#include "f28004x_defaultisr.h"



extern void F28x_usDelay(long LoopCount);
#define DELAY_US(A)  F28x_usDelay(((((long double) A * 1000.0L) / (long double)10.00L) - 9.0L) / 5.0L)

#define HWREG(x) (*((volatile uint32_t *)(x)))
#define HWREG_BP(x) __byte_peripheral_32((uint32_t *)(x))
#define HWREGH(x) (*((volatile uint16_t *)(x)))

#define SWAP(x) ( ((((short int)(x))>>8)&0x00FF) | (((short int)(x))<<8) )
#define SWAPL(x) ( ((((long int)(x))>>16)&0x0000FFFF) | (((long int)(x))<<16) )

// The following pointer to a function call looks up the ADC offset trim for a given condition. Use this in the AdcSetMode(...) function only.
#define GetAdcOffsetTrimOTP (Uint16 (*)(Uint16 OTPoffset))0x0703AC

#define HWCODE 109   // HV-PS_V1
#define SECTORS 14

#define YEAR 2022
#define MONTH 12
#define DAY 1

#define FACTOR_UIN 0.00752  // Faktor zur Berechnung der Spannung an den Analogeingängen: 3.3V / 4096 * 112 / 12

#define EPWM1_PERIOD 1000   // Wert bis zu dem die PWM hoch läuft (up-down), entspricht 50 kHz
#define EPWM4_PERIOD 1000   // Wert bis zu dem die PWM hoch läuft (up-down), entspricht 50 kHz
#define EPWM1_MAX_CMP 900   // Maxiamale Einschaltdauer PWM
#define EPWM1_MIN_CMP 70   // Minimale Einschaltdauer PWM
#define EPWM4_MAX_CMP 900   // Maxiamale Einschaltdauer PWM
#define EPWM4_MIN_CMP 70   // Minimale Einschaltdauer PWM

#define VO_DC_PLUS_MAX 112  // Spannung Zwischenkreis nach Gleichrichter

#define CU_BUCK_POSITIV_LIMIT 2170      // Limit positiver Strom durch Tiefsetzsteller
#define CU_BUCK_NEGATIV_LIMIT 1920      // Limit negativer Strom durch Tiefsetzsteller

#define RAMP_SPEED 0.0001       // Geschwindigkeit Rampe



void Init_gpios(void);
void Init_system(void);
void Init_piectrl(void);
void Init_variables(void);
void Init_can(void);
void Init_EPwm(void);


interrupt void EPWM1_ISR(void);
interrupt void Read_can_a_ISR(void);
interrupt void cpuTimer1ISR(void);
void Eternal_loop(void);




void Init_can_module(void);
void Setup_can_obj(short int CAN, unsigned short int MOBJECTID, unsigned long int ID, unsigned short int DIRECTION, unsigned short int LENGTH, unsigned long int MASKE, unsigned short int FLAGS);
void Send_can_a(mboxdata *DATA);
void Send_can_a_16(mboxdata *DATA);

void Read_can_a(void);

void Send_cylic_messages(void);
void Process_can_data(mboxdata *DATA);
void Send_status(void);
void verarbeitung_can_msg(mboxdata *DATA);

void Setup_adc(void);
void Read_adc(void);
void Init_pga(void);




//float Current_calc(float,float);
//float Voltage_calc(float,float,float);
//void Regelung(void);

#endif

