void CContactInfo::CountMultiFields(AECHAR *pwzField, int &nCount)
{
	if (NULL==pwzField ) return;

	nCount++;

	AECHAR pwzNewTag[]=NEW_FIELD;
	char pszNewtag[10];
	SPRINTF(pszNewtag, "%S", pwzNewTag);

	char *pszTmp=NULL;
	int nLen=WSTRLEN(pwzField);
	pszTmp = (char*)MALLOC(nLen+1);
	if ( NULL==pszTmp ) return;
	WSTRTOSTR(pwzField, pszTmp, nLen+1);

	char *pNext=pszTmp;
	char *pFound=NULL;
	while ( NULL!=(pFound=STRSTR(pNext, pszNewtag)))
	{
		nCount++;
		pNext = pFound+1;
	}

	FREEIF(pszTmp);
}