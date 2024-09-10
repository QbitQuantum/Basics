void
FGP_doPostParseActions( FiniteGridParams params ) {
  /*
    Does more customized checking of the options to the program.
  */
  PomdpFgProgOptions opts;
  char tmp_str[MAX_OPT_STRING_LEN];
  int idx;

  /* just for convenience within this routine */
  opts = params->opts;

  /* Must have a POMDP filename or else things ill not work. */
  if (( opts->pomdp_filename == NULL )
	 || ( opts->pomdp_filename[0] == '\0' ))
    {
	 fprintf( stderr, "No POMDP file specified. Use '-h' for help.\n" );
	 exit( 1 );
    }

  /****************/
   /* First see if a random number seed is given, and if it is set the
      seed to this value. */
  if( opts->rand_seed[0] != '\0' )
    setRandomSeedFromString( opts->rand_seed );

  /* Otherwise initialize the random number generator with
	psuedo-random seed. */
  else
    randomize();

  /****************/
  /* Try to make the prefix be the prefix of the POMDP file if the
	default is chosen. */
  if ( strcmp( opts->prefix_str, POMDP_FG_OPTS_OPT_O_DEFAULT ) == 0 ) {

    strcpy( tmp_str, opts->pomdp_filename );

    /* This will point to null term at first */
    idx = strlen( tmp_str );  

    /* Start at the end and move left until we see the first
	  "period". */
    while (( idx > 0 ) && ( tmp_str[idx] != '.'))
	 idx--;

    /* Only override if we found a period in param filename */
    if ( idx > 0 ) {

	 /* Null terminate at the period */
	 tmp_str[idx] = '\0';

	 sprintf( opts->prefix_str, "%s-%d", tmp_str, getPid() );
	 
    } /* if we can override the default */

  } /* if default prefix is being used */

} /* FGP_doPostParseActions */