// ---------------------------------------------------------
// CWtaiHandler::GetParameterCountL()
// ---------------------------------------------------------
//
TInt CWtaiHandler::GetParameterCountL()
	{
	CLOG_ENTERFN( "CWtaiHandler::GetParameterCount()" );

	// wtai://<library>/<function> (; <parameter>)*

	TInt retVal = 0;
	TPtrC path = RemoveSchemeFromUrlL( KWtai );
	TInt length = path.Length();

	/* Count for the amount of parameter */
	for( TInt i = 0; i < length; i++ )
		{
		if( path[i] == KSemiColon )
			{
			retVal++;
			}
		}

	CLOG_LEAVEFN( "CWtaiHandler::GetParameterCount()" );

	return retVal;
	}