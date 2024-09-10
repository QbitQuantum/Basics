static void GetRestrictions(ULONG cRestrictions, const VARIANT *rgRestrictions, PWSTR tableName)
{
	//if (cRestrictions >= 3 && V_VT(&rgRestrictions[2]) == VT_BSTR && V_BSTR(&rgRestrictions[2]) != NULL)
	//{
	//	CW2A constraint(V_BSTR(&rgRestrictions[2]));
	//	ATLTRACE2("\tConstraint Name = %s\n", (LPSTR)constraint);

	//	strncpy(constraint, constraintName, 127);
	//	constraint[127] = '\0';
	//}

	if (cRestrictions >= 5 && V_VT(&rgRestrictions[5]) == VT_BSTR && V_BSTR(&rgRestrictions[5]) != NULL)
	{	
		ATLTRACE2(L"\tTable Name = %s\n", V_BSTR(&rgRestrictions[5]));
		wcsncpy(tableName, V_BSTR(&rgRestrictions[5]), 127);
		tableName[127] = '\0'; // ensure zero-terminated string
	}

	//if (cRestrictions >= 6 && V_VT(&rgRestrictions[5]) == VT_BSTR && V_BSTR(&rgRestrictions[5]) != NULL)
	//{
	//	CW2A column_name(V_BSTR(&rgRestrictions[5]));
	//	ATLTRACE2("\tColumn Name = %s\n", (LPSTR)column_name);

	//}
}