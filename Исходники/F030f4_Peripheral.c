void USART_SendChar(unsigned char ch)
{
    while ((USART1->ISR & USART_ISR_TXE) == 0)
    {
        __NOP();
    };
    USART1->TDR = ch;
}