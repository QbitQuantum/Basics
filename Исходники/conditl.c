static void conditionally_tokenize( bool cond, bool alr_ign )
{
    
    signed long wlen;

    /*  Note:  The following variables *must* remain within
     *      the scope of this routine; a distinct instance
     *      is needed each time this routine is re-entered
     *     (aka "a nested call").
     */
    bool ignoring;
    bool first_else = TRUE;  /*  The "else" we see is the first.  */
    bool not_done = TRUE;
    unsigned int cond_strt_lineno = lineno;
    char *cond_strt_ifile_nam = strdup( iname);

    ignoring = BOOLVAL( ( cond == FALSE ) || ( alr_ign != FALSE ) );

    if ( trace_conditionals )
    {
        char *cond_val = cond ? "True" : "False" ;
	char *cond_junct = alr_ign ? ", but Already " : "; ";
	char *processg = ignoring ? "Ignoring" : "Processing" ;
	tokenization_error( INFO,
	    "Tokenization-Condition is %s%s%s.\n",
		cond_val, cond_junct, processg);
    }

    while ( not_done )
    {
        wlen = get_word();
	if ( wlen == 0 )
	{
	    continue;
	}

	if ( wlen < 0 )
	{
	    tokenization_error( TKERROR,
	        "Conditional without conclusion; started");
	    just_where_started( cond_strt_ifile_nam, cond_strt_lineno);
	    not_done = FALSE ;
	    continue;
	}

	if ( is_a_then ( statbuf ) )
	{
	    if ( trace_conditionals )
	    {
		tokenization_error( INFO,
		    "Concluding Conditional");
		just_started_at( cond_strt_ifile_nam, cond_strt_lineno);
	    }
	    not_done = FALSE ;
	    continue;
	}

	if ( is_an_else( statbuf ) )
	{
	    if ( ! alr_ign )
	    {
		if ( first_else )
		{
		    ignoring = INVERSE( ignoring);
		}
	    }

	    if ( ! first_else )
	    {
		int severity = ignoring ? WARNING : TKERROR ;
		char *the_scop = ignoring ? "(ignored)" : "the" ;
		tokenization_error( severity, "Multiple %s directives "
		    "within %s scope of the Conditional",
			 strupr(statbuf), the_scop);
		just_started_at( cond_strt_ifile_nam, cond_strt_lineno);
	    }else{
		first_else = FALSE;
		if ( trace_conditionals )
		{
		    char *when_enc = alr_ign ? "While already" : "Now" ;
		    char *processg = alr_ign ? "ignoring" :
				    ignoring ? "Ignoring" : "Processing" ;
		    char *enc       = alr_ign ? ", e" : ".  E" ;

		    tokenization_error( INFO,
			"%s %s%sncountered %s belonging to Conditional",
			    when_enc, processg, enc, strupr(statbuf) );
		    just_started_at( cond_strt_ifile_nam, cond_strt_lineno);
		}
	    }

	    continue;
	}

	/*  If we are ignoring source input, for whatever reason, we still
	 *      need to be sensitive to the nesting of Conditional Operators
	 *      and some other commands and directives, as indicated...
	 */
	if ( ignoring )
	{
	    ignore_one_word( statbuf );
	}else{
	    /*  And if we're not ignoring source input, process it! */
	    tokenize_one_word ( wlen );
	}
    }
}