void morph_macro(macro_list **ppList, char *pMacro, char *pMorph, char *pPrintf)
{
    macro_list *pEntry = NULL;

    if(ppList == NULL || pMacro == NULL || pMorph == NULL || pPrintf == NULL) {
	return;
    }

    /*  Find macro of said name.
     *  Case insensitive.
     */
    pEntry = *ppList;
    while(pEntry)    {
	if(stricmp(pEntry->m_pMacro, pMacro) == 0)  {
	    break;
	}

	pEntry = pEntry->m_pNext;
    }

    if(pEntry)  {
	char_list *pFilename = NULL;
	char aPath[_MAX_PATH];
	char aDrive[_MAX_DRIVE];
	char aDir[_MAX_DIR];
	char aFName[_MAX_FNAME];
	char aExt[_MAX_EXT];
	char *pBuffer = NULL;

	/*  Start with buffer size needed.
	 *  We expand this as we go along if needed.
	 */
	pBuffer = (char *)malloc(strlen(pMorph) + 2);
	strcpy(pBuffer, pMorph);
	strcat(pBuffer, "=");

	/*  Go through each value, converting over to new macro.
	 */
	pFilename = pEntry->m_pValue;
	while(pFilename) {
	    _splitpath(pFilename->m_pString, aDrive, aDir, aFName, aExt);

	    /*  Expand buffer by required amount.
	     */
	    sprintf(aPath, pPrintf, aFName);
	    strcat(aPath, " ");
	    pBuffer = (char *)realloc(pBuffer, _msize(pBuffer) + strlen(aPath));
	    strcat(pBuffer, aPath);

	    pFilename = pFilename->m_pNext;
	}

	/*  Add the macro.
	 */
	add_macro(pBuffer, ppList);

	free(pBuffer);
	pBuffer = NULL;
    }
}