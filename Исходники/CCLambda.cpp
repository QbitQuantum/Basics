ICCItem *CCLambda::Execute (CEvalContext *pCtx, ICCItem *pArgs)

//	Execute
//
//	Executes the function and returns a result

	{
	CCodeChain *pCC = pCtx->pCC;
	ICCItem *pItem;
	ICCItem *pOldSymbols;
	ICCItem *pLocalSymbols;
	ICCItem *pVar;
	ICCItem *pArg;
	ICCItem *pResult;
	int i;
	BOOL bNoEval;

	//	We must have been initialized

	if (m_pArgList == NULL || m_pCode == NULL)
		return pCC->CreateNil();

	//	If the argument list if quoted, then it means that the arguments
	//	have already been evaluated. This happens if we've been called by
	//	(apply).

	bNoEval = pArgs->IsQuoted();

	//	Set up the symbol table

	pLocalSymbols = pCC->CreateSymbolTable();
	if (pLocalSymbols->IsError())
		return pLocalSymbols;

	//	Loop over each item and associate it

	for (i = 0; i < m_pArgList->GetCount(); i++)
		{
		pVar = m_pArgList->GetElement(i);
		pArg = pArgs->GetElement(i);

		//	If the name of this variable is %args, then the rest of the arguments
		//	should go into a list

		if (strCompareAbsolute(pVar->GetStringValue(), CONSTLIT("%args")) == 0)
			{
			ICCItem *pVarArgs;

			//	If there are arguments left, add them to a list

			if (pArg)
				{
				int j;
				ICCItem *pError;
				CCLinkedList *pList;

				//	Create a list

				pVarArgs = pCC->CreateLinkedList();
				if (pVarArgs->IsError())
					{
					pLocalSymbols->Discard(pCC);
					return pVarArgs;
					}
				pList = (CCLinkedList *)pVarArgs;

				//	Add each argument to the list

				for (j = i; j < pArgs->GetCount(); j++)
					{
					pArg = pArgs->GetElement(j);

					if (bNoEval)
						pResult = pArg->Reference();
					else
						pResult = pCC->Eval(pCtx, pArg);

					pList->Append(pCC, pResult, &pError);
					pResult->Discard(pCC);
					if (pError->IsError())
						{
						pVarArgs->Discard(pCC);
						pLocalSymbols->Discard(pCC);
						return pError;
						}

					pError->Discard(pCC);
					}
				}
			else
				pVarArgs = pCC->CreateNil();

			//	Add to the local symbol table

			pItem = pLocalSymbols->AddEntry(pCC, pVar, pVarArgs);
			pVarArgs->Discard(pCC);
			}

		//	Bind the variable to the argument

		else if (pArg == NULL)
			pItem = pLocalSymbols->AddEntry(pCC, pVar, pCC->CreateNil());
		else
			{
			ICCItem *pResult;

			//	Evaluate the arg and add to the table

			if (bNoEval)
				pResult = pArg->Reference();
			else
				pResult = pCC->Eval(pCtx, pArg);

			pItem = pLocalSymbols->AddEntry(pCC, pVar, pResult);
			pResult->Discard(pCC);
			}

		//	Check for error

		if (pItem->IsError())
			{
			pLocalSymbols->Discard(pCC);
			return pItem;
			}

		pItem->Discard(pCC);
		}

	//	Setup the context

	pLocalSymbols->SetParent(pCtx->pLexicalSymbols);
	pOldSymbols = pCtx->pLocalSymbols;
	pCtx->pLocalSymbols = pLocalSymbols;

	//	Evalute the code

	pResult = pCC->Eval(pCtx, m_pCode);

	//	Clean up

	pCtx->pLocalSymbols = pOldSymbols;
	pLocalSymbols->Discard(pCC);

	return pResult;
	}