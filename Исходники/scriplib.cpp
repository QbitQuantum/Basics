void DefineMacro( char *macroname )
{
	script_t	*pmacro = (script_t *)malloc( sizeof( script_t ) );

	strcpy( pmacro->filename, macroname );
	pmacro->line = script->line;
	pmacro->nummacroparams = 0;

	char *mp = pmacro->macrobuffer;
	char *cp = script->script_p;

	while (TokenAvailable( ))
	{
		GetToken( false );

		if (token[0] == '\\' && token[1] == '\\')
		{
			break;
		}
		cp = script->script_p;

		pmacro->macroparam[pmacro->nummacroparams++] = mp;

		strcpy( mp, token );
		mp += strlen( token ) + 1;

		if (mp >= pmacro->macrobuffer + sizeof( pmacro->macrobuffer ))
			Error("Macro buffer overflow\n");
	}
	// roll back script_p to previous valid location
	script->script_p = cp;

	// find end of macro def
	while (*cp && *cp != '\n')
	{
		//Msg("%d ", *cp );
		if (*cp == '\\' && *(cp+1) == '\\')
		{
			// skip till end of line
			while (*cp && *cp != '\n')
			{
				*cp = ' '; // replace with spaces
				cp++;
			}

			if (*cp)
			{
				cp++;
			}
		}
		else
		{
			cp++;
		}
	}

	int size = (cp - script->script_p);

	pmacro->buffer = (char *)malloc( size + 1);
	memcpy( pmacro->buffer, script->script_p, size );
	pmacro->buffer[size] = '\0';
	pmacro->end_p = &pmacro->buffer[size]; 

	macrolist[nummacros++] = pmacro;

	script->script_p = cp;
}