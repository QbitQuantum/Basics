eEsifError EsifCfgMgrInit ()
{
#ifdef ESIF_ATTR_OS_WINDOWS
		if (GetWindowsDirectoryA(g_DataVaultDir, sizeof(g_DataVaultDir)) == 0)
			esif_ccb_strcpy(g_DataVaultDir, "C:\\Windows", sizeof(g_DataVaultDir));
		esif_ccb_strcat(g_DataVaultDir, "\\ServiceProfiles\\LocalService\\AppData\\Local\\Intel\\DPTF\\", sizeof(g_DataVaultDir));
#else
		esif_ccb_strcpy(g_DataVaultDir, "/etc/dptf/", sizeof(g_DataVaultDir));
#endif

#ifdef BIG_LOCK
	esif_ccb_mutex_init(&g_shellLock);
#endif

	if (!g_DataBankMgr) {
		g_DataBankMgr = DataBank_Create();
		if (g_DataBankMgr) {
			return DataBank_LoadDataVaults(g_DataBankMgr);
		}
	}
	return ESIF_E_NO_MEMORY;
}