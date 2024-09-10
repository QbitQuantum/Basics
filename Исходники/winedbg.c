static	unsigned dbg_save_internal_vars(void)
{
    HKEY	                hkey;
    int		                i;

    /* @@ Wine registry key: HKCU\Software\Wine\WineDbg */
    if (RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Wine\\WineDbg", &hkey)) 
    {
	WINE_ERR("Cannot create WineDbg key in registry\n");
	return FALSE;
    }

    for (i = 0; i < DBG_IV_LAST; i++) 
    {
        /* FIXME: type should be infered from basic type -if any- of intvar */
        if (dbg_internal_vars[i].pval == &dbg_internal_vars[i].val)
            RegSetValueEx(hkey, dbg_internal_vars[i].name, 0,
                          REG_DWORD, (const void*)dbg_internal_vars[i].pval, 
                          sizeof(*dbg_internal_vars[i].pval));
    }
    RegCloseKey(hkey);
    return TRUE;
}