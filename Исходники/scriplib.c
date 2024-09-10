void Parse1DMatrix (int x, vec_t *m) {
	int		i;

	MatchToken( "(" );

	for (i = 0 ; i < x ; i++) {
		GetToken( qfalse );
		m[i] = atof(token);
	}
#if 0
	MatchToken( ")" );
#else
	// su44: MoHAA patchDef2's sometimes have here additional keywords
	while(1) {
		GetToken( qtrue );
		if(!stricmp(token,"subdivisions")) {
			GetToken( qtrue ); // value
		} else if(!stricmp(token,"surfaceDensity")) {
			GetToken( qtrue ); // value
		} else if(!stricmp(token,"+surfaceparm")) {
			GetToken( qtrue ); // flagname
		} else if(!stricmp(token,"-surfaceparm")) {
			GetToken( qtrue ); // flagname		
		} else if(!stricmp(token,"surfaceColor")) {
			GetToken( qtrue );	
			GetToken( qtrue );	
			GetToken( qtrue );	
		} else {
			break;
		}
	}

	if ( strcmp( token, ")" ) ) {
		Error( "Parse1DMatrix: MatchToken( \"%s\" ) failed at line %i", ")", scriptline );
	}
#endif
}