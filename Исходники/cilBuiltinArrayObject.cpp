/***************************************************************************
 *      join property
 ***************************************************************************/
void CArrayObject::join( CCilVm* const pVm,
									const int32_t iNumArguments, 
									CVariable* pArguments )

{
	assert( iNumArguments >= 1 );
	CVariable& varThis = *pArguments;

	wstring sSeparator = wstring( STRING_INTERNAL_JOIN_DEFAULT_SEPARATOR );

	//Set up separator string
	if( iNumArguments > 1 )
	{
		//Set new separator
		pArguments ++;
		sSeparator = *pArguments->toString( pVm );
	}

	//Initialize destination variable in the eval stack
	pVm->pushEvalStackUndefined();
	
	CVariable& var = pVm->getEvalStackFirstEntry();
	var.iOperandType = OPERAND_STRING;
	var.pString = new wstring(L"");

	uint32_t iIndex = 0;
	uint32_t iLength = 0;
	hash_map< wstring, CVariable >::iterator itStart = varThis.refObject->getPropertyMap().begin();
	hash_map< wstring, CVariable >::iterator itEnd = varThis.refObject->getPropertyMap().end();
	while( itStart != itEnd )
	{
		bool bDigit = CheckArrayIndex( itStart->first );
		if( bDigit )
			iLength ++;
		itStart++;
	}
	
	wchar_t strIndex[ 16 ];

	while( iLength )
	{
		swprintf( strIndex, 16, L"%d", iIndex );
		CVariable* pvar;
		pvar = varThis.refObject->lookupProperty( strIndex );
		if( iIndex )
			var.pString->append( sSeparator );
		iIndex++;
		if( pvar )
		{
			CVariable varTmp = *pvar;
			
			//To eliminate recursive death
			if( varThis.refObject != varTmp.refObject ||
				varTmp.iOperandType != OPERAND_OBJECTREF )
			{
				varTmp.convertToString( pVm );
				var.pString->append( *varTmp.pString );
			}
			iLength--;
		}
	}
	
	return;
}