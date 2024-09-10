DOUBLE WindDataParser::GetDoubeItemByIndex(const VARIANT& safeArray, int index)
{
	if(!IsArray(safeArray))
	{
		return 0.0;
	}

	if (VT_R8 != (safeArray.vt & VT_BSTR_BLOB) && VT_DATE != (safeArray.vt & VT_BSTR_BLOB))
	{
		return 0.0;
	}
	long lPos = (long)index;
	DOUBLE dbl = 0;

	SafeArrayGetElement(safeArray.parray, &lPos, &dbl);
	
	return dbl;
}