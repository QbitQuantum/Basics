/** 
 * @UART uart sleep wakeup demo 
 * @param none
 * @return none
 */ 
void UartSleepWuDemo(void)
{
	UINT8 recbuf[3];
	Memset(recbuf,0x0,3);
	ModuleIrqRegister(Uart_Exception, UartIrqService);
	printf("Uart WFI sleep enetr!\r\n");
	//sleep
	SCB->SCR &= ~0x04;
	//sleep mode enter
	__WFI();	                               
	UartReceive(recbuf, 1);
	printf("\r\n");
	printf("Uart WFI  sleep Wakeup!\r\n");
}