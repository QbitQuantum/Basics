void delay(unsigned int x)
{
	while(x!=0)
	{
		x--;
		__NOP();
	}
}