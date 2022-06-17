#include "App_definitions.h"
#include "App_structs.h"


//#############################################
// Augelagerte Funktionen
//#############################################



//#
// Funktion zur Regelung des Tiefsetzstellers
//#
// Output:
// Input:

void Regelung(void)
{

    float temp;

    GLOBALS.vo_diff = TARGET_VALUES.VO_DC_PLUS_PLUS - GLOBALS.vo_dc_plus_plus; // Differenz Spannung DC++

    GLOBALS.vo_diff_sum += GLOBALS.vo_diff;

    temp = CONTROL_CONST.VO_KP * GLOBALS.vo_diff + CONTROL_CONST.VO_KI * CONTROL_CONST.SAMP_TIME * GLOBALS.vo_diff_sum;    // PI-Regler Spannung  -> Stromwert als Ausgabewert


    if(temp > CONTROL_CONST.CUR_BUCK_MAX)       // Limitierung Strom Maximalwert
    {
        temp = CONTROL_CONST.CUR_BUCK_MAX;
    }

    else if(temp < CONTROL_CONST.CUR_BUCK_MIN)  // Limitierung Strom Minimalwert
    {
        temp = CONTROL_CONST.CUR_BUCK_MIN;
    }

    if(GLOBALS.vo_diff < 1)
    {
        GLOBALS.vo_diff_sum = 0;
    }


    GLOBALS.cur_diff = temp - GLOBALS.cur_buck ; // Differenz Strom Buck Converter

    GLOBALS.cur_diff_sum += GLOBALS.cur_diff;

    temp = CONTROL_CONST.CUR_KP * GLOBALS.cur_diff + CONTROL_CONST.CUR_KI * CONTROL_CONST.SAMP_TIME * GLOBALS.cur_diff_sum;    // PI-Regler Strom  -> Spaannungswert als Ausgabewert



    if(temp > CONTROL_CONST.VO_DC_PLUS_PLUS_MAX)    // Limitierung Spannung
    {
        temp = CONTROL_CONST.VO_DC_PLUS_PLUS_MAX;
    }

    else if(temp < CONTROL_CONST.VO_DC_PLUS_PLUS_MIN)
    {
        temp = CONTROL_CONST.VO_DC_PLUS_PLUS_MIN;
    }

    GLOBALS.epwm1_duty = temp/CONTROL_CONST.VO_DC_PLUS_PLUS_MAX; // Berechnung Duty Cycle

}

//#
// Rampenfunktion
//#

void Ramp(float *target_value, float *instant_value)
{
    if(*target_value > (0.9 * VO_DC_PLUS_MAX))      // Limitierung falls Input über max. Spannung
    {
        *target_value = 0.9 * VO_DC_PLUS_MAX;
    }



    if (*instant_value < *target_value)             // Rampe hoch fahren
    {
        *instant_value += 0.0001;
    }
    else if(*instant_value > *target_value)         // Rampe runter fahren
    {
        *instant_value -= 0.0001;
    }



}


//#
// Duty Cycle Berechnung
//#

float Duty_cycle(float *target_value)
{
    float temp;

    temp = *target_value / VO_DC_PLUS_MAX;

    if(temp > 0.9)      // Abfrage ob Duty Cycle größer 0.9 -> wegen Bootsprap Schaltung
    {
        temp = 0.9;
    }
    return temp;
}


//#
// Funktion zur Berechnung des Compare Wertes für die PWM aus einem zuvor berechneten Duty Cycle
//#
// Output: CMP Wert für ePWM Register
// Input: Duty Cycle

unsigned short int EPwm1_cmp_calc(float *duty_cycle)
{
        float temp;


        temp = EPWM1_PERIOD * *duty_cycle;     // Berechnung CMP Wert

        temp = (unsigned short int)temp; // Type Casting von Fließkommazahl zu Ganzzahl


        if(temp > EPWM1_MAX_CMP)             // Limitierung CMP Wert nach oben
        {
            temp = EPWM1_MAX_CMP;
        }

        else if(temp < EPWM1_MIN_CMP)        // Limitierung CMP Wert nach unten
        {
            temp = 0;
        }

            return temp;

}



//void Offset_adjustment(void)                        // Erfassung Offset Werte von OP und Stromsensoren
//{
//    OFFSETS.CUR_BUCK = Current_calc(ADC.IN4,0.0);
//    OFFSETS.CUR_OUT = Current_calc(ADC.IN5,0.0);
//    OFFSETS.VO_DC_PLUS_PLUS = Voltage_calc(ADC.IN2,0.0);
//    OFFSETS.VO_OUT = Voltage_calc(ADC.IN6,0);
//}

// Berechnung Strom

float Current_calc(float *adc_value_current, float *adc_cur_offset)
{
    float temp;


    temp = (*adc_value_current - *adc_cur_offset) * CONVERSION_FACTORS.CUR_SENSOR;

    return temp;

}

float Voltage_calc(float adc_value_voltage, float adc_vo_offset, float conversion_factor)
{
    float temp;


    temp = (adc_value_voltage * conversion_factor) - adc_vo_offset;


    return temp;
}



//Tiefpass IIR-Filter für ADC Werte
//
// https://de.mathworks.com/help/mcb/ref/iirfilter.html?searchHighlight=IIR%20Filter&s_tid=srchtitle_IIR%2520Filter_6

//Output: Gefilterter AD-Wert
//Input: Neuer Wert von AD-Wandler, Koeffizient Filterstärke, Pointer zum letzten Wert


float IIR_filter(float newSample, float a, float *oldValue)
{
    float newValue;                                         // Rückgabewert der Funkion

    newValue = a * newSample + (1 - a) * *oldValue;         // Filterung AD-Wert  durch verrechnung mit altem Wert

    *oldValue = newValue;                                   // Letzten Wert für neunen Zyklus speichern

    return newValue;

}
void ADC_calibration(void)
{
    OFFSETS.VO_DC_MINUS = AdcaResultRegs.ADCRESULT0;
    OFFSETS.VO_DC_PLUS_PLUS = AdcbResultRegs.ADCRESULT0;
    OFFSETS.VO_DC_PLUS = AdccResultRegs.ADCRESULT0;

    OFFSETS.CUR_BUCK = AdccResultRegs.ADCRESULT1;
    OFFSETS.CUR_OUT = AdcaResultRegs.ADCRESULT1;

    OFFSETS.VO_OUT = AdcbResultRegs.ADCRESULT2;

}

