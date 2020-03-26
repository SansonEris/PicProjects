char EEPROM_rd (char indirizzo){

   EEADR = indirizzo;       // copio l'indirizzo nel registro EEADR
   EECON1bits.EEPGD = 0;    // puntamento alla memoria eeprom dati
   EECON1bits.RD = 1;       // effettuo la lettura
   
   return (EEDAT);          // restituisco il dato letto
}

void EEPROM_wr (char indirizzo, char dato){
   
   EEADR = indirizzo;
   EEDAT = dato;
   EECON1bits.EEPGD = 0;    // puntamento alla memoria eeprom dati
   EECON1bits.WREN = 1;     // abilito la scrittura sulla memoria EEPROM
   
   INTCONbits.GIE = 0;       // disabilito tutti gli interrupt  
   
   EECON2 = 0x55;           // sequenza richiesta
   EECON2 = 0xAA;
   
   EECON1bits.WR = 1;       // avvia scrittura
   
   while (EECON1bits.WR) {} // aspetto la fine della scrittura
   
   INTCONbits.GIE = 1;      // abilito tutti gli interrupt  
   
   EECON1bits.WREN = 0;     // disabilito la scrittura sulla memoria EEPROM   
   
}