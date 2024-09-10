int ParseParamGroup( ParseContext* ctx )
{
	ConfigToken ParamTokens[] = { Token_IP, Token_Port, Token_KeyFile, Token_Pwd, Token_PwdFile, Token_RightBrace };
	ConfigToken token = Token_Unknown;
	char token_checks[TOKEN_COUNT];
	int rc = 0; 

	memset( token_checks, 0, sizeof(token_checks) );

	if( MatchToken( ctx, Token_LeftBrace ) == CONFIG_PARSE_ERROR ) return CONFIG_PARSE_ERROR;

	do 
	{
		/* get the parameter */
		token = ParseOneOf( ctx, ParamTokens, ARRAY_SIZE( ParamTokens ) );
		if( token == CONFIG_PARSE_ERROR ) rc = CONFIG_PARSE_ERROR;

		if( rc == 0 && token != Token_RightBrace )
		{
			token_checks[token] = 1;
			/* get the value */
			Advance( ctx );
			if( ctx->token == NULL )
			{
				sprintf( error_buffer, "%s: unexpected EOF found near '%s'", ERROR_PREFIX, TokenToString( token ) );
				rc = CONFIG_PARSE_ERROR;
			}

			/* assign the parameter value */
			if( rc == 0 ) rc = AssignParam( ctx, token, ctx->token );
		}

	} while( rc == 0 && token != Token_RightBrace );

	if( rc == 0 ) 
	{
		/* validate the current server settings */
		if( !token_checks[Token_IP] ) rc = FormatMissingServerParamError( Token_IP );
		if( rc == 0 && !token_checks[Token_KeyFile] ) rc = FormatMissingServerParamError( Token_KeyFile );
		if( rc == 0 && !token_checks[Token_Port] ) rc = FormatMissingServerParamError( Token_Port );

		if( rc == 0 && token_checks[Token_Pwd] && token_checks[Token_PwdFile] )
		{
			sprintf( error_buffer, "%s: Error in server definition: Either 'pwdfile' (recommended) or 'pwd' parameter is expected, but not both",
					ERROR_PREFIX );
			rc = CONFIG_PARSE_ERROR;
		}
	}

	return rc;
}