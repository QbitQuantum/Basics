void
_SHOWVALUE(
	unsigned long value,
	int size,
	const char *name,
	const char *file,
	int line)
{
	if(__debug_level >= DEBUGLEVEL_Reports)
	{
		char *fmt;

		switch(size)
		{
			case 1:

				fmt = "%s:%ld:%s = %ld, 0x%02lx";
				break;

			case 2:

				fmt = "%s:%ld:%s = %ld, 0x%04lx";
				break;

			default:

				fmt = "%s:%ld:%s = %ld, 0x%08lx";
				break;
		}

		_INDENT();

		if(debug_file == (BPTR)NULL)
			kprintf(fmt,file,line,name,value,value);
		else
			FPrintf(debug_file,fmt,file,line,name,value,value);

		if(size == 1 && value < 256)
		{
			if(debug_file == (BPTR)NULL)
			{
				if(value < ' ' || (value >= 127 && value < 160))
					kprintf(", '\\x%02lx'",value);
				else
					kprintf(", '%lc'",value);
			}
			else
			{
				if(value < ' ' || (value >= 127 && value < 160))
					FPrintf(debug_file,", '\\x%02lx'",value);
				else
					FPrintf(debug_file,", '%lc'",value);
			}
		}

		if(debug_file == (BPTR)NULL)
		{
			kprintf("\n");
		}
		else
		{
			FPrintf(debug_file,"\n");
			Flush(debug_file);
		}
	}
}