#ifndef FUNCS_INCLUDED
#define FUNCS_INCLUDED



void Regelung(void);
void Ramp(float*,float*);
float Duty_cycle(float*);
unsigned short int EPwm1_cmp_calc(float*);
float Current_calc(float*, float*);
float Voltage_calc(float, float, float);
float IIR_filter(float,float,float*);
void ADC_calibration(void);





#endif
