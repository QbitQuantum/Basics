ALERROR CDesignCollection::CreateTemplateTypes (SDesignLoadCtx &Ctx)

//	CreateTemplateTypes
//
//	This is called inside of BindDesign to create all template types

	{
	ALERROR error;
	int i;

	//	Create an appropriate context for running code

	CCodeChainCtx CCCtx;

	//	Loop over all active types looking for templates.
	//	NOTE: We cannot use the type-specific arrays because they have not been
	//	set up yet (remember that we are inside of BindDesign).

	for (i = 0; i < m_AllTypes.GetCount(); i++)
		{
		CDesignType *pTemplate = m_AllTypes.GetEntry(i);
		if (pTemplate->GetType() != designTemplateType)
			continue;

		//	Get the function to generate the type source

		CString sSource;
		SEventHandlerDesc Event;
		if (pTemplate->FindEventHandler(GET_TYPE_SOURCE_EVENT, &Event))
			{
			ICCItem *pResult = CCCtx.Run(Event);
			if (pResult->IsError())
				{
				Ctx.sError = strPatternSubst(CONSTLIT("GetTypeSource (%x): %s"), pTemplate->GetUNID(), pResult->GetStringValue());
				return ERR_FAIL;
				}
			else if (pResult->IsNil())
				sSource = NULL_STR;
			else
				sSource = pResult->GetStringValue();

			CCCtx.Discard(pResult);
			}

		//	Define the type

		if (!sSource.IsBlank())
			{
			if (error = AddDynamicType(pTemplate->GetExtension(), pTemplate->GetUNID(), sSource, true, &Ctx.sError))
				return error;
			}
		}

	return NOERROR;
	}