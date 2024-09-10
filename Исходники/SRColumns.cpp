static void GetRestrictions(ULONG cRestrictions, const VARIANT *rgRestrictions,
							PWSTR table_name, PWSTR column_name)
{
	// restriction이 없다고 항상 cRestrictions==0은 아니다.
	// 따라서 vt!=VT_EMPTY인지 등도 검사해줘야 한다.

	if(cRestrictions>=3 && V_VT(&rgRestrictions[2])==VT_BSTR && V_BSTR(&rgRestrictions[2])!=NULL)
	{	// TABLE_NAME restriction
		wcsncpy(table_name, V_BSTR(&rgRestrictions[2]), 1023);
		ATLTRACE2(L"\tTable Name = %s\n", V_BSTR(&rgRestrictions[2]));
		table_name[1023] = 0; // ensure zero-terminated string
	}

	if(cRestrictions>=4 && V_VT(&rgRestrictions[3])==VT_BSTR && V_BSTR(&rgRestrictions[3])!=NULL)
	{	// COLUMN_NAME restriction
		wcsncpy(column_name, V_BSTR(&rgRestrictions[3]), 1023);
		ATLTRACE2("\tColumn Name = %s\n", V_BSTR(&rgRestrictions[3]));
		column_name[1023] = 0; // ensure zero-terminated string
	}
}