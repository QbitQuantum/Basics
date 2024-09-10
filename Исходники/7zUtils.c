LONG SNPrintf( STRPTR outbuf, LONG size, CONST_STRPTR fmt, ... )
{
	va_list args;
	long rc;
	
	va_start (args, fmt);
	rc = VSNPrintf( outbuf, size, fmt, args );
	va_end(args);
	
	return(rc);
}