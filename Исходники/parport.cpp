void CParallel::Write_CON(Bitu val)
	{
	// init printer if bit 4 is switched on
	// ...
	autofeed = ((val & 0x02) != 0);		// autofeed adds 0xa if 0xd is sent

	// data is strobed to the parallel printer on the falling edge of strobe bit
	if ((!(val & 1)) && (controlreg & 1))
		{
		Putchar(datareg);
		if (autofeed && (datareg == 0xd))
			Putchar(0xa);
		ack = true;
		}
	controlreg = val;
	}