void DisplayFile(wchar_t* szFile, BOOL isFile, ULONG DumpFilter, wchar_t* szObjName, strPassBackFn pDisplayString)
{
    // Open the emit scope
    WCHAR szScope[1024];
	char szString[1024];

    if (isFile)
    {
        wcscpy(szScope, L"file:");
        wcscat(szScope, szFile);
    }
    else
        wcscpy(szScope, szFile);

    // print bar that separates different files
    pDisplayString("////////////////////////////////////////////////////////////////\n");
    wchar_t rcFname[_MAX_FNAME], rcExt[_MAX_EXT];

    _wsplitpath(szFile, 0, 0, rcFname, rcExt);
    sprintf(szString,"\nFile %S%S: \n",rcFname, rcExt);
    pDisplayString(szString);

    if (DumpFilter & MDInfo::dumpValidate)
    {
        if (!_wcsicmp(rcExt, OBJ_EXT_W) || !_wcsicmp(rcExt, LIB_EXT_W))
            g_ValModuleType = ValidatorModuleTypeObj;
        else
            g_ValModuleType = ValidatorModuleTypePE;
    }

    if (!_wcsicmp(rcExt, LIB_EXT_W))
        DisplayArchive(szFile, DumpFilter, szObjName, pDisplayString);
    else
    {
        MDInfo metaDataInfo(g_pDisp, szScope, pDisplayString, DumpFilter);
        metaDataInfo.DisplayMD();
    }
} // void DisplayFile()