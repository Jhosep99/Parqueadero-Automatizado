/* 
 * File:   RtcLib.h
 * Author: jdgar
 *
 * Created on 11 de octubre de 2021, 11:33 AM
 */

#ifndef RTCLIB_H
#define	RTCLIB_H

#include "I2C.h"


char dec2bcd(char dato){
    
   dato = ((dato/10)<<4)|(dato%10); 
   return dato;
}

char bcd2dec (char dato2){
    
    dato2 = ((dato2 & 0xF0)>>4)*10 + (dato2 & 0x0F);
    return dato2;
}

void Escribir_DS_Seg(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x00);
    I2C_Enviar(d);
    I2C_Stop();
}

void Escribir_DS_Min(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x01);
    I2C_Enviar(d);
    I2C_Stop();
}
void Escribir_DS_Hora(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x02);
    I2C_Enviar(d);
    I2C_Stop();
}

void Escribir_DS_dia_S(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x03);
    I2C_Enviar(d);
    I2C_Stop();
}

void Escribir_DS_dia_M(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x04);
    I2C_Enviar(d);
    I2C_Stop();
}

void Escribir_DS_Mes(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x05);
    I2C_Enviar(d);
    I2C_Stop();
}

void Escribir_DS_year(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x06);
    I2C_Enviar(d);
    I2C_Stop();
}

void Escribir_DS_control(char d){
    
    d = dec2bcd(d);
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x07);
    I2C_Enviar(d);
    I2C_Stop();
}

char valor_segundos (){
    char d;
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x00);
    I2C_Reiniciar();
    I2C_Enviar(0xD1);
    d = I2C_Read();
    I2C_Stop();
    d = bcd2dec(d);
    
    return d;
}

char valor_min (){
    char d;
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x01);
    I2C_Reiniciar();
    I2C_Enviar(0xD1);
    d = I2C_Read();
    I2C_Stop();
    d = bcd2dec(d);
    return d;
}

char valor_Hora (){
    char d;
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x02);
    I2C_Reiniciar();
    I2C_Enviar(0xD1);
    d = I2C_Read();
    I2C_Stop();
    d = bcd2dec(d);
    
    return d;
}

char valor_Dia (){
    char d;
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x04);
    I2C_Reiniciar();
    I2C_Enviar(0xD1);
    d = I2C_Read();
    I2C_Stop();
    d = bcd2dec(d);
    
    return d;
}

char valor_mes (){
    char d;
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x05);
    I2C_Reiniciar();
    I2C_Enviar(0xD1);
    d = I2C_Read();
    I2C_Stop();
    d = bcd2dec(d);
    
    return d;
}

char valor_anio (){
    char d;
    I2C_Start();
    I2C_Enviar(0xD0); // D0h para escribir en el DS1307
    I2C_Enviar(0x06);
    I2C_Reiniciar();
    I2C_Enviar(0xD1);
    d = I2C_Read();
    I2C_Stop();
    d = bcd2dec(d);
    
    return d;
}
#endif	/* RTCLIB_H */

