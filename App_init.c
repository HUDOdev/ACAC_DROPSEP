
#include <App_definitions.h>

void Init_gpios(void)
{
  EALLOW;

  GpioDataRegs.GPADAT.all=0x00000000;     // alle GPIOS auf null setzen
  GpioDataRegs.GPBDAT.all=0x00000000;     // alle GPIOS auf null setzen
  GpioDataRegs.GPHDAT.all=0x00000000;     // alle GPIOS auf null setzen

  // GPIO 0, Pin 52, EPWM1_A
  GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0b00;
  GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 0b01;
  GpioCtrlRegs.GPAPUD.bit.GPIO0   = 1;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO0   = 1;    // Output

  // GPIO 1, Pin 51, EPWM1_B
  GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0b00;
  GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 0b01;
  GpioCtrlRegs.GPAPUD.bit.GPIO1   = 1;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO1   = 1;    // output

  // GPIO 2, Pin 50
  GpioCtrlRegs.GPAPUD.bit.GPIO2   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO2   = 1;    // output

  // GPIO 3, Pin 49
  GpioCtrlRegs.GPAPUD.bit.GPIO3   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO3   = 1;    // output

  // GPIO 4, Pin 48
  GpioCtrlRegs.GPAPUD.bit.GPIO4   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO4   = 0;    // Input

  // GPIO 5, Pin 61
  GpioCtrlRegs.GPAPUD.bit.GPIO5   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO5   = 0;    // Input

  // GPIO 6, Pin 64, EPWM4_A
  GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = 0b00;
  GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 0b01;
  GpioCtrlRegs.GPAPUD.bit.GPIO6   = 1;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO6   = 1;    // Output

  // GPIO 7, Pin 57, EPWM4_B
  GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = 0b00;
  GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 0b01;
  GpioCtrlRegs.GPAPUD.bit.GPIO7   = 1;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO7   = 1;    // Output

  // GPIO 8, Pin 47
  GpioCtrlRegs.GPAPUD.bit.GPIO8   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO8   = 0;    // Imput

  // GPIO 9, Pin 62, SPI CLK
  GpioCtrlRegs.GPAPUD.bit.GPIO9   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO9   = 0;    // Input

  // GPIO 10, Pin 63, CAN B RX
  GpioCtrlRegs.GPAPUD.bit.GPIO10   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO10   = 0;    // Input

  // GPIO 11, Pin 31
  GpioCtrlRegs.GPAPUD.bit.GPIO11   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO11   = 0;    // Input

  // GPIO 12, Pin 30
  GpioCtrlRegs.GPAPUD.bit.GPIO12   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO12   = 0;    // Input

  // GPIO 13, Pin 29
  GpioCtrlRegs.GPAPUD.bit.GPIO13   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO13   = 0;    // Input

  // GPIO 14, Pin 96
  GpioCtrlRegs.GPAPUD.bit.GPIO14   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO14   = 0;    // input

  // GPIO 15, Pin95
  GpioCtrlRegs.GPAPUD.bit.GPIO15   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO15   = 0;    // input

  // GPIO 16, Pin 33
  GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 0b10;
  GpioCtrlRegs.GPAMUX2.bit.GPIO16  = 0b11;
  GpioCtrlRegs.GPAPUD.bit.GPIO16   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO16   = 0;    // Input

  // GPIO 17, Pin 34
  GpioCtrlRegs.GPAPUD.bit.GPIO17   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO17   = 0;    // Input

  // GPIO 18, Pin 41, X2, Wird durch die Oszillatoreinstellung eingestellt

  // GPIO 19, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO19   = 1;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO19   = 0;    // Input

  // GPIO 20, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO20   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO20   = 0;    // Input

  // GPIO 21, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO21   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO21   = 0;    // Input

  // GPIO 22, Pin 56
  GpioCtrlRegs.GPAPUD.bit.GPIO22   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO22   = 0;    // Input

  // GPIO 23, Pin 54
  GpioCtrlRegs.GPAPUD.bit.GPIO23   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO23   = 1;    // Output
  GpioCtrlRegs.GPAAMSEL.bit.GPIO23 = 0;    // GPIO 23 nach Reset in speziellem Analog-Modus, für GPIO Nutzung Bit zurücksetzen
  // GPIO 24, Pin 35
  GpioCtrlRegs.GPAPUD.bit.GPIO24   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO24   = 0;    // Input

  // GPIO 25, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO25   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO25   = 0;    // Input

  // GPIO 26, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO26   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO26   = 1;    // Output

  // GPIO 27, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO27   = 0;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO27   = 0;    // Input

  // GPIO 28, Pin 2
  GpioCtrlRegs.GPAPUD.bit.GPIO28   = 0;    // Pullup disabled
  GpioCtrlRegs.GPADIR.bit.GPIO28   = 0;    // Input

  // GPIO 29, Pin 1
  GpioCtrlRegs.GPAPUD.bit.GPIO29   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO29   = 0;    // Input

  // GPIO 30, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO30   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO30   = 0;    // Input

  // GPIO 31, kein Pin
  GpioCtrlRegs.GPAPUD.bit.GPIO31   = 0;    // Pullup enabled
  GpioCtrlRegs.GPADIR.bit.GPIO31   = 0;    // Input

  //GPIO 32, Pin 40, CAN A TX
  GpioCtrlRegs.GPBGMUX1.bit.GPIO32 = 0b10;
  GpioCtrlRegs.GPBMUX1.bit.GPIO32  = 0b01;
  GpioCtrlRegs.GPBPUD.bit.GPIO32   = 1;    // Pullup disabled
  GpioCtrlRegs.GPBDIR.bit.GPIO32   = 1;    // Output

  //GPIO 33, Pin 32, CAN A RX
  GpioCtrlRegs.GPBGMUX1.bit.GPIO33 = 0b10;
  GpioCtrlRegs.GPBMUX1.bit.GPIO33  = 0b01;
  GpioCtrlRegs.GPBPUD.bit.GPIO33   = 1;    // Pullup disabled
  GpioCtrlRegs.GPBDIR.bit.GPIO33   = 0;    // Input
  GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;    // asynchron

  // GPIO 34, kein Pin
  GpioCtrlRegs.GPBPUD.bit.GPIO34   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO34   = 1;    // Output

  // GPIO 35, Pin 39, TDI, ab Reset bereits korrekt eingestellt

  // GPIO 36 existiert nicht

  // GPIO 37, Pin 37, TDO, ab Reset bereits korrekt eingestellt

  // GPIO 38 existiert nicht

  // GPIO39-59 keine Pins
  GpioCtrlRegs.GPBPUD.bit.GPIO39   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO39   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO40   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO40   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO41   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO41   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO42   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO42   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO43   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO43   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO44   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO44   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO45   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO45   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO46   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO46   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO47   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO47   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO48   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO48   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO49   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO49   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO50   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO50   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO51   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO51   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO52   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO52   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO53   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO53   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO54   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO54   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO55   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO55   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO56   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO56   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO57   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO57   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO58   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO58   = 0;    // Input

  GpioCtrlRegs.GPBPUD.bit.GPIO59   = 0;    // Pullup enabled
  GpioCtrlRegs.GPBDIR.bit.GPIO59   = 0;    // Input

  // GPIO60-63 existieren nicht

  // AIO 226 an B2/C6, OCD
  GpioCtrlRegs.GPHAMSEL.bit.GPIO226 = 0;  // Digital mode for B2 / AIO226
  // AIO 246 an C14, Digital in
  GpioCtrlRegs.GPHAMSEL.bit.GPIO246 = 0;  // Digital mode for C14 / AIO246
}

void Init_system(void)
{
  InitSysCtrl();        // Initialize device clock and peripherals

  DINT;                 // Disable CPU interrupts

  Init_piectrl();       // Initialize the PIE control registers to their default state.

  IER = 0x0000;         // Disable CPU interrupts and clear all CPU interrupt flags
  IFR = 0x0000;

  InitPieVectTable();   // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR)

//  // Timer Interrupt mit Timer1 alle 10ms
//    EALLOW;
//    PieVectTable.TIMER1_INT =  &cpuTimer1ISR;
//    //PieVectTable.CANA0_INT = &Read_can_a_ISR;
//    EDIS;
//
//
//    CpuTimer1Regs.TCR.bit.TSS = 1;    // Stop timer
//    CpuTimer1Regs.TPR.all  = 0;       // Sysclock-Divider = 1
//    CpuTimer1Regs.TPRH.all = 0;
//    CpuTimer1Regs.PRD.all = 1000000; // alle 10ms
//    CpuTimer1Regs.TCR.bit.TRB = 1;    // Reset to PRD
//    CpuTimer1Regs.TCR.bit.FREE = 0;   //
//    CpuTimer1Regs.TCR.bit.TIE = 1;    // Interrupt an
//    IER |= M_INT13;                   // Interrupt zulassen





  Init_EPwm();              // EPwm-Register belegen
  Init_gpios();             // Ausgangspins der Mikroprossessor initialisiern
  Init_variables();         // Variablen vorbelegen
  Init_can();
  Init_pga();
  Setup_adc();





}

//#
// Initialisierung Variabeln

void Init_variables(void)
{
  //GLOBALS.hwid = 0xFFFF; // wird bereits vorher ausgelesen!


  CANCOMM.activity = 0;           // Abschalten des automatischen Nachrichtenwiederholens
  CANCOMM.can_rr = 100;
  CANCOMM.uid_requested = 0;
  CANCOMM.delay1000 = 0;
  CANCOMM.can_silence = 0;

  GLOBALS.timer_250 = 250;


  GLOBALS.cmp_value_epwm1 = 0;
  GLOBALS.cmp_value_epwm4 = 0;




  OFFSETS.CUR_BUCK = 0.0;
  OFFSETS.CUR_OUT = 0.0;
  OFFSETS.VO_DC_MINUS = 0.0;
  OFFSETS.VO_DC_PLUS = 0.0;
  OFFSETS.VO_DC_PLUS_PLUS = 0.0;
  OFFSETS.VO_OUT = 0.0;

  CONVERSION_FACTORS.CUR_SENSOR = 0.021775;             // Faktor Umrechnung ADC zu Strom   !
  CONVERSION_FACTORS.VO_DC_PLUS = 0.107;                // Faktor Umrechnung ADC zu Spannung  325V/3735,6321    möglichst einfacher Faktor, deshalb der krumme AD Wert
  CONVERSION_FACTORS.VO_DC_PLUS_PLUS = 0.080586;        // Faktor Umrechnung ADC zu Spannung  300V/3722,727272
  CONVERSION_FACTORS.VO_DC_MINUS = 0.0;
  CONVERSION_FACTORS.VO_OUT = 0.1;

  CONTROL_CONST.VO_DC_PLUS_PLUS_MAX = 112.0;        // Maximale D++ Spannung
  CONTROL_CONST.VO_DC_PLUS_PLUS_MIN = 0.0;          // Minimale D++ Spannung
  CONTROL_CONST.CUR_BUCK_MAX = 5.0;                 // Maximaler Strom durch die Induktivität
  CONTROL_CONST.CUR_BUCK_MIN = 0.0;                 // Minimaler Strom durch die Induktivität

  CONTROL_CONST.VO_KP = 0.0;                        // PI-Regler Parameter für Spannung und Strom
  CONTROL_CONST.VO_KI = 0.0;
  CONTROL_CONST.CUR_KP = 0.0;
  CONTROL_CONST.CUR_KI = 0.0;
  CONTROL_CONST.SAMP_TIME = 0.00000025;             // Sampling Time AD-Wandler 250ns -> siehe App_analog.c

  TARGET_VALUES.VO_DC_PLUS_PLUS = 0.0;
  TARGET_VALUES.CUR_BUCK = 0.0;

  //#
  // Konstanten
  //#




}

void Init_piectrl(void)
{
  DINT;     // Disable Interrupts at the CPU level:
  PieCtrlRegs.PIECTRL.bit.ENPIE = 0;     // Disable the PIE
  // Clear all PIEIER registers:
  PieCtrlRegs.PIEIER1.all = 0;
  PieCtrlRegs.PIEIER2.all = 0;
  PieCtrlRegs.PIEIER3.all = 0;
  PieCtrlRegs.PIEIER4.all = 0;
  PieCtrlRegs.PIEIER5.all = 0;
  PieCtrlRegs.PIEIER6.all = 0;
  PieCtrlRegs.PIEIER7.all = 0;
  PieCtrlRegs.PIEIER8.all = 0;
  PieCtrlRegs.PIEIER9.all = 0;
  PieCtrlRegs.PIEIER10.all = 0;
  PieCtrlRegs.PIEIER11.all = 0;
  PieCtrlRegs.PIEIER12.all = 0;
  // Clear all PIEIFR registers:
  PieCtrlRegs.PIEIFR1.all = 0;
  PieCtrlRegs.PIEIFR2.all = 0;
  PieCtrlRegs.PIEIFR3.all = 0;
  PieCtrlRegs.PIEIFR4.all = 0;
  PieCtrlRegs.PIEIFR5.all = 0;
  PieCtrlRegs.PIEIFR6.all = 0;
  PieCtrlRegs.PIEIFR7.all = 0;
  PieCtrlRegs.PIEIFR8.all = 0;
  PieCtrlRegs.PIEIFR9.all = 0;
  PieCtrlRegs.PIEIFR10.all = 0;
  PieCtrlRegs.PIEIFR11.all = 0;
  PieCtrlRegs.PIEIFR12.all = 0;
}

void Init_can(void)
{
  Init_can_module();                // Konfiguriere CANB

  // Um die CAN-Weiterleitung abzuwickeln: Für jeden CAN jeweils zwei Mailboxen für RX mit 2er-FIFO und 2x vier Mailboxen für TX

  // TX-Boxen für alle Sondernachrichten, werden dynamisch verwaltet mit Sowohl ID, Länge und bis zu 8 Byte Daten
    Setup_can_obj(1, 1, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)
    Setup_can_obj(1, 2, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)
    Setup_can_obj(1, 3, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)
    Setup_can_obj(1, 4, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)

  // TX-Box für Standardnachrichten (16|16), ID wird dynamisch verwaltet, Länge ist immer 2 Byte und 16bit-ID
  Setup_can_obj(1, 5, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)
  Setup_can_obj(1, 6, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)
  Setup_can_obj(1, 7, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)
  Setup_can_obj(1, 8, 0x00000000, 1, 2, 0x00000000, 0x01); // Flags: 0b00000001 (0,0,0,0,0,0,0,single message)

  // RX-Box CAN-B, FiFo-Tiefe 2, Akzeptiert alle Nachrichten mit Extended-ID, MEssage-Objects 9 + 10
  Setup_can_obj(1, 9, 0x00009FFF, 0, 2, 0x80000000, 0x28); // Flags: 0b00001000 (0,0,keine Maske,0,Rx Int,0,0,not last of FIFO)
  Setup_can_obj(1, 10, 0x00009FFF, 0, 2, 0x80000000, 0x29); // Flags: 0b00001001 (0,0, keine Maske,0,Rx Int,0,0, last of FIFO)

  EALLOW;

  CanaRegs.CAN_GLB_INT_CLR.bit.INT0_FLG_CLR = 1;

  CanaRegs.CAN_GLB_INT_EN.bit.GLBINT0_EN = 1; // Enable INT0 auf Can A

//  PieCtrlRegs.PIEIER9.all = 0x12; // Enable Int7 in PIEIER Gruppe 9 -> CAN B 0
//
//  IER |= M_INT9;                  // Interrupts Gruppe 9 zur CPU zulassen
}

void Init_EPwm(void)
{
    EALLOW;

// ePWM1
    // Event trigger
    // Interrupt
    EPwm1Regs.ETSEL.bit.INTEN = 1;      // Enable EPWM1_INT generation
    EPwm1Regs.ETSEL.bit.INTSEL = 0x3;    // Enable event time-base counter equal to zero or period (TBCTR= 0x00 or TBCTR = TBPRD). This mode is useful in up-down countmode. |S.1967
    EPwm1Regs.ETPS.bit.INTPRD  = 1;     //Generate an interrupt on the first event INTCNT = 01

    // Event Trigger for ADC
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;        // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 0x3;      // 011: Enable event time-base counter equal to zero or period (TBCTR = 0x00 or TBCTR = TBPRD). This mode is useful in up-down count mode.
    EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST;   // Generate pulse on 1st event |S.1969
    //
    // Setup TBCLK
    //

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up-down
    EPwm1Regs.TBPRD = EPWM1_PERIOD;                     // Set timer period
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;             // Disable phase loading
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;                 // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                           // Clear counter
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0x00;               // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = 0x00;                  // durch 1 geteilt

    // Wichtiges Bit für Debbunging wenn Prozesser angehalten wird

    EPwm1Regs.TBCTL.bit.FREE_SOFT = 0x11;               // These bits select the behavior of the ePWM time-base counter during emulation events, FREE-RUN |S.1888
    //
    // Setup shadow register load on PWM PERIOD, konfiguriert wann der neue Wert für das CMP Register übernommen wird
    //
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;    // Neuer Wert wird beim erreichen von PRD übernommen aus Shadow Regiser übernommen
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Neue Werte von CPU werden vor übernahme in Shadow Register geladen
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;    // Für CMPB
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;     // Für CMPB
    EPwm1Regs.CMPA.bit.CMPA = 0;     // Compare Wert am Aanfang auf Null
    EPwm1Regs.CMPB.bit.CMPB = 0;     // CMPB für SOC -> Wandlungen dauern ca. 5µs (4 (Wandlungen) * 25 (AD-Fenster) *  50ns (ADC Wandlungsfrequenz))
    //
    // Set Compare values  S.1924 !WICHTIG!
    //
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;              // Action When TBCTR = 0, 10: Set: force EPWMxA output high.
    EPwm1Regs.AQCTLA.bit.PRD = AQ_CLEAR;            // Action When TBCTR = TBPRD, 01: Clear: force EPWMxA output low.
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // Action When TBCTR = CMPA on Up Count, 01: Clear: force EPWMxA output low.
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;              // Action When TBCTR = CMPA on Down Count,  10: Set: force EPWMxA output high.
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;             // Action When TBCTR = 0, 01: Clear: force EPWMxA output low.
    EPwm1Regs.AQCTLB.bit.PRD = AQ_SET;              // Action When TBCTR = TBPRD, 10: Set: force EPWMxA output high.
    EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;              // Action When TBCTR = CMPA on Up Count, 10: Set: force EPWMxA output high.
    EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;            // Action When TBCTR = CMPA on Down Count, 01: Clear: force EPWMxA output low.

    //
    // Dead Band Operating Modes
    //
    EPwm1Regs.DBCTL.bit.HALFCYCLE = 0;              // Dead Band counters are clocked at TBCLK*2
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;          // EPWM7A is the source for both FED and RED
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;       // Active high complementary(AHC). EPWM1B ist invertiert und schaltet oberen Transistor
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // both RED and FED active
    EPwm1Regs.DBRED.bit.DBRED = 100;                 // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register |S.1933, S.1814
    EPwm1Regs.DBFED.bit.DBFED = 100;                 // Dead-Band Generator Falling Edge Delay High Resolution Mirror Register |S.1935

    EPwm1Regs.DBCTL.bit.DEDB_MODE = 0;
    EPwm1Regs.DBCTL.bit.OUTSWAP = 0x00;
    //
    // Trip- Zone
    //
    EPwm1Regs.TZSEL.bit.OSHT1 = TZ_ENABLE;   // Enable TZ1 as one-shot trip
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;  // Set TZA
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;  // Set TZB




}

void Init_pga(void)
{
    EALLOW;

    Pga1Regs.PGACTL.bit.GAIN = 0;
    Pga1Regs.PGACTL.bit.FILTRESSEL = 0;
    Pga1Regs.PGACTL.bit.PGAEN = 1;

//    Pga2Regs.PGACTL.bit.GAIN = 0;
//    Pga2Regs.PGACTL.bit.FILTRESSEL = 0;
//    Pga2Regs.PGACTL.bit.PGAEN = 1;
//
//    Pga3Regs.PGACTL.bit.GAIN = 0;
//    Pga3Regs.PGACTL.bit.FILTRESSEL = 0;
//    Pga3Regs.PGACTL.bit.PGAEN = 1;

    Pga4Regs.PGACTL.bit.GAIN = 1;
    Pga4Regs.PGACTL.bit.FILTRESSEL = 0;
    Pga4Regs.PGACTL.bit.PGAEN = 1;

//    Pga5Regs.PGACTL.bit.GAIN = 0;
//    Pga5Regs.PGACTL.bit.FILTRESSEL = 0;
//    Pga5Regs.PGACTL.bit.PGAEN = 1;
//
//    Pga6Regs.PGACTL.bit.GAIN = 0;
//    Pga6Regs.PGACTL.bit.FILTRESSEL = 0;
//    Pga6Regs.PGACTL.bit.PGAEN = 1;

    EDIS;

}


void Setup_adc(void)
{
  EALLOW;                                           // Enable full writing access for protected CPU Registers

  // Analog Subsystem
  AnalogSubsysRegs.ANAREFPP.bit.ANAREFBDIS = 1;     // Analoge Referenz B disabled
  AnalogSubsysRegs.ANAREFPP.bit.ANAREFCDIS = 1;     // Analoge Referenz C disabled (an B)
  AnalogSubsysRegs.TSNSCTL.bit.ENABLE = 1;          // Temperature Sensor eingeschaltet

  AnalogSubsysRegs.ANAREFCTL.all = 0;               // Interne 3.3V (1.65V) Referenz für alle ADC-Module

  AnalogSubsysRegs.DCDCCTL.bit.DCDCEN = 0;          // Internen DCDC-Schaltregler abschalten

  EDIS;



  SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
  SetVREF(ADC_ADCB, ADC_INTERNAL, ADC_VREF3P3);
  SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);

  EALLOW;                                           // Enable full writing access for protected CPU Registers, SetVREF function reset the access to protected registers

  // Konfiguration Abtastrate

  // AD-Wandlermodul A
  AdcaRegs.ADCCTL2.bit.PRESCALE = 8;    // SYSCLK / 5 = 20MHz
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;    // Power Up A, All analog circuitry inside the core is powered up | S.1499

  // AD-Wandlermodul B
  AdcbRegs.ADCCTL2.bit.PRESCALE = 8;    // SYSCLK / 5 = 20MHz
  AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;    // Power Up B, All analog circuitry inside the core is powered up | S.1499

  // AD-Wandlermodul C
  AdccRegs.ADCCTL2.bit.PRESCALE = 8;    // SYSCLK / 5 = 20MHz
  AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;    // Power Up C, All analog circuitry inside the core is powered up | S.1499

  // Konfiguration ADC Register
  //
  // SOC -> start of conversation, |S.1445   WICHTIG!


  // ADC Timings S.1463

//Spannungsmessungen DC

    // A6,  Voltage DC-
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 6;     // SOC0 wandelt in ADCINA6, Kanal der gewandelt wird
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 4;     // SOC0 verwendet eine Abtastdauer von 20 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534, ePWM1, ADCSOCA

    // B6, Voltage DC+
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 6;     // SOC0 wandelt in ADCINA6, Kanal der gewandelt wird
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = 4;     // SOC0 verwendet eine Abtastdauer von 20 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534

    // C14, Voltage DC++
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 14;    // SOC0 wandelt in ADCINA6, Kanal der gewandelt wird
    AdccRegs.ADCSOC0CTL.bit.ACQPS = 4;     // SOC0 verwendet eine Abtastdauer von 20 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534


//Strommessungen

    // C1, Current DC++
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 1;     // SOC1 wandelt in ADCINA6, Kanal der gewandelt wird
    AdccRegs.ADCSOC1CTL.bit.ACQPS = 24;     // SOC1 verwendet eine Abtastdauer von 25 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534

    // A5, Current OUT
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 5;      // SOC1 wandelt in ADCINA6, Kanal der gewandelt wird
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 24;     // SOC1 verwendet eine Abtastdauer von 25 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5;    // Trigger Source Select |S.1534

//Spannungsmessung AC

    // B0, Voltage OUT
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 0;     // SOC2 wandelt in ADCINA6, Kanal der gewandelt wird
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = 9;     // SOC2 verwendet eine Abtastdauer von 25 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534


//Interne  Spannungen

    // C2, Vref DC-
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 2;     // SOC2 wandelt in ADCINA6, Kanal der gewandelt wird
    AdccRegs.ADCSOC2CTL.bit.ACQPS = 24;     // SOC2 verwendet eine Abtastdauer von 25 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534

// PGA Pins für Stromsensoren


//    AdccRegs.ADCSOC7CTL.bit.CHSEL = 9;     // SOC7 wandelt in ADCINB11, PGA4_OUT |S.1616
//    AdccRegs.ADCSOC7CTL.bit.ACQPS = 24;     // SOC2 verwendet eine Abtastdauer von 25 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
//    AdccRegs.ADCSOC7CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534
//
//
//    AdcbRegs.ADCSOC7CTL.bit.CHSEL = 2;     // SOC2 wandelt in ADCINA6, Kanal der gewandelt wird
//    AdcbRegs.ADCSOC7CTL.bit.ACQPS = 24;     // SOC2 verwendet eine Abtastdauer von 25 SYSCLK-Zyklen, Erfassungsfenster, Abtastdauer
//    AdcbRegs.ADCSOC7CTL.bit.TRIGSEL = 5;   // Trigger Source Select |S.1534
//


    EDIS; // Disable access to protected registers

    DELAY_US(1000);



}







