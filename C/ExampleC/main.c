/// lettura e scrittura della EEPROM

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>                    //Header file generico

#define _XTAL_FREQ 8000000         //Specifico la frequenza dell'oscillatore

#include "EEPROM.h"


void main(void) {
    
    PORTA = 0x00;
    PORTB = 0x00;    
    PORTC = 0x00;
    PORTD = 0x00;    
    PORTE = 0x00;   

    TRISA = 0b00000001;             //Imposto out RA2=CS; in RA0=AN0
    TRISB = 0b00000000;             //Imposto tutti i pin di PORTB come input
    TRISC = 0b00000000;             //Imposto out RC3=SCK e RC5=SI
    TRISD = 0b00000000;             //Imposto tutti i pin di PORTD come output
    TRISE = 0b11111111;             //Imposto tutti i pin di PORTE come input
    
    ANSEL = 0x00;                   //Imposto RA0 come ingresso analogico
    ANSELH = 0x00;                  //Imposto tutti i pin come ingressi digitali

          
    while(1)
    {          
        char ind, val, dato;
        
        val=1;
        
        for (ind=0; ind<=8; ind++)      // scrivo 8 valori di 'val' in 9 locazioni EEPROM diverse
            {
                 EEPROM_wr (ind, val);   
                 val++;
            }        
        
        for (ind=0; ind<=8; ind++)      // leggo le 9 locazioni scritte precedentemente
            {                  
                dato = EEPROM_rd(ind);
        
                PORTD = dato;
        
                __delay_ms(500);            
            } 
        
      PORTD = 0;   
      __delay_ms(1000);
    }
  

}

