static void lcd_delay(unsigned long j)
{
	while(j--)
	{ 
            __NOP();
	}
}