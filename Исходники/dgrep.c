/**********************************************************************
 *
 *	dgrep
 *
 * Greps previously opened handle h.
 */
static void dgrep(int h)
{
	REG1 int	bufsize;
	REG2 int	nleftover = 0;
	REG3 int	leading_bytes = 0;
	int		nlines;
	int		nread;

	linecount = 1L;		/* first line number is 1 */
	matchcount = 0L;
	waiting_lines = 0;
	if (verbose && show_fname != NONE) {
		printf("*** File %s:\n", path);
		fname_shown = TRUE;
	} else
		fname_shown = FALSE;
	if (show_fname == BLOCK)	/* reset context match flag */
		first_match = TRUE;
	nread = align(maxbuf);
	while ((bufsize = read(h, buffer+leading_bytes+nleftover, nread)) > 0)
	{
		/* update nread to contain all bytes in the buffer */
		nread += leading_bytes+nleftover;
		bufsize += nleftover;
#if 0 /* Pete removed, because it behaves erroneusly when input is pipe */
		if (bufsize + leading_bytes < nread) { /* not full buffer */
			bufsize += add_last_newline_if(buffer, bufsize + leading_bytes);
            }
#endif
		nleftover = dgrep_buffer(buffer+leading_bytes, bufsize);
	    if (nleftover < 0) {
	    	break;
            } else if (nleftover == bufsize) {
		    nread = align(maxbuf-leading_bytes-nleftover);
                if (nread == 0) {
		        fprintf(stderr, "Warning: No line separator in buffer");
		        if (show_fname != NONE)
			        fprintf(stderr, " in file %s", path);
		        fprintf(stderr, "\n");
	    		nleftover = 0;
                }
	    } else {
	    	bufsize += leading_bytes;
		    if (leading_context && bufsize == nread) {
			    nlines = leading_context;
			    leading_bytes = 
				    get_leading_bytes(
				    buffer,
				    buffer+bufsize-nleftover-1,
				    &nlines);
		    } else {
			    leading_bytes = 0;
                }
			memcpy(buffer, buffer+bufsize-leading_bytes-nleftover,
				leading_bytes+nleftover);
            }
		nread = align(maxbuf-leading_bytes-nleftover);
	}
	if (nleftover > 0) {
		buffer[nleftover++] = EOL2;
		dgrep_buffer(buffer, nleftover);
	}
	if (!silent && count && !names) {
		if (show_fname != NONE)
			printf(path);
		show_number(matchcount);
		printf("\n");
	}
}