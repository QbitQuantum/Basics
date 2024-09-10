int spi_sync()
{
	uint32_t timer;

	setTimer(&timer);
	while(1)
	{
		if(spi_checkIdle())
			return 1;
		if (getTimer(timer)>500000) // timeout .5 seconds
			return 0;
	}	
}