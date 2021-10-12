/* 
 * File:   Sensores_De_Presencia.h
 * Author: jdgar
 *
 * Created on 7 de octubre de 2021, 02:47 PM
 */

#ifndef SENSORES_DE_PRESENCIA_H
#define	SENSORES_DE_PRESENCIA_H

#include <stdio.h>
#define CFG_LED_1 TRISA0
#define CFG_LED_2 TRISA1
#define CFG_LED_3 TRISA2
#define CFG_LED_4 TRISA3
#define CFG_LED_5 TRISB7
#define CFG_LED_6 TRISA5
#define LED_1 RA0
#define LED_2 RA1
#define LED_3 RA2
#define LED_4 RA3
#define LED_5 RB7
#define LED_6 RA5

#define CFG_Sensor1 TRISB0
#define CFG_Sensor2 TRISB1
#define CFG_Sensor3 TRISB2
#define CFG_Sensor4 TRISB3
#define CFG_Sensor5 TRISB4
#define CFG_Sensor6 TRISB5
#define Sensor1 RB0
#define Sensor2 RB1
#define Sensor3 RB2
#define Sensor4 RB3
#define Sensor5 RB4
#define Sensor6 RB5

void Sensores_De_Presencia_Init(void);
void Leds_De_Sensores (void);
void Lugares_Disponibles (void);

//FUNCIONES
void Sensores_De_Presencia_Init(void){
    CFG_Sensor1 = 1;
    CFG_Sensor2 = 1;
    CFG_Sensor3 = 1;
    CFG_Sensor4 = 1;
    CFG_Sensor5 = 1;
    CFG_Sensor6 = 1;
    CFG_LED_5 = 0;
    TRISA = 0x00;
    ADCON1 = 0b0110;
}

void Leds_De_Sensores (void){
    
    LED_1 = !Sensor1;
    LED_2 = !Sensor2;
    LED_3 = !Sensor3;
    LED_4 = !Sensor4;
    LED_5 = !Sensor5;
    LED_6 = !Sensor6;
}

void Lugares_Disponibles (void){
    if(LED_1 == 0){
        printf("Lugar 1\n\r");
    }
    if(LED_2 == 0){
        printf("Lugar 2\n\r");
    }
    if(LED_3 == 0){
        printf("Lugar 3\n\r");
    }
    if(LED_4 == 0){
        printf("Lugar 4\n\r");
    }
    if(LED_5 == 0){
        printf("Lugar 5\n\r");
    }
    if(LED_6 == 0){
        printf("Lugar 6\n\r");
    }
}

void Lugares_Ocupados (void){
    if(LED_1 == 1){
        printf("Lugar 1\n\r");
    }
    if(LED_2 == 1){
        printf("Lugar 2\n\r");
    }
    if(LED_3 == 1){
        printf("Lugar 3\n\r");
    }
    if(LED_4 == 1){
        printf("Lugar 4\n\r");
    }
    if(LED_5 == 1){
        printf("Lugar 5\n\r");
    }
    if(LED_6 == 1){
        printf("Lugar 6\n\r");
    }
}
#endif	/* SENSORES_DE_PRESENCIA_H */

