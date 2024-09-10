xpr_bool_t ShellEnumerator::enumerate(HWND aHwnd, LPSHELLFOLDER aShellFolder, xpr_sint_t aListType, xpr_sint_t aAttributes)
{
    DWORD   sFlags = 0;
    HRESULT sComResult;

    switch (aListType)
    {
    case ListTypeAll:        sFlags = SHCONTF_FOLDERS | SHCONTF_NONFOLDERS; break;
    case ListTypeOnlyFile:   sFlags = SHCONTF_NONFOLDERS;                   break;
    case ListTypeOnlyFolder: sFlags = SHCONTF_FOLDERS;                      break;
    }

    if (XPR_TEST_BITS(aAttributes, AttributeHidden))
    {
        sFlags |= SHCONTF_INCLUDEHIDDEN;
    }

    if (XPR_TEST_BITS(aAttributes, AttributeSystem))
    {
        sFlags |= SHCONTF_STORAGE;
    }

    LPENUMIDLIST sEnumIdList = XPR_NULL;

    sComResult = aShellFolder->EnumObjects(aHwnd, sFlags, &sEnumIdList);

    if (FAILED(sComResult))
    {
        if (XPR_IS_NOT_NULL(sEnumIdList))
        {
            COM_RELEASE(sEnumIdList);
        }

        return XPR_FALSE;
    }

    COM_RELEASE(mEnumIdList);

    mEnumIdList = sEnumIdList;

    return XPR_TRUE;
}