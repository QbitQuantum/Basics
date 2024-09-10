ALERROR CRandomEnhancementGenerator::InitFromXML (SDesignLoadCtx &Ctx, CXMLElement *pDesc)

//	InitFromXML
//
//	Loads the structure from XML

	{
	m_iChance = pDesc->GetAttributeInteger(ENHANCED_ATTRIB);
	CString sEnhancement = pDesc->GetAttribute(ENHANCEMENT_ATTRIB);

	//	If we have no enhancement desc, then we come up with a random
	//	one using our own internal algorithm.

	char *pPos = sEnhancement.GetASCIIZPointer();
	if (sEnhancement.IsBlank())
		{
		m_dwMods = 0;
		m_pCode = NULL;
		}

	//	If the enhancement desc is a script, then load it now

	else if (*pPos == '=')
		{
		CCodeChain &CC = g_pUniverse->GetCC();

		m_dwMods = 0;

		m_pCode = CC.Link(pPos, 1, NULL);
		if (m_pCode->IsError())
			{
			Ctx.sError = m_pCode->GetStringValue();
			m_pCode->Discard(&CC);
			return ERR_FAIL;
			}

		if (m_iChance == 0)
			m_iChance = 100;
		}

	//	Otherwise, see if this is a valid mod number

	else
		{
		m_dwMods = (DWORD)strToInt(sEnhancement, 0, NULL);
		m_pCode = NULL;

		if (m_dwMods != 0 && m_iChance == 0)
			m_iChance = 100;
		}

	return NOERROR;
	}