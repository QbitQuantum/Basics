int
pause(void)
{
	for(;;)
		if(_SLEEP(1000*1000) < 0)
			return -1;
}