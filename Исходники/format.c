/***********************************************************************
 *           acmFormatChooseA (MSACM32.@)
 */
MMRESULT WINAPI acmFormatChooseA(PACMFORMATCHOOSEA pafmtc)
{
    ACMFORMATCHOOSEW    afcw;
    MMRESULT            ret;
    LPWSTR              title = NULL;
    LPWSTR              name = NULL;
    LPWSTR              templ = NULL;
    DWORD               sz;

    afcw.cbStruct  = sizeof(afcw);
    afcw.fdwStyle  = pafmtc->fdwStyle;
    afcw.hwndOwner = pafmtc->hwndOwner;
    afcw.pwfx      = pafmtc->pwfx;
    afcw.cbwfx     = pafmtc->cbwfx;
    if (pafmtc->pszTitle)
    {
        sz = MultiByteToWideChar(CP_ACP, 0, pafmtc->pszTitle, -1, NULL, 0);
        if (!(title = HeapAlloc(GetProcessHeap(), 0, sz * sizeof(WCHAR))))
        {
            ret = MMSYSERR_NOMEM;
            goto done;
        }
        MultiByteToWideChar(CP_ACP, 0, pafmtc->pszTitle, -1, title, sz);
    }
    afcw.pszTitle  = title;
    if (pafmtc->pszName)
    {
        sz = MultiByteToWideChar(CP_ACP, 0, pafmtc->pszName, -1, NULL, 0);
        if (!(name = HeapAlloc(GetProcessHeap(), 0, sz * sizeof(WCHAR))))
        {
            ret = MMSYSERR_NOMEM;
            goto done;
        }
        MultiByteToWideChar(CP_ACP, 0, pafmtc->pszName, -1, name, sz);
    }
    afcw.pszName   = name;
    afcw.cchName   = pafmtc->cchName;
    afcw.fdwEnum   = pafmtc->fdwEnum;
    afcw.pwfxEnum  = pafmtc->pwfxEnum;
    afcw.hInstance = pafmtc->hInstance;
    if (pafmtc->pszTemplateName)
    {
        sz = MultiByteToWideChar(CP_ACP, 0, pafmtc->pszTemplateName, -1, NULL, 0);
        if (!(templ = HeapAlloc(GetProcessHeap(), 0, sz * sizeof(WCHAR))))
        {
            ret = MMSYSERR_NOMEM;
            goto done;
        }
        MultiByteToWideChar(CP_ACP, 0, pafmtc->pszTemplateName, -1, templ, sz);
    }
    afcw.pszTemplateName = templ;
    /* FIXME: hook procs not supported yet */
    if (pafmtc->pfnHook)
    {
        FIXME("Unsupported hook procs\n");
        ret = MMSYSERR_NOTSUPPORTED;
        goto done;
    }
    ret = acmFormatChooseW(&afcw);
    if (ret == MMSYSERR_NOERROR)
    {
        WideCharToMultiByte(CP_ACP, 0, afcw.szFormatTag, -1, pafmtc->szFormatTag, sizeof(pafmtc->szFormatTag),
                            NULL, NULL);
        WideCharToMultiByte(CP_ACP, 0, afcw.szFormat, -1, pafmtc->szFormat, sizeof(pafmtc->szFormat),
                            NULL, NULL);
        if (pafmtc->pszName)
            WideCharToMultiByte(CP_ACP, 0, afcw.pszName, -1, pafmtc->pszName, pafmtc->cchName, NULL, NULL);
    }
done:
    HeapFree(GetProcessHeap(), 0, title);
    HeapFree(GetProcessHeap(), 0, name);
    HeapFree(GetProcessHeap(), 0, templ);
    return ret;
}