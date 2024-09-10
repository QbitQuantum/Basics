// Function to compare strings used for sort operation 
UINT CALLBACK ListViewCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	bool isAsc = (lParamSort > 0);
	int column = abs(lParamSort) - 1;
	
	UINT result = 0;

	WCHAR buf1[MAX_BUFFER_LENGTH];
	WCHAR buf2[MAX_BUFFER_LENGTH];

	// Retrieve text from items
	ListView_GetItemText(m_list, lParam1, column, buf1, sizeof(buf1) / sizeof(WCHAR));
	ListView_GetItemText(m_list, lParam2, column, buf2, sizeof(buf2) / sizeof(WCHAR));

	wcslen(buf1);
	// Perform string compare depending on sort type
	if (isAsc) 
	{
		result = CompareStringEx(LOCALE_NAME_SYSTEM_DEFAULT,
			0,
			buf1,
			wcslen(buf1),
			buf2,
			wcslen(buf2),
			NULL, NULL, 0);
	}
	else 
	{	
		result = CompareStringEx(LOCALE_NAME_SYSTEM_DEFAULT,
			0,
			buf2,
			wcslen(buf2),
			buf1,
			wcslen(buf1),
			NULL, NULL, 0);
	}

	// Make return result consistent with C runtime
	return result - 2;
}