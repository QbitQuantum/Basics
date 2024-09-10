ALERROR CCurrencyAndRange::InitFromXML (SDesignLoadCtx &Ctx, const CString &sDesc)

//	InitFromXML
//
//	Initialize from XML

	{
	ALERROR error;

	//	Handle blank

	if (sDesc.IsBlank())
		{
		m_pCurrency.LoadUNID(NULL_STR);
		m_Value.SetConstant(0);
		return NOERROR;
		}

	//	Look for a colon separator

	char *pPos = sDesc.GetASCIIZPointer();
	char *pStart = pPos;
	while (*pPos != '\0' && *pPos != ':')
		pPos++;

	//	If found, then take the first part as the currency
	//	and the second part as value.

	CString sCurrency;
	CString sValue;
	if (*pPos == ':')
		{
		sCurrency = CString(pStart, pPos - pStart);
		sValue = CString(pPos + 1);
		}

	//	Otherwise, assume credits (blank string means credits)

	else
		sValue = sDesc;

	//	Load the currency type

	m_pCurrency.LoadUNID(sCurrency);

	//	Load the range

	if (error = m_Value.LoadFromXML(sValue))
		{
		Ctx.sError = strPatternSubst(CONSTLIT("Invalid dice range: %s"), sValue);
		return ERR_FAIL;
		}

	//	Done

	return NOERROR;
	}