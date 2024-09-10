void DSAD_Printf(OUT const INT8 *string,...)
{
#if 0
	va_list args;
	int i;
	if (dsadPrintEnable == 1)
 	{
		va_start(args,string);
		i = Vsnprintf((char *)dsadPrintBuff,sizeof(dsadPrintBuff), string, args);
		va_end(args);
		DSADS_P("%s", dsadPrintBuff);
	}
#endif
}