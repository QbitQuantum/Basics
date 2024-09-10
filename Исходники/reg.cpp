static void BackupRegTree_Worker(HKEY hKey,const char *pszSubKey,struct BackupRegTreeParam *param)
{
	LONG res;
	DWORD nMaxSubKeyLen,nMaxValNameLen,nMaxValSize;
	DWORD index,cchName,dwType,cbData;
	BYTE *pData;
	char *pszName;
	register TCHAR *ptszName;
	DWORD nDbPrefixLen;
	if ((res=RegOpenKeyExA(hKey,pszSubKey,0,KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS,&hKey))==ERROR_SUCCESS) {
		if ((res=RegQueryInfoKey(hKey,NULL,NULL,NULL,NULL,&nMaxSubKeyLen,NULL,NULL,&nMaxValNameLen,&nMaxValSize,NULL,NULL))==ERROR_SUCCESS) {
			if (nMaxSubKeyLen>nMaxValNameLen) nMaxValNameLen=nMaxSubKeyLen;
			/* prepare buffer */
			nDbPrefixLen = (DWORD)(mir_strlen(*param->ppszDbPrefix) + mir_strlen(pszSubKey) + 1);
			cchName = nDbPrefixLen + nMaxValNameLen + 3;
			if (cchName>*param->pdwDbPrefixSize) {
				pszName=(char*)mir_realloc(*param->ppszDbPrefix,cchName);
				if (pszName==NULL) return;
				*param->ppszDbPrefix=pszName;
				*param->pdwDbPrefixSize=cchName;
			}
			mir_strcat(mir_strcat(*param->ppszDbPrefix,pszSubKey),"\\"); /* buffer safe */
			/* enum values */
			pszName=(char*)mir_alloc(nMaxValNameLen+1);
			if (nMaxValSize==0) nMaxValSize=1;
			pData=(BYTE*)mir_alloc(nMaxValSize);
			if (pszName!=NULL && pData!=NULL) {
				index=0;
				while(!res) {
					cchName=nMaxValNameLen+1;
					cbData=nMaxValSize;
					if ((res=RegEnumValueA(hKey,index++,pszName,&cchName,NULL,NULL,NULL,NULL))==ERROR_SUCCESS) {
						(*param->ppszDbPrefix)[nDbPrefixLen]=0;
						mir_strcat(*param->ppszDbPrefix,pszName); /* buffer safe */
						ptszName=a2t(pszName);
						if (ptszName!=NULL) {
							if (!RegQueryValueEx(hKey,ptszName,NULL,&dwType,pData,&cbData)) {

								WriteDbBackupData(*param->ppszDbPrefix,dwType,pData,cbData);

							}
							mir_free(ptszName);
						}
					}
				}
				if (res==ERROR_NO_MORE_ITEMS) res=ERROR_SUCCESS;
			}
			mir_free(pData); /* does NULL check */
			/* enum subkeys */
			if (param->level<32 && pszName!=NULL) {
				++param->level; /* can be max 32 levels deep (after prefix), restriction of RegCreateKeyEx() */
				index=0;
				while(!res) {
					cchName=nMaxSubKeyLen+1;
					if ((res=RegEnumKeyExA(hKey,index++,pszName,&cchName,NULL,NULL,NULL,NULL))==ERROR_SUCCESS) {
						(*param->ppszDbPrefix)[nDbPrefixLen]=0;
						BackupRegTree_Worker(hKey,pszName,param); /* recursion */
					}
				}
			}
			if (res==ERROR_NO_MORE_ITEMS) res=ERROR_SUCCESS;
			mir_free(pszName); /* does NULL check */
		}
		RegCloseKey(hKey);
	}
}