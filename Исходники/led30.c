void Code_0(void)
{
	uint8_t i;
	GPIOB->BSRR = GPIO_Pin_1;
	for(i=0;i<1;i++)
		__nop();
	__nop();
	GPIOB->BRR = GPIO_Pin_1;
	for(i=3;i>0;i--)
	{
		__nop();__nop();
	}
	__nop();
}