int main(void){
    configureUART1(19200,'N',1);        // 19200 baud, 8 Bits, No Parity, 1 Stop Bit
    TRISEbits.TRISE0 = 0;               // RE0 Configured As Output

    while(1){
        while(U1STAbits.TRMT == 0);     // Wait While TRMPT == 0
        LATEbits.LATE0 = 1;             // Set RE0
        putS("123456789A\n");           // Send String
        LATEbits.LATE0 = 0;             // Reset RE0
    }
    return 0;
}