/* PUBLIC						HTAA_getUnfoldedLine()
 *		READ AN UNFOLDED HEADER LINE FROM SOCKET
 * ON ENTRY:
 *	HTAA_setupReader must absolutely be called before
 *	this function to set up internal buffer.
 *
 * ON EXIT:
 *	returns a newly-allocated character string representing
 *		the read line.	The line is unfolded, i.e.
 *		lines that begin with whitespace are appended
 *		to current line.  E.g.
 *
 *			Field-Name: Blaa-Blaa
 *			 This-Is-A-Continuation-Line
 *			 Here-Is_Another
 *
 *		is seen by the caller as:
 *
 *	Field-Name: Blaa-Blaa This-Is-A-Continuation-Line Here-Is_Another
 *
 */
char *HTAA_getUnfoldedLine(void)
{
    char *line = NULL;
    char *cur;
    int count;
    BOOL peek_for_folding = NO;

    if (in_soc < 0) {
	CTRACE((tfp, "%s %s\n",
		"HTAA_getUnfoldedLine: buffer not initialized",
		"with function HTAA_setupReader()"));
	return NULL;
    }

    for (;;) {

	/* Reading from socket */

	if (start_pointer >= end_pointer) {	/*Read the next block and continue */
#ifdef USE_SSL
	    if (SSL_handle)
		count = SSL_read(SSL_handle, buffer, BUFFER_SIZE);
	    else
		count = NETREAD(in_soc, buffer, BUFFER_SIZE);
#else
	    count = NETREAD(in_soc, buffer, BUFFER_SIZE);
#endif /* USE_SSL */
	    if (count <= 0) {
		in_soc = -1;
		return line;
	    }
	    if (count > (int) buffer_length)
		count = (int) buffer_length;
	    start_pointer = buffer;
	    end_pointer = buffer + count;
	    *end_pointer = '\0';
#ifdef NOT_ASCII
	    cur = start_pointer;
	    while (cur < end_pointer) {
		*cur = TOASCII(*cur);
		cur++;
	    }
#endif /*NOT_ASCII */
	}
	cur = start_pointer;

	/* Unfolding */

	if (peek_for_folding) {
	    if (*cur != ' ' && *cur != '\t')
		return line;	/* Ok, no continuation line */
	    else		/* So this is a continuation line, continue */
		peek_for_folding = NO;
	}

	/* Finding end-of-line */

	while (cur < end_pointer && *cur != '\n')	/* Find the end-of-line */
	    cur++;		/* (or end-of-buffer).  */

	/* Terminating line */

	if (cur < end_pointer) {	/* So *cur==LF, terminate line */
	    *cur = '\0';	/* Overwrite LF */
	    if (*(cur - 1) == '\r')
		*(cur - 1) = '\0';	/* Overwrite CR */
	    peek_for_folding = YES;	/* Check for a continuation line */
	}

	/* Copying the result */

	if (line)
	    StrAllocCat(line, start_pointer);	/* Append */
	else
	    StrAllocCopy(line, start_pointer);	/* A new line */

	start_pointer = cur + 1;	/* Skip the read line */

    }				/* forever */
}