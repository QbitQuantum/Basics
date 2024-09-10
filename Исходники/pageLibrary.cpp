ICCItem *fnPageMap (CEvalContext *pEvalCtx, ICCItem *pArgs, DWORD dwData)

//	fnPageMap
//
//	(pageMap address|pageID enumMethod ['excludeNil] var exp) -> filtered list

	{
	CCodeChain *pCC = pEvalCtx->pCC;

	//	Args

	ICCItem *pAddress = pArgs->GetElement(0);
	ICCItem *pMethod = pArgs->GetElement(1);

	bool bExcludeNil;
	int iOptionalArg = 2;
	if (pArgs->GetCount() > 4)
		bExcludeNil = strEquals(pArgs->GetElement(iOptionalArg++)->GetStringValue(), CONSTLIT("excludeNil"));
	else
		bExcludeNil = false;

	ICCItem *pVar = pArgs->GetElement(iOptionalArg++);
	ICCItem *pBody = pArgs->GetElement(iOptionalArg++);

	//	Open the page

	IPage *pPage;
	CString sError;
	if (g_PM.OpenPage(pAddress->GetStringValue(), &pPage, &sError) != NOERROR)
		return pCC->CreateError(sError, NULL);

	//	Prepare the method

	SPageEnumCtx EnumCtx;
	if (pPage->EnumReset(*pCC, pMethod, EnumCtx, &sError))
		{
		g_PM.ClosePage(pPage);
		return pCC->CreateError(sError, NULL);
		}

	//	Create a destination list

	ICCItem *pResult = pCC->CreateLinkedList();
	if (pResult->IsError())
		{
		g_PM.ClosePage(pPage);
		return pResult;
		}

	CCLinkedList *pList = (CCLinkedList *)pResult;

	//	Setup the locals. We start by creating a local symbol table

	ICCItem *pLocalSymbols = pCC->CreateSymbolTable();
	if (pLocalSymbols->IsError())
		{
		pResult->Discard(pCC);
		g_PM.ClosePage(pPage);
		return pLocalSymbols;
		}

	//	Associate the enumaration variable

	ICCItem *pError = pLocalSymbols->AddEntry(pCC, pVar, pCC->CreateNil());
	if (pError->IsError())
		{
		pLocalSymbols->Discard(pCC);
		pResult->Discard(pCC);
		g_PM.ClosePage(pPage);
		return pError;
		}

	pError->Discard(pCC);

	//	Setup the context

	if (pEvalCtx->pLocalSymbols)
		pLocalSymbols->SetParent(pEvalCtx->pLocalSymbols);
	else
		pLocalSymbols->SetParent(pEvalCtx->pLexicalSymbols);
	ICCItem *pOldSymbols = pEvalCtx->pLocalSymbols;
	pEvalCtx->pLocalSymbols = pLocalSymbols;

	//	Get the offset of the variable so we don't have to
	//	search for it all the time

	int iVarOffset = pLocalSymbols->FindOffset(pCC, pVar);

	//	Enumerate the page

	while (pPage->EnumHasMore(EnumCtx))
		{
		ICCItem *pItem = pPage->EnumGetNext(*pCC, EnumCtx);
		if (pItem->IsError())
			{
			pResult->Discard(pCC);
			pResult = pItem;
			break;
			}

		//	Set the element

		pLocalSymbols->AddByOffset(pCC, iVarOffset, pItem);

		//	Eval

		ICCItem *pMapped = pCC->Eval(pEvalCtx, pBody);
		if (pMapped->IsError())
			{
			pItem->Discard(pCC);
			pResult->Discard(pCC);
			pResult = pMapped;
			break;
			}

		//	If the evaluation is not Nil, then we include the
		//	item in the result

		if (!bExcludeNil || !pMapped->IsNil())
			pList->Append(*pCC, pMapped);

		pItem->Discard(pCC);
		pMapped->Discard(pCC);
		}

	//	Clean up

	pEvalCtx->pLocalSymbols = pOldSymbols;
	pLocalSymbols->Discard(pCC);
	g_PM.ClosePage(pPage);

	//	Done

	if (pResult->GetCount() > 0)
		return pResult;
	else
		{
		pResult->Discard(pCC);
		return pCC->CreateNil();
		}
	}