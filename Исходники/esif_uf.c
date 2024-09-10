int EsifLogFile_Open(EsifLogType type, const char *filename, int append)
{
	int rc=0;
	char fullpath[MAX_PATH]={0};
	char mode[3] = {(append ? 'a' : 'w'), 0, 0};

	esif_ccb_write_lock(&g_EsifLogFile[type].lock);
	if (g_EsifLogFile[type].handle != NULL)
		esif_ccb_fclose(g_EsifLogFile[type].handle);

	EsifLogFile_GetFullPath(fullpath, sizeof(fullpath), filename);
#ifdef ESIF_ATTR_OS_WINDOWS
	mode[1] = 'c';
	g_EsifLogFile[type].handle = _fsopen(fullpath, mode, _SH_DENYWR);
	if (g_EsifLogFile[type].handle == NULL)
		rc = errno;
#else
	rc = esif_ccb_fopen(&g_EsifLogFile[type].handle, fullpath, mode);
#endif
	if (rc == 0) {
		esif_ccb_free(g_EsifLogFile[type].filename);
		g_EsifLogFile[type].filename = esif_ccb_strdup((char *)fullpath);
	}
	esif_ccb_write_unlock(&g_EsifLogFile[type].lock);
	return rc;
}