static void tok822_quote_atom(TOK822 *tp)
{
    char   *cp;
    int     ch;

    /*
     * RFC 822 expects 7-bit data. Rather than quoting every 8-bit character
     * (and still passing it on as 8-bit data) we leave 8-bit data alone.
     */
    for (cp = vstring_str(tp->vstr); (ch = *(unsigned char *) cp) != 0; cp++) {
	if ( /* !ISASCII(ch) || */ ch == ' '
	    || ISCNTRL(ch) || strchr(tok822_opchar, ch)) {
	    tp->type = TOK822_QSTRING;
	    break;
	}
    }
}