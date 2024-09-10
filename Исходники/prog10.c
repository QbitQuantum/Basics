// Interrupt Handler (UART)
void _int_(_UART1_VECTOR) isr_uart1(void){
    if(IFS0bits.U1RXIF){
        putC(U1RXREG);
        IFS0bits.U1RXIF = 0;            // Clear Receive Interrupt Flag
    }
}