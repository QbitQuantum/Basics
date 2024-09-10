// S_OK : 성공
// S_FALSE : 데이터는 가져왔지만 Consumer가 원하는 데이터가 아님
// E_FAIL : 실패
static HRESULT FetchData(int hReq, CTABLESRow &trData, int table_type)
{
	char *name;
	int type, ind, res;
	T_CCI_ERROR err_buf;

	res = cci_fetch(hReq, &err_buf);
	if(res<0) return RaiseError(E_FAIL, 1, __uuidof(IDBSchemaRowset), err_buf.err_msg);

	res = cci_get_data(hReq, 1, CCI_A_TYPE_STR, &name, &ind);
	if(res<0) return RaiseError(E_FAIL, 0, __uuidof(IDBSchemaRowset));
	CA2W nametmp(name);
	wcsncpy(trData.m_szTable, nametmp, 128);
	trData.m_szTable[128] = 0;
	_wcsupr(trData.m_szTable);

	res = cci_get_data(hReq, 2, CCI_A_TYPE_INT, &type, &ind);
	if(res<0) return RaiseError(E_FAIL, 0, __uuidof(IDBSchemaRowset));

	if((type==0 && (table_type & TABLE_TYPE_SYSTEM))
		|| (type==1 && (table_type & TABLE_TYPE_VIEW))
		|| (type==2 && (table_type & TABLE_TYPE_TABLE)))
	{
		switch(type)
		{
		case 0:
			wcscpy(trData.m_szType, L"SYSTEM TABLE");
			wcscpy(trData.m_szDesc, L"System Class");
			break;
		case 1:
			wcscpy(trData.m_szType, L"VIEW");
			wcscpy(trData.m_szDesc, L"Virtual Class");
			break;
		case 2:
			wcscpy(trData.m_szType, L"TABLE");
			wcscpy(trData.m_szDesc, L"Class");
			break;
		}
	}
	else
		return S_FALSE;

	return S_OK;
}