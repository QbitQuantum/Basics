bool CompString::create()
{
    HIMCC& handle = imc_->hCompStr;

    if (!handle) {
        handle = ImmCreateIMCC(sizeof(myCompStr));
        if (!handle)
            return false;
    } else if (ImmGetIMCCSize(handle) < sizeof(myCompStr)) {
        HIMCC temp = ImmReSizeIMCC(handle, sizeof(myCompStr));
        if (!temp)
            return false;
        handle = temp;
    }

    cs_ = (COMPOSITIONSTRING*)ImmLockIMCC(handle);
    if (!cs_)
        return false;

    ZeroMemory(cs_, sizeof(myCompStr));

    cs_->dwSize = sizeof(myCompStr);

    cs_->dwCompReadAttrOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->compReadAttr;
    cs_->dwCompReadClauseOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->compReadClause;
    cs_->dwCompReadStrOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->compReadStr;

    cs_->dwCompAttrOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->compAttr;
    cs_->dwCompClauseOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->compClause;
    cs_->dwCompStrOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->compStr;

    cs_->dwResultReadClauseOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->resultReadClause;
    cs_->dwResultReadStrOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->resultReadStr;

    cs_->dwResultClauseOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->resultClause;
    cs_->dwResultStrOffset = (DWORD)(UINT_PTR)&((myCompStr*)0)->resultStr;

    ImmUnlockIMCC(handle);

    return true;
}