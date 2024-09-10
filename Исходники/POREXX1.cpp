void POREXX1::application()
{
	log( "I", "Application POREXX1 starting." << endl ) ;

	int i ;
	int j ;

	bool found ;

	size_t version  ;
	string rxsource ;
	string path     ;

	RexxInstance *instance   ;
	RexxThreadContext *threadContext ;
	RexxArrayObject args     ;
	RexxCondition condition  ;
	RexxDirectoryObject cond ;
	RexxObjectPtr result     ;

	RexxContextEnvironment environments[ 2 ] ;
	RexxOption             options[ 3 ]      ;

	environments[ 0 ].handler = lspfServiceHandler ;
	environments[ 0 ].name    = "ISPEXEC" ;
	environments[ 1 ].handler = NULL ;
	environments[ 1 ].name    = ""   ;

	options[ 0 ].optionName = APPLICATION_DATA ;
	options[ 0 ].option     = (void *)this     ;
	options[ 1 ].optionName = DIRECT_ENVIRONMENTS  ;
	options[ 1 ].option     = (void *)environments ;
	options[ 2 ].optionName = ""  ;

	rxsource = word( PARM, 1 )    ;
	PARM     = subword( PARM, 2 ) ;
	found    = false              ;

	if ( rxsource.size() > 0 && rxsource[ 0 ] == '%' ) { rxsource.erase( 0, 1 ) ; }
	if ( rxsource == "" )
	{
		log( "E", "POREXX1 error. No REXX passed" << endl ) ;
		ZRC     = 16 ;
		ZRSN    = 4  ;
		ZRESULT = "No REXX passed" ;
		cleanup() ;
		return    ;
	}

	if ( rxsource[ 0 ] == '/' ) { rexxName = rxsource ; }
	else
	{
		j = getpaths( ZORXPATH ) ;
		for ( i = 1 ; i <= j ; i++ )
		{
			path     = getpath( ZORXPATH, i ) ;
			if ( path.back() != '/' ) { path += "/" ; }
			rexxName = path + rxsource ;
			if ( !exists( rexxName ) ) { continue ; }
			if ( is_regular_file( rexxName ) ) { found = true ; break ; }
			log( "E", "POREXX1 error. " << rxsource << " found but is not a regular file" << endl ) ;
			setmsg( "PSYS012B" ) ;
			ZRC     = 16 ;
			ZRSN    = 12 ;
			ZRESULT = "Invalid REXX passed" ;
			cleanup() ;
			return    ;
		}
		if ( !found )
		{
			log( "E", "POREXX1 error. " << rxsource << " not found in ZORXPATH concatination" << endl ) ;
			setmsg( "PSYS012C" ) ;
			ZRC     = 16 ;
			ZRSN    = 8  ;
			ZRESULT = "REXX not found" ;
			cleanup() ;
			return    ;
		}
	}

	if ( RexxCreateInterpreter( &instance, &threadContext, options ) )
	{
		args = threadContext->NewArray( 1 ) ;
		threadContext->ArrayPut(args, threadContext->String( PARM.c_str() ), 1 ) ;
		version = threadContext->InterpreterVersion() ;

		log( "I", "Starting OOREXX Interpreter Version. .: " << version << endl ) ;
		log( "I", "Running program. . . . . . . . . . . .: " << rxsource << endl ) ;
		log( "I", "With parameters. . . . . . . . . . . .: " << PARM << endl ) ;

		result = threadContext->CallProgram( rexxName.c_str(), args) ;

		if ( threadContext->CheckCondition() )
		{
			cond = threadContext->GetConditionInfo() ;
			threadContext->DecodeConditionInfo( cond, &condition ) ;
			log( "E", "POREXX1 error running REXX.: " << rxsource << endl ) ;
			log( "E", "   Condition Code . . . . .: " << condition.code << endl ) ;
			log( "E", "   Condition Error Text . .: " << threadContext->CString( condition.errortext ) << endl ) ;
			log( "E", "   Condition Message. . . .: " << threadContext->CString( condition.message ) << endl ) ;
			setmsg( "PSYS011M" ) ;
			ZRC     = 20 ;
			ZRSN    = condition.code ;
			ZRESULT = threadContext->CString( condition.message ) ;
		}
		else
		{
			if ( result != NULLOBJECT )
			{
				CSTRING resultString = threadContext->CString( result ) ;
			}
		}
		instance->Terminate() ;
	}
	cleanup() ;
	return    ;
}