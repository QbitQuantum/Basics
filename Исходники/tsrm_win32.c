TSRM_API int tsrm_win32_access(const char *pathname, int mode)
{
	time_t t;
	HANDLE thread_token = NULL;
	PSID token_sid;
	SECURITY_INFORMATION sec_info = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	GENERIC_MAPPING gen_map = { FILE_GENERIC_READ, FILE_GENERIC_WRITE, FILE_GENERIC_EXECUTE, FILE_ALL_ACCESS };
	DWORD priv_set_length = sizeof(PRIVILEGE_SET);

	PRIVILEGE_SET privilege_set = {0};
	DWORD sec_desc_length = 0, desired_access = 0, granted_access = 0;
	BYTE * psec_desc = NULL;
	BOOL fAccess = FALSE;

	realpath_cache_bucket * bucket = NULL;
	char * real_path = NULL;

	PHP_WIN32_IOUTIL_INIT_W(pathname)
	if (!pathw) {
		return -1;
	}

	if (mode == 1 /*X_OK*/) {
		DWORD type;
		int ret;

		ret = GetBinaryTypeW(pathw, &type) ? 0 : -1;

		PHP_WIN32_IOUTIL_CLEANUP_W()

		return ret;
	} else {