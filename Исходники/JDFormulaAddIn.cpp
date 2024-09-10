// Need String, String (char), Integer
extern "C" long _declspec(dllexport) _stdcall Split(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 2;

	// Check Input Parameters
	if (nNumArgs != 3 ||
		pArgs[0].nVarType != 2 ||
		pArgs[1].nVarType != 2 ||
		pArgs[2].nVarType != 1) {
		const wchar_t* errorMessage = L"Syntax: Syntax, Delimiter, Token Number.";
		SetString(pReturnValue, errorMessage);
		pReturnValue->isNull = 1;
		return 0;
	}

	// Check for Nulls
	if (pArgs[0].isNull || pArgs[2].isNull || pArgs[2].dVal < 0 || pArgs[1].isNull || wcslen(pArgs[1].pVal) == 0) {
		SetString(pReturnValue, pArgs[0].pVal);
		ResetIsNull(nNumArgs, pArgs);
		return 1;
	}

	// Copy the string
	size_t nLen = wcslen(pArgs[0].pVal);
	if (nLen == 0) {
		pReturnValue->isNull = true;
		return 1;
	}

	wchar_t *input = new wchar_t[nLen + 1];
	wcscpy(input, pArgs[0].pVal);

	// Split the String
	wchar_t* buffer = NULL;
	wchar_t *token = NULL;
	token = wcstok_s(input, pArgs[1].pVal, &buffer);
	int count = 1;
	while (token != NULL && count < pArgs[2].dVal) {
		token = wcstok_s(NULL, pArgs[1].pVal, &buffer);
		count++;
	}

	if (token == NULL) {
		pReturnValue->isNull = true;
	} else {
		SetString(pReturnValue, token);
	}

	delete input;
	return 1;
}