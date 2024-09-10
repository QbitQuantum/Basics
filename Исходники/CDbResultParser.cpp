void FillValueTableNumber64(CValueTable* pValueTable, const char* str, 
						  size_t stRowIndex, size_t stColIndex, bool bNull)
{
#ifdef _WIN32
	T value = (T)_atoi64(str);
#else
	T value = (T)atoll(str);
#endif
	pValueTable->ExpandBuffer(stRowIndex, stColIndex, sizeof(T));
	pValueTable->SetValue(stRowIndex, stColIndex, &value, sizeof(T), bNull);
}