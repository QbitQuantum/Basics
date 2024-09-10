void assign_local ( void )
{
    signed long wlen;
    bool is_okay;
    u8 *savd_pc = pc;
    unsigned int savd_lineno = lineno;

    wlen = get_word();

	if ( wlen <= 0 )
	{
	    warn_unterm(TKERROR, "Locals Assignment", lineno);
	    return;
	}

    local_op = "!";   /*  Set to Store  */

    is_okay = handle_local( statbuf);
    if( INVERSE(is_okay)  )
    {
        tokenization_error ( TKERROR,
	    "Cannot apply -> to %s, only to a declared Local.\n", statbuf );
        pc = savd_pc;
	lineno = savd_lineno;
    }
    local_op = "@";   /*  Reset to Fetch  */
}