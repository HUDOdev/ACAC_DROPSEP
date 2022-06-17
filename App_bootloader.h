/* Filename: bootloader.h */
#ifndef BOOT_INCLUDED
#define BOOT_INCLUDED




void Send_fwdate(void);
void Send_boot_status(void);
void Bl_message(mboxdata *DATA);

extern unsigned short int flag;

struct Swinfo
{
	unsigned short int swyear;
	unsigned short int swmd;
	unsigned short int hwcode;
	unsigned short int reserve;
};

extern const struct Swinfo SWFLASHINFO;


#endif
