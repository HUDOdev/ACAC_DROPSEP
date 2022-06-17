#include "App_definitions.h"

#pragma CODE_SECTION(Send_boot_status, ".TI.ramfunc");
#pragma CODE_SECTION(Send_fwdate, ".TI.ramfunc");
#pragma CODE_SECTION(Bl_message, ".TI.ramfunc");
#pragma DATA_SECTION(SWFLASHINFO, "swinfo");	// Info über Applikation im Flash
#pragma DATA_SECTION(flag, "global");					// Flag im RAM

unsigned short int flag;

// Die folgende Zeile muss bei neuer FW-Version angepasst werden. Das dritte Item enthält den spezifischen Hardwarecode
const struct Swinfo SWFLASHINFO = {0x2000 + ((((YEAR-2000)/10) * 16) + ((YEAR-2000)%10)), ((((MONTH/10) * 16) + (MONTH%10))<<8)+(((DAY/10) * 16) + (DAY%10)), 107, 0xFFFF};


void Send_fwdate(void)
{
  mboxdata data_out;

  data_out.DATA_A.word.LOW_WORD = GLOBALS.hwid;
  data_out.DATA_A.word.HI_WORD =  ((SWFLASHINFO.hwcode)<<8) + ((SWFLASHINFO.hwcode)>>8); // Endianess auf altes Format drehen
  data_out.DATA_B.byte.BYTE4 = SWFLASHINFO.swmd & 0x00FF;
  data_out.DATA_B.byte.BYTE5= (SWFLASHINFO.swmd & 0xFF00) >> 8;
  data_out.DATA_B.word.HI_WORD=  ((SWFLASHINFO.swyear)<<8) + ((SWFLASHINFO.swyear)>>8); // Endianess auf altes Format drehen
  data_out.ident = 0x1FFFFFFB;
  data_out.length = 8;
  Send_can_a(&data_out);
}

void Send_boot_status(void)
{
  mboxdata data_out;
  flag = 0xA5A5;

  data_out.DATA_A.word.LOW_WORD = GLOBALS.hwid;
  data_out.DATA_A.word.HI_WORD =  ((SWFLASHINFO.hwcode)<<8) + ((SWFLASHINFO.hwcode)>>8); // Endianess auf altes Format drehen
  data_out.DATA_B.byte.BYTE4 = 0xFF;
  data_out.DATA_B.byte.BYTE5 = 0xFF;
  data_out.DATA_B.byte.BYTE6 = 0xFF;
  data_out.DATA_B.byte.BYTE7 = 0;
  data_out.ident = 0x1FFFFFFE;
  data_out.length = 8;
  Send_can_a(&data_out);
}

void Bl_message(mboxdata *DATA)
{
  if (DATA->DATA_A.word.HI_WORD == 0xFFFF) // Bei Busabfrage
  {
    CANCOMM.send_delay = 1; // Verzögerung um 10ms
  }
  else if (DATA->DATA_A.word.HI_WORD == 0xFEFF)  CANCOMM.can_silence = 1; // Silence CAN
  else if (DATA->DATA_A.word.HI_WORD == 0xFDFF)  CANCOMM.can_silence = 0; // "Un"-Silence CAN

  // Wechsel in Bootloader
  else if ( (DATA->DATA_A.word.LOW_WORD == GLOBALS.hwid) && (DATA->DATA_A.word.HI_WORD == ((SWFLASHINFO.hwcode)<<8) + ((SWFLASHINFO.hwcode)>>8))) // nur bei passender Adresse und passendem HW-Code
  {
      // hier Code einfügen zum Wechsel in sicheren Zustand !

      EALLOW;
      DINT;

      EALLOW;
      IER = 0x0000;    // Disable CPU interrupts and clear all CPU interrupt flags
      IFR = 0x0000;



      flag = 0x5A5A;
      EALLOW;
      WdRegs.WDCR.all = 0;  // Watchdog-Reset

      asm(" RPT#255||NOP");

  }
}

