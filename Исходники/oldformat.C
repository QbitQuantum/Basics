char* form(const char* format ...)
{
	register char* buf = bfree;
	if (max < buf+fld_size) buf = formbuf;

#	ifdef VSPRINTF
		va_list args ;
		va_start(args,format) ;
		VSPRINTF(buf,format,args) ;
		va_end(args) ;
#	else
		// not very portable
		register int* ap = (int*)((char*)&format+sizeof(char*));
		sprintf(buf,format,ap[0],ap[1],ap[2],ap[3],ap[4],ap[5],ap[6],ap[7],ap[8],ap[9]);	
#	endif

	register int ll = strlen(buf);			// not all sprintf's return length

	// If we have scribbled beyond the end of the buffer then
	// who knows what data we've destroyed.  Better to abort here
	// here there is some chance that somebody can associate
	// the location with the error than to continue and die
	// a mysterious death later.
//	if (fld_size < ll) abort();
	if (buf+ll >= formbuf+cb_size-1) {
	    fprintf(stderr, fmsg1);
	    abort();
	}
	
	bfree = buf+ll+1;
	return buf;
}