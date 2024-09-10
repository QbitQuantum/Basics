static HWND 	SearchResource(LPCSTR lpName,
					   int type,
					 DLGPROC pDialogProc,
					 LPARAM param,
					 char *lpFileBase,
					 int TotalFileSize,
					 HWND parentWnd)
{
	char *pResAll = lpFileBase + TotalFileSize;
	PRES pRes = (PRES)lpFileBase;
	char pszSearchedName[256];
	char *pszType = ResourceType(pRes);
	char *pszName;
	int size = ResourceSize(pRes);	
	char Name[512],*bb;
	PDIALOGBOXHEADER pdbh;
	HWND result;
	UINT_PTR ul;

	ul = (UINT_PTR)lpName;
	if (HIWORD(ul) == 0) {
		sprintf(pszSearchedName,"%d",LOWORD(ul));
	}
	else
	if (IsOrd((char *)lpName)) {
		sprintf(pszSearchedName,"%d",OrdID(lpName));
	}
	else if (lpName[1] == 0 && lpName[3] == 0) {
		ConvertWideString((char *)lpName,(char *)pszSearchedName);
	}
	else {
		strcpy(pszSearchedName,lpName);
	}
	do {
		if (pRes->HeaderSize+pRes->DataSize == 0)
			break;
		if (IsOrd((char *)pRes) && OrdID(pRes) == ORDID_RT_DLGINCLUDE) {
			/* Ignore include files */
			;
		}
		else if (IsOrd((char *)pRes) &&
				OrdID(pRes) == ORDID_RT_RESOURCE32) {
	        /*
            * This is the dummy resource that identifies a
            * 32 bit resource file.  This resource should be
            * skipped also.
            */
			}
			else {
			/* This is some other kind of a resource. See if it matches */
				if (pRes->DataSize) {
					int size = ResourceSize(pRes);	
					pszType = ResourceType(pRes);
					if (IsOrd(pszType) && OrdID(pszType) == type) {	
					    pszName = ResourceName(pRes);
						if (!IsOrd(pszName)) {
							if (pszName[1] == 0 && pszName[3] == 0)
								ConvertWideString(pszName,Name);
							else
								strcpy(Name,pszName);
						}
						else {
							sprintf(Name,"%d",OrdID(pszName));
						}
						if (!strcmp(Name,pszSearchedName)) {
							/* found it.*/
							if (type == 5) {
								/* Build a dialog box */
								pdbh = (PDIALOGBOXHEADER) SkipResHeader(pRes);
								bb = malloc(size);
								memcpy(bb,pdbh,size);
								result = CreateDialogIndirectParam(GetModuleHandle(NULL),
									(LPDLGTEMPLATE)bb,
									parentWnd,
									pDialogProc,param);
								free(bb);
								return result;
							}
							else if (type == 4) {
								/* Build a menu */
								return (HWND) ReadMenu((char *)SkipResHeader(pRes));
							}
							else if (type == 3) {
								/* Build an Icon */
								HICON hicon;
								hicon = CreateIconFromResource((PBYTE)SkipResHeader(pRes),
									size,
									TRUE,
									0x30000);
								return (HWND)hicon;
							}
							else if (type == 1) {
								/* Build a cursor */
								return (HWND)CreateIconFromResource((PBYTE)SkipResHeader(pRes),
									size,
									FALSE,
									0x30000);
							}
							else if (type == 2 || type == 14) {
								/* Build bitmap */
								char *start = SkipResHeader(pRes);
								bb = malloc(size);
								memcpy(bb,start,size);
								return (HWND) bb;
							}
						}
					}

				}
			}
			/* Move to the next resource. */
		pRes = (PRES) (((char *) pRes) + pRes->HeaderSize + pRes->DataSize);
        DWordAlign((PBYTE *)&pRes);
	} while (pRes < (PRES) ((char *) pResAll + size));
	return (HWND) 0;
}