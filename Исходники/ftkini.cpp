/****************************************************************************
Desc:	Stores a new value for the specified name (or creates a new name/value
	   pair) in the list of INI_STRUCTs
****************************************************************************/
RCODE FTKAPI F_IniFile::setParam(
	const char *	pszParamName,
	const char *	pszParamVal)
{
	RCODE				rc = NE_FLM_OK;
	INI_LINE *		pLine;

	f_assert( m_bReady);

	// If the parameter exists in the list, just store the new value.
	// Othewise, create a new INI_LINE and add it to the list
	
	pLine = findParam( pszParamName);
	if( !pLine)
	{
		if( RC_BAD( rc = setParamCommon( &pLine, pszParamName)))
		{
			goto Exit;
		}
	}

	if( RC_BAD( rc = toAscii( &pLine->pszParamValue, pszParamVal)))
	{
		goto Exit;
	}
	
Exit:

	return( rc);
}