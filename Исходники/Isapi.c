CHAR *Isapi_ArgAlloc(EXTENSION_CONTROL_BLOCK *pECB,CHAR *lpVarName)
{
	// pECB->lpszQueryString
	CHAR *p,*p2;
	CHAR szName[180];
	UINT is;
	sprintf(szName,"&%s=",lpVarName);

	if (!pECB->lpszQueryString) return NULL;
	is=(UINT) strlen(szName); if (strlen(pECB->lpszQueryString)<is) return NULL;
	
	// Se inizia per
	if (!_memicmp(pECB->lpszQueryString,szName+1,is-1))
	{
		p=pECB->lpszQueryString; p+=(is-1);
		p2=strstr(p,"&"); if (p2) *p2=0;
		p=strDecode(p,SE_URL,NULL);
		if (p2) *p2='&';
		return p;
	}
	// Cerco all'interno
	p=strCaseStr(pECB->lpszQueryString,szName); if (!p) return NULL;
	p+=strlen(szName); p2=strstr(p,"&"); if (p2) *p2=0;
	p=strDecode(p,SE_URL,NULL);
	if (p2) *p2='&';
	return p;
}