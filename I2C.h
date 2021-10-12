/* 
 * File:   I2C.h
 * Author: jdgar
 *
 * Created on 11 de octubre de 2021, 11:29 AM
 */

#ifndef I2C_H
#define	I2C_H
#define _XTAL_FREQ 900000
#include <xc.h> 

void I2C_Init(unsigned long FOSC);
void I2C_Condiciones_Espera();
void I2C_Start();
void I2C_Stop();
void I2C_Enviar(char dato);
void I2C_Reiniciar();
unsigned char I2C_Read();

void I2C_Init(unsigned long FOSC){
    TRISC4 = 1; //Sda
    TRISC3 = 1; //Scl
    
    SSPSTATbits.SMP=1; // frec 100Khz a 1Mhz
    SSPCONbits.SSPEN=1; // habilitamos modulos i2c
    SSPCONbits.SSPM=0b1000;
    
    // FOSC = _XTAL/(4*SSPADD+1)
    SSPADD = (unsigned int)((_XTAL_FREQ/(4.0*FOSC))-1); 
    SSPCON2=0x00;      
}

void I2C_Condiciones_Espera(){
    while( (SSPCON2 & 0x1F  ) || (SSPSTAT & 0x04) );
}

void I2C_Start(){
    I2C_Condiciones_Espera();
    SSPCON2bits.SEN=1;
}

void I2C_Stop(){
    I2C_Condiciones_Espera();
    SSPCON2bits.PEN=1;
}

void I2C_Enviar(char dato){
    I2C_Condiciones_Espera();
    SSPBUF=dato;
}

void I2C_Reiniciar(){
    I2C_Condiciones_Espera();
    SSPCON2bits.RSEN =1;
}

unsigned char I2C_Read(){
    unsigned char datoR;
    I2C_Condiciones_Espera();
    SSPCON2bits.RCEN=1;
    I2C_Condiciones_Espera();
    datoR = SSPBUF;
    I2C_Condiciones_Espera();
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN=1;
    return datoR;
}

#endif	/* I2C_H */

