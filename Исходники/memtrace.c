int
Mtrace(char *fmt,...)
{
	static	int inMtraceNow;
	int len;
	char *eolp;
	va_list argp;
	
	/* Mtrace not configured or disabled, so just return.
	 */
	if (!Mip || Mip->off)
		return(0);

	/* This may be called from interrupt and/or non-interrupt space of
	 * an application, so we must deal with possible reentrancy here.
	 */
	if (inMtraceNow) {
		Mip->reentered++;
		return(0);	
	}

	inMtraceNow = 1;

	Mip->ptr += snprintf(Mip->ptr,MAXLINSIZE,"\n<%04d> ",Mip->sno++);

	va_start(argp,fmt);
	len = vsnprintf(Mip->ptr,MAXLINSIZE,fmt,argp);
	va_end(argp);

	/* Strip all CR/LFs from the incoming string.
	 * The incoming string can have CR/LFs in it; however, they are stripped
	 * so that the format of the dump is stable (one line per Mtrace call).
	 * Notice that the top line of this function inserts a newline ahead
	 * of the sequence number; hence, additional CR/LFs in the text would
	 * just confuse the output.
	 */
	eolp = Mip->ptr;
	while(*eolp) {
		if ((*eolp == '\r') || (*eolp == '\n')) {
			strcpy(eolp,eolp+1);
			len--;
		}
		else
			eolp++;
	}

	/* If print flag is set, then dump to the console...
	 */
	if (Mip->mode & MODE_PRINT) {
		int	i;
		for(i=0;i<len;i++)
			putchar(*Mip->ptr++);
		putchar('\n');
	}
	else
		Mip->ptr += len;

	if (Mip->ptr >= Mip->end) {
		Mip->ptr = Mip->base;
		if (Mip->mode & MODE_NOWRAP)
			Mip->off = 1;
		else
			Mip->wrap++;
	}

	/* Flush the d-cache of the mtrace buffer and Mip structure after each
	 * transfer...
	 * This is important because if this is being accessed from an
	 * application that has d-cache enabled, then the hardware is reset,
	 * there is a chance that the data written was in cache and would be
	 * lost.
	 */
	flushDcache((char *)Mip,sizeof(struct mtInfo));
	flushDcache((char *)Mip->base,Mip->end - Mip->base);

	inMtraceNow = 0;
	return(len);
}