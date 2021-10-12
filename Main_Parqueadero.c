// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "FusesParqueadero.h"
#include "LCD.h"
#include "Sensores_De_Presencia.h"
#include "UART.h"
#include "I2C.h"
#include "RtcLib.h"
#include <stdio.h>


#define INPUT 1
#define OUTPUT 0
#define ON 1
#define OFF 0
//PUERTO C
#define CFG_Entrada TRISC0
#define CFG_Salida  TRISC1
#define Entrada     RC0
#define Salida      RC1
//PUERTO D
#define CFG_LED_OCUPADO    TRISD3
#define LED_OCUPADO        RD3
#define CFG_LED_blu    TRISB6
#define LED_blu        RB6

int Conteo = 0;
int resultado = 0;
char dato_rx;
unsigned char Pantalla[20];
unsigned char Disponible[20];
int hora, minutos, segundos, dia, mes, anio;
void Fijar_Datos_Reloj();
void Imprimir_Datos_Reloj();
void main (void){
    Sensores_De_Presencia_Init();
    UART_init();
    printf("BIENVENIDO");
    printf("\n\r\n\rOpciones:\n\r");
    printf("\n \r_ O para ver lugares ocupados.");
    printf("\n \r_ L para ver lugares libres.");
    printf("\n \r_ H para ver la hora actual.");
    printf("\n \r_ F para ver la fecha actual.\n\r");
    __delay_ms(100);
    CFG_Entrada = INPUT;
    CFG_Salida = INPUT;
    CFG_LED_OCUPADO = OUTPUT;
    CFG_LED_blu = OUTPUT;
    I2C_Init(1000000);
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    Conteo = 0;
    Fijar_Datos_Reloj();
    LED_blu = OFF;
    LED_OCUPADO = OFF;
    __delay_ms(10);
    
    while(1){
        
        Leds_De_Sensores();
        __delay_ms(50);
  
        if(Entrada == OUTPUT){
            Conteo = Conteo + 1;
        }
        if(Salida == OUTPUT){
            Conteo = Conteo - 1;
        }
        Lcd_Out(1,1," Parqueadero Cauca ");
        __delay_ms(50);
        
        
        if(Conteo != 6){        
            
             sprintf (Pantalla,"    Ocupado : %1d     ",Conteo);
             Lcd_Out2(2,1,Pantalla);
             resultado = 6 - Conteo;
             sprintf (Disponible,"  Disponible:  %1d    ",resultado);
             Lcd_Out2(3,1,Disponible);
             Lcd_Out(4,1,"--|-|-|--||--|-|-|--");
        }
        
        if ( Conteo < 0){
            Conteo = 0;
        }
       
        if(Conteo >= 6){
                sprintf (Pantalla,"    Ocupado : %1d     ",Conteo);
                Lcd_Out2(2,1,Pantalla);
                resultado = 6 - Conteo;
                sprintf (Disponible,"  Disponible:  %1d    ",resultado);
                Lcd_Out2(3,1,Disponible);
                Lcd_Out(4,1," PARQUEADERO LLENO ");
                Conteo = 6;
             LED_OCUPADO = ON;
         }else {
            LED_OCUPADO = OFF;
         }
        
        //bluetooth   
        dato_rx = UART_read();
        
     
       if((dato_rx == 'O')||(dato_rx == 'o')){
            
           LED_blu = 1;
            printf("\n \rLugares ocupados: %i\n \r",Conteo);
            printf("\n\r");
            Lugares_Ocupados();
       }
                
        if ((dato_rx == 'L')||(dato_rx == 'l')){
            
            printf("\n \rLugares libres: %i\n \r",resultado);
            printf("\n\r");
            Lugares_Disponibles();
                LED_blu = 0;
        }
        
        if ((dato_rx == 'H')||(dato_rx == 'h')){
            printf("\n\rHora: %i:%i:%i\n\r",hora, minutos, segundos);
        }
        
        if ((dato_rx == 'F')||(dato_rx == 'f')){
            printf("\n\rFecha: %i/%i/%i\n\r",dia, mes, anio);
        }
        if ((dato_rx != NULL ) && (dato_rx != 'F')&&(dato_rx != 'f')&&(dato_rx != 'H')&&(dato_rx != 'h')&&(dato_rx != 'L')
                &&(dato_rx != 'l')&&(dato_rx != 'O')&&(dato_rx != 'o')){
            printf("\n\rSeleccion no valida, por favor ingrese una de las siguientes opciones:");
            printf("\n\r\n\rOpciones:\n\r");
            printf("\n \r_ O para ver lugares ocupados.");
            printf("\n \r_ L para ver lugares libres.");
            printf("\n \r_ H para ver la hora actual.");
            printf("\n \r_ F para ver la fecha actual.\n\r");
           
        }
        
        Imprimir_Datos_Reloj();
        
    }
}

void Fijar_Datos_Reloj(){
   
    Escribir_DS_Hora(1);
    Escribir_DS_Min(20);
    Escribir_DS_Seg(50);
    Escribir_DS_Mes(12);
    Escribir_DS_dia_M(10);
    Escribir_DS_year(22);
    Escribir_DS_dia_S(1);
    Escribir_DS_control(0);
}

void Imprimir_Datos_Reloj(){
    hora = valor_Hora();
    minutos = valor_min();
    segundos = valor_segundos();
     // Fecha
    dia = valor_Dia();
    mes = valor_mes();
    anio = valor_anio();
    /*Lcd_Out(1,0,"- Hora:  ");
    Lcd_Chr_CP((hora/10)+48);
    Lcd_Chr_CP((hora%10)+48);
    Lcd_Chr_CP(':');
    Lcd_Chr_CP((minutos/10)+48);
    Lcd_Chr_CP((minutos%10)+48);
    Lcd_Chr_CP (':');
    Lcd_Chr_CP((segundos/10)+48);
    Lcd_Chr_CP((segundos%10)+48);
    Lcd_Out(1,16,"---");
    __delay_ms(200);
    Lcd_Out(1,0,"- Fecha:  ");
    Lcd_Chr_CP((dia/10)+48);
    Lcd_Chr_CP((dia%10)+48);
    Lcd_Chr_CP('/');
    Lcd_Chr_CP((mes/10)+48);
    Lcd_Chr_CP((mes%10)+48);
    Lcd_Chr_CP ('/');
    Lcd_Chr_CP((anio/10)+48);
    Lcd_Chr_CP((anio%10)+48);
    Lcd_Out(1,17,"--")*/
    __delay_ms (500);
}