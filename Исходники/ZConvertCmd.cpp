// xxx.exe -enc dst.path src.path xxxxx 1 rc4 0  
HRESULT CZConvertCmd::TransferCmdLine()
{
	LPWSTR *szArglist;
	int nArgs;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

	if (nArgs == 3&& NULL != szArglist)
	{
		if (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_ENCRPT_BYMEM))
		{
			LPTSTR memName = szArglist[2];
			ZDbgPrint(DBG_INFO,_T("ZDATABACK memName = %s"),memName);
			return TransferByMem(memName);
		}
		else
		{
			return ERROR_INVALID_PARAMETER;
		}
	}
	else if( szArglist == NULL || nArgs < 5)
	{
		return ERROR_INVALID_PARAMETER;
	}

	TCHAR dstPath[MAX_PATH] = {NULL};
	TCHAR srcPath[MAX_PATH] = {NULL};
	ULONG optionType = 0;
	ULONG encyptType = ENCRYPT_RC4;
	BOOL showProcDialog = FALSE;
	UCHAR passWord[MAX_PATH];
	ULONG passWorfLen = 0;

	if (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_ENCRPT_TOFILE))
	{
		optionType = CONVERT_OPTIONCODE_ENCRPT_TOFILE;
	}
	else if  (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_DECRPT_FROMFILE))
	{
		optionType = CONVERT_OPTIONCODE_DECRPT_FROMFILE;
	}
	else if  (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_ENCRPT_TOZIP))
	{
		optionType = CONVERT_OPTIONCODE_ENCRPT_TOZIP;
	}
	else if  (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_DECRPT_FROMZIP))
	{
		optionType = CONVERT_OPTIONCODE_DECRPT_FROMZIP;
	}

	_tcscpy_s(dstPath,_countof(dstPath),szArglist[2]);
	_tcscpy_s(srcPath,_countof(srcPath),szArglist[3]);

	memcpy(passWord,szArglist[4],_tcslen(szArglist[4]) * sizeof(TCHAR));
	passWorfLen = _tcslen(szArglist[4]) * sizeof(TCHAR);

	if (nArgs > 5)
	{
		if (0==_tcscmp(szArglist[5],CONVERT_CMD_SHOWPROCDIALOG))
		{
			showProcDialog = TRUE;
		}
		else if (0==_tcscmp(szArglist[5],CONVERT_CMD_NOTSHOWPROCDIALOG))
		{
			showProcDialog = FALSE;
		}
	}

	if (nArgs > 6)
	{
		if (0==_tcscmp(szArglist[6],CONVERT_CMD_ENCRPTTYPE_RC4))
		{
			encyptType = ENCRYPT_RC4;
		}
	}
	ZDbgPrint(DBG_INFO,_T("ZDATABACK srcpath = %s"),srcPath);

	return ConvertFileBase(dstPath,srcPath,optionType,encyptType,showProcDialog,passWord,passWorfLen,NULL,0,NULL);
}