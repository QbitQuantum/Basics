bool	CResourceDef::MakeResourceName()
{
	ADDTOCALLSTACK("CResourceDef::MakeResourceName");
	if ( m_pDefName )
		return true;
	LPCTSTR pszName = GetName();

	GETNONWHITESPACE( pszName );
	TCHAR * pbuf = Str_GetTemp();
	TCHAR ch;
	TCHAR * pszDef;

	strcpy(pbuf, "a_");

	LPCTSTR pszKey = NULL;	// auxiliary, the key of a similar CVarDef, if any found
	pszDef = pbuf + 2;

	for ( ; *pszName; pszName++ )
	{
		ch	= *pszName;
		if ( ch == ' ' || ch == '\t' || ch == '-' )
			ch	= '_';
		else if ( !isalnum( ch ) )
			continue;
		// collapse multiple spaces together
		if ( ch == '_' && *(pszDef-1) == '_' )
			continue;
		*pszDef	= ch;
		pszDef++;
	}
	*pszDef	= '_';
	*(++pszDef)	= '\0';

	
	size_t iMax = g_Exp.m_VarDefs.GetCount();
	int iVar = 1;
	size_t iLen = strlen( pbuf );

	for ( size_t i = 0; i < iMax; i++ )
	{
		// Is this a similar key?
		pszKey	= g_Exp.m_VarDefs.GetAt(i)->GetKey();
		if ( strnicmp( pbuf, pszKey, iLen ) != 0 )
			continue;

		// skip underscores
		pszKey = pszKey + iLen;
		while ( *pszKey	== '_' )
			pszKey++;

		// Is this is subsequent key with a number? Get the highest (plus one)
		if ( IsStrNumericDec( pszKey ) )
		{
			int iVarThis = ATOI( pszKey );
			if ( iVarThis >= iVar )
				iVar = iVarThis + 1;
		}
		else
			iVar++;
	}

	// add an extra _, hopefully won't conflict with named areas
	sprintf( pszDef, "_%i", iVar );
	SetResourceName( pbuf );
	// Assign name
	return true;
}