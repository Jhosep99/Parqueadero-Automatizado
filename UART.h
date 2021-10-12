/* 
 * File:   Sensores_De_Presencia.h
 * Author: jdgar
 *
 * Created on 08 de octubre de 2021, 07:08 AM
 */

#ifndef UART_H
#define UART_H

void UART_init();
char UART_read(void);
void UART_write(char dato);
void UART_printf(unsigned char *cadena);

void UART_init()
{
    TRISCbits.TRISC7 = 1;   //RX input
    TRISCbits.TRISC6 = 0;   //TX output 
    
    TXSTAbits.SYNC = 0;     //UART
    TXSTAbits.TX9 = 0;      //8 BITS
    TXSTAbits.BRGH = 0;     //Baja VELOCIDAD
    SPBRG = 5;            //9600 a 20MHZ
    RCSTAbits.SPEN = 1;     //UART on    
    TXSTAbits.TXEN = 1;    //TX on
    RCSTAbits.CREN = 1;     //RX on
}

char UART_read(void)
{
    if (PIR1bits.RCIF == 1){
        
        PIR1bits.RCIF = 0;
        return RCREG;
    }
       
    else
        return 0;
}

void UART_write(char dato)
{
    TXREG = dato;
     while(TXSTAbits.TRMT == 0);
}

void UART_printf(unsigned char *cadena)
{
    while(*cadena !=0x00){
        UART_write(*cadena);
        cadena++;
    }
}

void putch (char data){
    UART_write(data);
}
#endif