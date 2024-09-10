/*
===============
idEditField::AutoComplete
===============
*/
void idEditField::AutoComplete( void )
{
	char completionArgString[MAX_EDIT_LINE];
	idCmdArgs args;
	
	if( !autoComplete.valid )
	{
		args.TokenizeString( buffer, false );
		idStr::Copynz( autoComplete.completionString, args.Argv( 0 ), sizeof( autoComplete.completionString ) );
		idStr::Copynz( completionArgString, args.Args(), sizeof( completionArgString ) );
		autoComplete.matchCount = 0;
		autoComplete.matchIndex = 0;
		autoComplete.currentMatch[0] = 0;
		
		if( strlen( autoComplete.completionString ) == 0 )
		{
			return;
		}
		
		globalAutoComplete = autoComplete;
		
		cmdSystem->CommandCompletion( FindMatches );
		cvarSystem->CommandCompletion( FindMatches );
		
		autoComplete = globalAutoComplete;
		
		if( autoComplete.matchCount == 0 )
		{
			return;	// no matches
		}
		
		// when there's only one match or there's an argument
		if( autoComplete.matchCount == 1 || completionArgString[0] != '\0' )
		{
		
			/// try completing arguments
			idStr::Append( autoComplete.completionString, sizeof( autoComplete.completionString ), " " );
			idStr::Append( autoComplete.completionString, sizeof( autoComplete.completionString ), completionArgString );
			autoComplete.matchCount = 0;
			
			globalAutoComplete = autoComplete;
			
			cmdSystem->ArgCompletion( autoComplete.completionString, FindMatches );
			cvarSystem->ArgCompletion( autoComplete.completionString, FindMatches );
			
			autoComplete = globalAutoComplete;
			
			idStr::snPrintf( buffer, sizeof( buffer ), "%s", autoComplete.currentMatch );
			
			if( autoComplete.matchCount == 0 )
			{
				// no argument matches
				idStr::Append( buffer, sizeof( buffer ), " " );
				idStr::Append( buffer, sizeof( buffer ), completionArgString );
				SetCursor( strlen( buffer ) );
				return;
			}
		}
		else
		{
		
			// multiple matches, complete to shortest
			idStr::snPrintf( buffer, sizeof( buffer ), "%s", autoComplete.currentMatch );
			
			if( strlen( completionArgString ) )
			{
				idStr::Append( buffer, sizeof( buffer ), " " );
				idStr::Append( buffer, sizeof( buffer ), completionArgString );
			}
		}
		
		autoComplete.length = strlen( buffer );
		autoComplete.valid = ( autoComplete.matchCount != 1 );
		SetCursor( autoComplete.length );
		
		common->Printf( "]%s\n", buffer );
		
		// run through again, printing matches
		globalAutoComplete = autoComplete;
		
		cmdSystem->CommandCompletion( PrintMatches );
		cmdSystem->ArgCompletion( autoComplete.completionString, PrintMatches );
		cvarSystem->CommandCompletion( PrintCvarMatches );
		cvarSystem->ArgCompletion( autoComplete.completionString, PrintMatches );
		
	}
	else if( autoComplete.matchCount != 1 )
	{
	
		// get the next match and show instead
		autoComplete.matchIndex++;
		
		if( autoComplete.matchIndex == autoComplete.matchCount )
		{
			autoComplete.matchIndex = 0;
		}
		
		autoComplete.findMatchIndex = 0;
		
		globalAutoComplete = autoComplete;
		
		cmdSystem->CommandCompletion( FindIndexMatch );
		cmdSystem->ArgCompletion( autoComplete.completionString, FindIndexMatch );
		cvarSystem->CommandCompletion( FindIndexMatch );
		cvarSystem->ArgCompletion( autoComplete.completionString, FindIndexMatch );
		
		autoComplete = globalAutoComplete;
		
		// and print it
		idStr::snPrintf( buffer, sizeof( buffer ), autoComplete.currentMatch );
		
		if( autoComplete.length > ( int ) strlen( buffer ) )
		{
			autoComplete.length = strlen( buffer );
		}
		
		SetCursor( autoComplete.length );
	}
}