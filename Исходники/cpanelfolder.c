static HRESULT WINAPI IShellExecuteHookA_fnExecute(IShellExecuteHookA *iface,
        LPSHELLEXECUTEINFOA psei)
{
    ICPanelImpl *This = impl_from_IShellExecuteHookA(iface);

    SHELLEXECUTEINFOA sei_tmp;
    PIDLCPanelStruct* pcpanel;
    char path[MAX_PATH];
    BOOL ret;

    TRACE("(%p)->execute(%p)\n", This, psei);

    if (!psei)
	return E_INVALIDARG;

    pcpanel = _ILGetCPanelPointer(ILFindLastID(psei->lpIDList));

    if (!pcpanel)
	return E_INVALIDARG;

    path[0] = '\"';
    lstrcpyA(path+1, pcpanel->szName);

    /* pass applet name to Control_RunDLL to distinguish between applets in one .cpl file */
    lstrcatA(path, "\" ");
    lstrcatA(path, pcpanel->szName+pcpanel->offsDispName);

    sei_tmp = *psei;
    sei_tmp.lpFile = path;
    sei_tmp.fMask &= ~SEE_MASK_INVOKEIDLIST;

    ret = ShellExecuteExA(&sei_tmp);
    if (ret)
	return S_OK;
    else
	return S_FALSE;
}