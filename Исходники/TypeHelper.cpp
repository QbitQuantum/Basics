//获取函数类型的名称
std::wstring GetFunctionTypeName(int typeID, DWORD modBase) {

	std::wostringstream nameBuilder;

	//获取参数数量
	DWORD paramCount;
	SymGetTypeInfo(
		GetDebuggeeHandle(),
		modBase,
		typeID,
		TI_GET_CHILDRENCOUNT,
		&paramCount);

	//获取返回值的名称
	DWORD returnTypeID;
	SymGetTypeInfo(
		GetDebuggeeHandle(),
		modBase,
		typeID,
		TI_GET_TYPEID,
		&returnTypeID);

	nameBuilder << GetTypeName(returnTypeID, modBase);

	//获取每个参数的名称
	BYTE* pBuffer = (BYTE*)malloc(sizeof(TI_FINDCHILDREN_PARAMS) + sizeof(ULONG) * paramCount);
	TI_FINDCHILDREN_PARAMS* pFindParams = (TI_FINDCHILDREN_PARAMS*)pBuffer;
	pFindParams->Count = paramCount;
	pFindParams->Start = 0;

	SymGetTypeInfo(
		GetDebuggeeHandle(),
		modBase,
		typeID,
		TI_FINDCHILDREN,
		pFindParams);

	nameBuilder << TEXT('(');

	for (int index = 0; index != paramCount; ++index) {

		DWORD paramTypeID;
		SymGetTypeInfo(
			GetDebuggeeHandle(),
			modBase,
			pFindParams->ChildId[index],
			TI_GET_TYPEID,
			&paramTypeID);

		if (index != 0) {
			nameBuilder << TEXT(", ");
		}

		nameBuilder << GetTypeName(paramTypeID, modBase);
	}

	nameBuilder << TEXT(')');

	free(pBuffer);

	return nameBuilder.str();
}