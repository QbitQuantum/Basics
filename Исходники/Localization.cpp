BOOL CLocalization::Load(LPCTSTR fileName) {
	FILE *file = _wfopen(fileName, _T("rb"));
	if (file == NULL) return FALSE;

	// skip two first bytes
	TCHAR ch = fgetwc(file);
	TCHAR row[ROW_LEN];
	while (fgetws(row, ROW_LEN, file) != NULL) {
		if (row[0] == ';') continue;		// comment
		TCHAR *equal = wcschr(row, '=');
		if (equal != NULL) {
			*equal = '\0';					// split into number and string parts
			TCHAR *str = equal + 1;			// localized string

			// get ID
			UINT id;
			swscanf(row, _T("%d"), &id);
			// remove trailing "
			TCHAR *quote = wcsrchr(str, '"');
			if (quote != NULL) *quote = '\0';
			// skip leading "
			quote = wcschr(str, '"');
			str = quote + 1;
			Str.Add(new CLocalizationStr(id, wcsdup(str)));
		}
	}

	fclose(file);

	qsort(Str.GetData(), Str.Count, sizeof(CLocalizationStr *), CompareLocStr);

	return TRUE;
}