//vrati pocet zkopirovanych stringu
int CWordManager::LoadSafeArrayToStringTable(SAFEARRAY *sarray, CStringTableImpl &str_table)
{
	LONG l_bound = 0;
	LONG u_bound = -1;

	SafeArrayGetLBound(sarray, 1, & l_bound);
	SafeArrayGetUBound(sarray, 1, & u_bound);

	str_table.Clear();


	for (LONG a = l_bound; a <= u_bound; a++)
	{
		BSTR arg;
		SafeArrayGetElement(sarray, &a, & arg);

		_bstr_t s;
		s.Assign(arg);

		str_table.Add(s);
	}
	
	SafeArrayDestroy(sarray);

	return u_bound - l_bound +1;
}