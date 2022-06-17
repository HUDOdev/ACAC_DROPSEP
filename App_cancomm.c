/* Filename: cancomm.c */

#include "App_definitions.h"

#pragma CODE_SECTION(Process_can_data, ".TI.ramfunc");


//  In diesem Programmteil wird die Funktion zur Verarbeitung der empfangenen CAN-Nachrichten aufgerufen
//  die Funktionen Send_status ist wie der Name schon sagt zum Senden der Autozustand an der Steuerelktronik
//  der Leistungmesser.


void Process_can_data(mboxdata *DATA)  //
{

  // Nachricht u.a. zum Wechseln in Bootloader (DLC = 4)
  if (DATA->ident == 0x1FFFFFFF)  Bl_message(DATA);
  else
  {
//      verarbeitung_can_msg(DATA);   // Aufruf der Funktion zur
                                // Verarbeitung der empfangenen Nachrichten
  }
}

void Send_status(void)          // Funktion zum Senden der Nachrichten
{
//    mboxdata DATA;
//    //unsigned short int r_fzg;
//
//    if      (ADC.r_cp > 65535) r_fzg = 65535;
//    else if (ADC.r_cp <     0) r_fzg =     0;
//    else                       r_fzg = (unsigned short int) ADC.r_cp;


    // Zustand der Wallbox (Inbetriebnahme)
    //DATA.DATA_A.byte.BYTE0 = GLOBALS.fzgstatus;
    //DATA.DATA_A.byte.BYTE1 = GLOBALS.prioload;
    //DATA.DATA_A.word.HI_WORD = r_fzg;
    //DATA.DATA_B.word.LOW_WORD  = (unsigned short int) (GLOBALS.strom_soll * 100);  // 10mA / LSB
//    DATA.DATA_B.word.HI_WORD = (unsigned short int) GLOBALS.duty;  // 1% / LSB
//
//    DATA.ident = 0x010 + (GLOBALS.hwid>>8); // Identifier zur Erkennung der Sender der Nachricht
//    DATA.length = 8;                        // Länge der Nachricht
//    Send_can_a(&DATA);                      // Aufruf der Funktion zur Sendung der Nachricht


}

//void verarbeitung_can_msg(mboxdata *DATA)     // Funktion zur Verarbeitung der empfangenen Nachrichten
//{
//  if (DATA->ident == 0x7F6)
//  {
//   // GLOBALS.strom_soll = DATA->DATA_A.word.LOW_WORD;
//    GLOBALS.timer_can = 5000; // 5s timeout
//  }
//}
