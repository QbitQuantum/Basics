/*	Converter from \n to CRLF
**	-------------------------
**	The input is assumed to be in local representation with lines
**	delimited by \n. The \n when found is changed to a CRLF sequence,
**	the network representation of a new line.
**	Conversion: '\r' is stripped and \n => CRLF
*/
PRIVATE int TextToNet_put_block (HTStream * me, const char* b, int len)
{
    int status;
#if 0
    const char *limit = b+len;
#endif    
    if (!me->start)
	me->start = b;
    else {
	len -= (me->start - b);
	b = me->start;
    }
    while (len-- > 0) {
	if (me->had_cr && *b == LF) {
	    if (b > me->start+1) {
		if ((status = PUTBLOCK(me->start, b - me->start-1)) != HT_OK)
		    return status;
	    }
	    me->start = b+1;
	    if ((status = PUTC('\n')) != HT_OK)
		return status;
	}
	me->had_cr = (*b++ == CR);
    }
    if (me->start < b && (status = PUTBLOCK(me->start, b-me->start)) != HT_OK)
	return status;
    me->start = NULL;			      /* Whole buffer is written :-) */
    return HT_OK;
}