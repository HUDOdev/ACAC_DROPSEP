#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED



// CAN-Datenregister mit Einzelzugriffen

struct  CANMDL_WORDS {      // bits  description
   unsigned short int      LOW_WORD:16; // 0:15
   unsigned short int      HI_WORD:16;  // 31:16
};

/* eCAN Message Data Register low (MDR_L) byte definitions */
struct  CANMDL_BYTES {      // bits   description
  unsigned short int      BYTE0:8;     // 31:24
  unsigned short int      BYTE1:8;     // 23:16
  unsigned short int      BYTE2:8;     // 15:8
  unsigned short int      BYTE3:8;     // 7:0
};


/* Allow access to the bit fields or entire register */

union CANMDL_REG {
   unsigned long int      all;
   struct CANMDL_WORDS   word;
   struct CANMDL_BYTES   byte;
};

/* eCAN Message Data Register high  (MDR_H) word definitions */
struct  CANMDH_WORDS {         // bits  description
  unsigned short int      LOW_WORD:16;    // 0:15
  unsigned short int      HI_WORD:16;     // 31:16
};

/* eCAN Message Data Register low (MDR_H) byte definitions */
struct  CANMDH_BYTES {      // bits   description
  unsigned short int      BYTE4:8;     // 63:56
  unsigned short int      BYTE5:8;     // 55:48
  unsigned short int      BYTE6:8;     // 47:40
  unsigned short int      BYTE7:8;     // 39:32
};

/* Allow access to the bit fields or entire register */
union CANMDH_REG {
   unsigned long int       all;
   struct CANMDH_WORDS     word;
   struct CANMDH_BYTES     byte;
};

typedef struct {
  unsigned long int   ident;
  union CANMDL_REG    DATA_A;
  union CANMDH_REG    DATA_B;
  unsigned short int  length;
} mboxdata;


struct Cancomm
{
  unsigned short int send_delay;
  unsigned short int can_silence;
  unsigned short int uid_requested;
  short int can_rr;
  short int delay1000;
  unsigned short int activity;
  short int diagnostic;
};


struct Globals
{
    unsigned short int antibrick;
    unsigned long int hwid;
    unsigned short int timer_250;
    unsigned short int unit_satus;
    unsigned short int pwm;
    unsigned short int timer_can;


    float cur_buck;                         // Istwert Strom Tiefsetzsteller
    float cur_out;                          // Istwert Strom Ausgang
    float vo_dc_plus;                       // Istwert Spannung DC+
    float vo_dc_plus_plus;                  // Istwert Spannung DC++
    float vo_dc_minus;                      // Istwert Spannung DC-
    float vo_out;                           // Istwert Spannung Ausgang
    float vo_2V4;
    float vo_diff;
    float vo_diff_sum;
    float cur_diff;
    float cur_diff_sum;

    float vo_dc_plus_to_dc_minus;
    float vo_dc_plus_plus_to_dc_minus;

    float epwm1_duty;
    float epwm4_duty;
    unsigned short int cmp_value_epwm1;
    unsigned short int cmp_value_epwm4;

    float adc_old_value;
    float adc_new_value;

    float vo_buck_instant_value;
};

// ADC
struct Adc
{
  // analoge Werte von Eingänge
  float IN1;
  float IN2;
  float IN3;
  float IN4;
  float IN5;
  float IN6;
  float IN7;
  float IN8;
  float IN9;
  float IN10;
  float IN11;

  float IN1_old;
  float IN2_old;
  float IN3_old;
  float IN4_old;
  float IN5_old;
  float IN6_old;
  float IN7_old;
  float IN8_old;
  float IN9_old;
  float IN10_old;
  float IN11_old;

  // Digitale Werte von Eingänge
  short int IN1_D;
  short int IN2_D;
  short int IN3_D;
  short int IN4_D;

  short int IN1_D_alt;
  short int IN2_D_alt;
  short int IN3_D_alt;
  short int IN4_D_alt;

    float Rx;
    float PP_DSP;

    float Rges;
    float PWM;
    float CP_DSP;
    float Ux;
    float U_cp;
    float r_cp;

    float R_sum_33;
    float U_33_AD;
    float U_24_AD;
};

// Struktur Offsets

struct Offsets
{
    float CUR_BUCK;
    float CUR_OUT;
    float VO_DC_MINUS;
    float VO_DC_PLUS;
    float VO_DC_PLUS_PLUS;
    float VO_OUT;

};

struct Conversion_factors
{
    float CUR_SENSOR;
    float VO_DC_MINUS;
    float VO_DC_PLUS;
    float VO_DC_PLUS_PLUS;
    float VO_OUT;
};

struct Control_const
{
    float VO_DC_PLUS_PLUS_MAX;
    float CUR_BUCK_MAX;
    float VO_DC_PLUS_PLUS_MIN;
    float CUR_BUCK_MIN;
    float VO_KP;
    float VO_KI;
    float CUR_KP;
    float CUR_KI;
    float SAMP_TIME;
};

struct Target_values
{
    float CUR_BUCK;            // Sollwert Strom Tiefsetzsteller
    float VO_DC_PLUS_PLUS;     // Sollwert Spannung DC++

};







extern struct Cancomm CANCOMM;
extern struct Globals GLOBALS;
extern struct Adc ADC;
extern struct Offsets OFFSETS;
extern struct Conversion_factors CONVERSION_FACTORS;
extern struct Control_const CONTROL_CONST;
extern struct Target_values TARGET_VALUES;



#endif

