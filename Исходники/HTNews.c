PRIVATE int response ARGS1(CONST char *,command)
{
    int result;    
    char * p = response_text;
    if (command) {
        int status;
	int length = strlen(command);
	if (TRACE) fprintf(stderr, "NNTP command to be sent: %s", command);
#ifdef NOT_ASCII
	{
	    CONST char  * p;
	    char 	* q;
	    char ascii[LINE_LENGTH+1];
	    for(p = command, q=ascii; *p; p++, q++) {
		*q = TOASCII(*p);
	    }
            status = NETWRITE(s, ascii, length);
	}
#else
        status = NETWRITE(s, command, length);
#endif
	if (status<0){
	    if (TRACE) fprintf(stderr,
	        "HTNews: Unable to send command. Disconnecting.\n");
	    NETCLOSE(s);
	    s = -1;
	    return status;
	} /* if bad status */
    } /* if command to be sent */
    
    for(;;) {  
	if (((*p++=NEXT_CHAR) == '\n') || (p == &response_text[LINE_LENGTH])) {
	    *p++=0;				/* Terminate the string */
	    if (TRACE) fprintf(stderr, "NNTP Response: %s\n", response_text);
	    sscanf(response_text, "%d", &result);
	    return result;	    
	} /* if end of line */
	
	if (*(p-1) < 0) {
	    if (TRACE) fprintf(stderr,
	    	"HTNews: EOF on read, closing socket %d\n", s);
	    NETCLOSE(s);	/* End of file, close socket */
	    return s = -1;	/* End of file on response */
	}
    } /* Loop over characters */
}