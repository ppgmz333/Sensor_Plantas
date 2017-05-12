/*
 * File:   main.c
 * Author: Patricio Gomez
 *
 * Created on 22 de abril de 2017, 05:01 PM
 */

#include "config.h"
#include "ADC.h"
#include "UART.h"
#include "DHT11_driver.h"
#include "Secondary_Data_Types_Definitions.h"
#include "xc.h"
#define FCY 20000000UL
#include "libpic30.h"

#define ADC_VOLT(x)             (x*3.3)/(0xFFC0)

#define LM35_TEMP(x)            (ADC_VOLT(x)/0.45)*(100)
#define LDR_LUX(x)              (ADC_VOLT(x))
#define YL69_HUM(x)             (ADC_VOLT(x))

#define AN0_LM35                0
#define AN1_LDR                 1
#define AN4_YL69                4

#define LM35_INDEX              0
#define LDR_INDEX               1
#define YL69_INDEX              2

Sensor_Data_Type Sensor_Data[3] = {
    {'T', 0.0, "000.00\0"},{'L', 0.0, "000.00\0"},{'S', 0.0, "000.00\0"}
};

DHT11_Data_Type DHT11_Data = {
    'D', 0, 0, 0.0, 0.0, "000.00\0", "000.00\0"
};

int main(void) {
      
    UART_init();
    ADC_init();

    uint8 s;
    
    for (;;) {

        UART_printString("Que show");

        Sensor_Data[LM35_INDEX].ADC_Sensor_Value = LM35_TEMP(ADC_Read_ANx(AN0_LM35));
        
        Sensor_Data[LDR_INDEX].ADC_Sensor_Value = LDR_LUX(ADC_Read_ANx(AN1_LDR));
      
        Sensor_Data[YL69_INDEX].ADC_Sensor_Value = YL69_HUM(ADC_Read_ANx(AN4_YL69));

        Float_To_String(Sensor_Data[LM35_INDEX].ADC_Sensor_Value, Sensor_Data[LM35_INDEX].String_Sensor_Value);
                
        UART_printString(&Sensor_Data[LM35_INDEX].String_Sensor_Value[0]);
        
        Float_To_String(Sensor_Data[LDR_INDEX].ADC_Sensor_Value, Sensor_Data[LDR_INDEX].String_Sensor_Value);
                
        UART_printString(&Sensor_Data[LDR_INDEX].String_Sensor_Value[0]);
        
        Float_To_String(Sensor_Data[YL69_INDEX].ADC_Sensor_Value, Sensor_Data[YL69_INDEX].String_Sensor_Value);
              
        UART_printString(&Sensor_Data[YL69_INDEX].String_Sensor_Value[0]);
        
        s = DHT11_Read_uint16(&DHT11_Data.Temperature_uint16, &DHT11_Data.Humidity_uint16);
        
        Float_To_String(DHT11_Data.Temperature_uint16, DHT11_Data.String_Temperaure_Value);
              
        UART_printString(&DHT11_Data.String_Temperaure_Value[0]);
                UART_printString("\n\r");

        Float_To_String(DHT11_Data.Humidity_uint16, DHT11_Data.String_Humidity_Value);
              
        UART_printString(&DHT11_Data.String_Humidity_Value[0]);
                UART_printString("\n\r");
                
                
                
        __delay_ms(1000);
        __delay_ms(1000);
    }

    return 0;
}
