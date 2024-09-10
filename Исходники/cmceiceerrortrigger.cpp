// ---------------------------------------------------------------------------
// CMceIceErrorTrigger::ParseErrorCode
// ---------------------------------------------------------------------------
//
TInt CMceIceErrorTrigger::ParseErrorCode() const
	{
	TInt errorCode( 0 );
	TLex8 lex( Value() );

	TChar ch = lex.Peek();
	while ( !ch.IsDigit() && ch != '-' && !ch.Eos() )
		{
		lex.Get();
		ch = lex.Peek();
		}

	if ( ch.Eos() )
		{
		errorCode = KErrNotFound;
		}
	else
		{
		lex.Val( errorCode );
		}
	RDebug::Print( _L("ICEPlugin Dummy: ParseErrorCode=%d" ), errorCode );
	return errorCode;
	}