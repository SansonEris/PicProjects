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

//colonne
#define col_1 RC4
#define col_2 RC5
#define col_3 RC6
#define col_4 RC7

//righe
#define rig_1 RC0
#define rig_2 RC1
#define rig_3 RC2
#define rig_4 RC3

//uscite random
#define LED0 RD0
#define LED1 RD1

int main(){

	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;

	TRISA = 0b00000000;
	TRISB = 0b00000000;
	TRISC = 0b00000000;
	TRISD = 0b00000000;
	TRISE = 0b00000000;

	ANSEL = 0x00; 	//imposto tutti i pin come input
	ANSELH = 0x00;

	/*
	INSERIRE
	ASSSEGNAMENTO
	16 TASTI/PULSANTI
	*/

//matrice del tastierino
int buttons[4][4] = {
	{TASTO1, TASTO2, TASTO3, TASTO4}, //riga 1
	{TASTO5, TASTO6, TASTO7, TASTO8}, //riga 2
	{TASTO9, TASTO10, TASTO11, TASTO12}, //riga 3
	{TASTO13, TASTO14, TASTO15, TASTO16} //riga 4
};

int row[4] = {rig_1,rig_2,rig_3,rig_4}, columns[4]={col_1,col_2,col_3,col_4}, ;


	while(true){

		/*-----verifica dei tasti premuti nel tastierino------*/


		//metto a 0 il valore della colonna su cui verificare il pulsante
	for(int i = 0; i < 4; i++){
		switch(i){
			case 0: 	//verifico la prima colonna
			columns[i] = 0;
			columns[i+=1] = 1;
			columns[i+=2] = 1;
			columns[i+=3] = 1;
			break;

			case 1:		//verifico la seconda colonna
			columns[i] = 0;
			columns[i-=1] = 1;
			columns[i+=1] = 1;
			columns[i+=2] = 1;
			break;

			case 2:		//verifico la terza colonna
			columns[i] = 0;
			columns[i-=2] = 1;
			columns[i-=1] = 1;
			columns[i+=1] = 1;
			break;

			case 3:		//verifico la quarta colonna
			columns[i] = 0;
			columns[i-=3] = 1;
			columns[i-=2] = 1;
			columns[i-=1] = 1;
			break;
		}
	
		//righe
			for(int k = 0; k < 4; k++){

				if(row[k]){ //verifico quale tasto viene premuto controllando le righe
					for(int j = 0; row[k] == 1; j++){ //continuo ad avere valore 1 sul pulsante premuto fin che é premuto
						buttons[k][i] = 1; //non dovrei mettere a 1 il pulsante, non so cosa dovrei fare ma quello é il pulsante premuto
						__delay_ms(1000); //pausa
					}
					buttons[k][i] = 0; //spengo il pulsante anche se bo
				}
				
			}
		} /*fine verifica tasti*/
	}
	//fine programma
}	

//se tengo premuto un tasto "f" per 2 second1 entro nelle sezione scrittura
//devo riconoscere 3 tasti in sequenza premuti, devo scrivere nel EEPROM -> il mio codice memorizzato;
//ogni tasto premuto dovrá essere verificato, se inserisco i 3 tasti in sequenza bo fai fare qualcosa


