int StringToEnum(const STR16 value, const Str8EnumLookupType *table) 
{
	if (NULL == value || 0 == *value) 
		return 0;

	int result = 0;
	int len = wcslen(value)+1;
	STR8 mval = (STR8)malloc( len*sizeof(CHAR8) );
	wcstombs(mval, value, len);
	for (const Str8EnumLookupType *itr = table; itr->name != NULL; ++itr) {
		if (0 == _stricmp(mval, itr->name)) {
			result = itr->value;
		}
	}
	free(mval);
	return (result) ? result : (int)wcstol(value, NULL, 0);
}