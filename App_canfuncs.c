#include "App_definitions.h"

#pragma CODE_SECTION(Setup_can_obj, ".TI.ramfunc");
#pragma CODE_SECTION(Send_can_a, ".TI.ramfunc");
#pragma CODE_SECTION(Send_can_a_16, ".TI.ramfunc");
#pragma CODE_SECTION(Read_can_a, ".TI.ramfunc");


void Init_can_module(void)
{
  if (!(CanaRegs.CAN_BTR.bit.BRP == 24))  // CAN A nur konfigurieren, wenn noch nicht im Bootloader geschehen (Debugging)
  {
    CanaRegs.CAN_CTL.bit.Init = 1;                        // Initialisierungsmodus
    CanaRegs.CAN_CTL.bit.PMD = 5;                         // Parity aus

    CanaRegs.CAN_RAM_INIT.all = 0x1A;                     // Start RAM Initialization with key

    while (!CanaRegs.CAN_RAM_INIT.bit.RAM_INIT_DONE) {}   // Warten bis Ram-Init abgeschlossen

    EALLOW;
    CanaRegs.CAN_CTL.bit.SWR = 1;                         // CAN-Module in Ausgangszustand versetzen
    EDIS;
    F28x_usDelay(1);                                      // Kurz warten
    CanaRegs.CAN_CTL.bit.CCE = 1;                         // Schreibzugriff auf Konfigurationregister zulassen

    CanaRegs.CAN_BTR.bit.BRP = 24;                        // Timingeinstellungen setzen
    CanaRegs.CAN_BTR.bit.SJW =  3;
    CanaRegs.CAN_BTR.bit.TSEG1 = 8;
    CanaRegs.CAN_BTR.bit.TSEG2 = 5;
    CanaRegs.CAN_BTR.bit.BRPE = 0;

    CanaRegs.CAN_CTL.bit.IE0 = 1;                         // INT0 einschalten
    CanaRegs.CAN_CTL.bit.CCE = 0;                         // Schreibzugriff auf Konfigurationregister verbieten
    CanaRegs.CAN_CTL.bit.Init = 0;                        // Initialisierungsmodus beenden

  }

  CanaRegs.CAN_CTL.bit.ABO = 1;                           // Auto-Bus-On einschalten
//  CanaRegs.CAN_ABOTR = 25000000;                          // 250ms Verzögerung
  CanaRegs.CAN_ABOTR = 100000000;
}


void Setup_can_obj(short int CAN, unsigned short int MOBJECTID, unsigned long int ID, unsigned short int DIRECTION, unsigned short int LENGTH, unsigned long int MASKE, unsigned short int FLAGS)
{                     // A oder B   , Message-Objekt 1-32, 29bit Identifier, Richtung: RX(0) TX(1), remote, Datenlänge 0-8 ,                      ggf. Maske              , Flags: Standard 1(EOB))
  // Diese Funktion sieht immer eine extended-ID vor, Es werden keine "außergewöhnlichen" Nachrichtentypen erzeugt
  unsigned long int base, arb, control, command;

  // Auswählen des jeweiligen CAN-Moduls (0=A, 1=B)
  if (!CAN) base = 0x00048000U; // Basisadresse CAN A
  else      base = 0x0004A000U; // Basisadresse CAN B


  // Zusammenstellen des Message-RAM-Offsets 0x0004 (MXtd, MDir, Rsvd, Mask)


  // Zusammenstellen des Message-RAM-Offsets 0x0008 (Extended, Direction, Identifier)
  if (DIRECTION)  arb = 0xE0000000U | (ID & 0x1FFFFFFF);   // oberstes nibble: 0b1110 - MsgVal, xtd, dir, id[29] (dir = 1 = TX) + Identifier
  else            arb = 0xC0000000U | (ID & 0x1FFFFFFF);   // oberstes nibble: 0b1100 - MsgVal, xtd, dir, id[29] (dir = 0 = RX) + Identifier
    // ggf. später noch remote messages einfügen

  // Zusammenstellen des Message-RAM-Offsets 0x000C (Rsv[17], MsgLst, Rsvd,UMask, TxIE, RxIE, RmtEn,Rsvd,EOB, Rsv[3], DLC[4])
  control = LENGTH;       // Datenlänge
  control |= (FLAGS<<7);  // Flags werden 1:1 übernommen und nur auf die richtige Position geshiftet


  // Zusammenstellen des Kommandas an IF1 zur Übertragung der Registerinhalte in den Message-RAM
  // Rsvd[8], Dir, Mask, Arb, Control, ClrIntPnd, TXRQST, DATA_A, DATA_B, Busy, DMAactive, Rsvd[6], Msg_Num[8]
  // Schreiben von IF ins RAM aller Einstellungen und auch Daten
  // 0b0000 0000 1111 0011 0000 0000 0000 0000 + ID
  command = 0x00F30000 + MOBJECTID;

  while (HWREGH(base + 0x100U) & 0x8000U) ; // Warten bis BUSY-bit ggf. wieder 0 ist

  HWREG_BP(base + 0x104U) = MASKE;
  HWREG_BP(base + 0x108U) = arb;
  HWREG_BP(base + 0x10CU) = control;
  HWREG_BP(base + 0x110U) = 0;          // Daten 3-0
  HWREG_BP(base + 0x114U) = 0;          // Daten 7-4

  HWREG_BP(base + 0x100U) = command;    // Befehl geben, um Daten in den Message-RAM zu übernehmen
  }


// Versenden von Nachrichten auf CAN A
void Send_can_a(mboxdata *DATA)
{
  unsigned long int checkfree;

  checkfree = HWREG_BP(0x00048088);                                 // Lese CANXRQ21 (Offset 0x88)

  HWREG_BP(0x00048128U) = 0xE0000000U | DATA->ident;                // ARB: oberstes nibble: 0b1110 - MsgVal, xtd, dir, id[29] (dir = 1 = TX) + Identifier nach IF2
  HWREG_BP(0x00048130U) = DATA->DATA_A.all;                         // Daten 3-0 nach IF2
  HWREG_BP(0x00048134U) = DATA->DATA_B.all;                         // Daten 7-4 nach IF2
  HWREG_BP(0x0004812CU) = 0x00000080 + DATA->length;                // Controlregister mit neuer Datenlänge nach IF2, es ist immer EOB gesetzt, alle anderen Flags sind aus

  // Wähle nächstmögliches freies Messageobject
  if      (!(checkfree & 0x0001)) HWREG_BP(0x00048120U) = 0xB70001; // Lade ARB, CTRL, DATA_A, DATA_B + TX_req in MoBj. 1
  else if (!(checkfree & 0x0002)) HWREG_BP(0x00048120U) = 0xB70002; // Lade ARB, CTRL, DATA_A, DATA_B + TX_req in MoBj. 2
  else if (!(checkfree & 0x0004)) HWREG_BP(0x00048120U) = 0xB70003; // Lade ARB, CTRL, DATA_A, DATA_B + TX_req in MoBj. 3
  else if (!(checkfree & 0x0008)) HWREG_BP(0x00048120U) = 0xB70004; // Lade ARB, CTRL, DATA_A, DATA_B + TX_req in MoBj. 4
 // else GLOBALS.FEHLER.BIT.can = 1;
}


// Versenden von Standard Nachrichten auf CAN A
void Send_can_a_16(mboxdata *DATA)
{
  unsigned long int checkfree;
  checkfree = HWREG_BP(0x00048088);                                 // Lese CANXRQ21 (Offset 0x88)

  HWREG_BP(0x00048128U) = 0xE0000000U + DATA->ident;                // ARB: oberstes nibble: 0b1110 - MsgVal, xtd, dir, id[29] (dir = 1 = TX) + Identifier nach IF2
  HWREG_BP(0x00048130U) = DATA->DATA_A.all ;                        // Daten 3-0 nach IF2

  // Wähle nächstmögliches freies Messageobject
  if      (!(checkfree & 0x0010)) HWREG_BP(0x00048120U) = 0xA60005; // Lade ARB, DATA_A + TX_req in MoBj. 5
  else if (!(checkfree & 0x0020)) HWREG_BP(0x00048120U) = 0xA60006; // Lade ARB, DATA_A + TX_req in MoBj. 6
  else if (!(checkfree & 0x0040)) HWREG_BP(0x00048120U) = 0xA60007; // Lade ARB, DATA_A + TX_req in MoBj. 7
  else if (!(checkfree & 0x0080)) HWREG_BP(0x00048120U) = 0xA60008; // Lade ARB, DATA_A + TX_req in MoBj. 8
 // else GLOBALS.FEHLER.BIT.can = 1;

}

void Read_can_a(void)
{
  mboxdata DATA;
  unsigned long int control;
  unsigned int  i;

  for (i = 9; i < 11; i++)
  {
    // komplettes Messageobjekt 9 bzw. 10 auslesen nach IF1, dabei gleichzeitig NewDat und IntPnd des Messagobject zurücksetzen
    HWREG_BP(0x00048100U) = 0x007F0000 + i;

    while(HWREGH(0x00048100U) & 0x8000) {}                    // Warten bis Übertragung abgeschlossen (Busy-Bit = 0)

    control = HWREG_BP(0x0004810CU);                          // Controlregister aus IF1 auslesen
    if (control & 0x00008000)                                 // Prüfung ob neue Daten in Mbox, wenn ja -> auswerten
    {
      DATA.ident      =  HWREG_BP(0x00048108U) & 0x1FFFFFFF;  // Identifier auslesen
      DATA.length     =  control & 0x0000000F;                // Datenlänge auslesen
      DATA.DATA_A.all =  HWREG_BP(0x00048110U);               // Daten 0-3 auslesen
      DATA.DATA_B.all =  HWREG_BP(0x00048114U);               // Daten 4-7 auslesen

      CANCOMM.activity = 1;                                   // CAN-Senden bis zum nächsten Reset zulassen, wenn mindestens eine Nachricht empfangen wurde
      CanaRegs.CAN_CTL.bit.DAR = 0;                           // Automatisch Wiederholung wieder einschalten
      Process_can_data(&DATA);                                // Auswerteroutine aufrufen
    }
  }
}





