BOOL wf_authenticate(freerdp* instance, char** username, char** password, char** domain)
{
	BOOL fSave;
	DWORD status;
	DWORD dwFlags;
	char UserName[CREDUI_MAX_USERNAME_LENGTH + 1];
	char Password[CREDUI_MAX_PASSWORD_LENGTH + 1];
	char User[CREDUI_MAX_USERNAME_LENGTH + 1];
	char Domain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];

	fSave = FALSE;
	ZeroMemory(UserName, sizeof(UserName));
	ZeroMemory(Password, sizeof(Password));
	dwFlags = CREDUI_FLAGS_DO_NOT_PERSIST | CREDUI_FLAGS_EXCLUDE_CERTIFICATES;

	status = CredUIPromptForCredentialsA(&wfUiInfo,
					     instance->settings->ServerHostname,
					     NULL, 0,
		UserName, CREDUI_MAX_USERNAME_LENGTH + 1,
		Password, CREDUI_MAX_PASSWORD_LENGTH + 1, &fSave, dwFlags);

	if (status != NO_ERROR)
	{
		WLog_ERR(TAG, "CredUIPromptForCredentials unexpected status: 0x%08X", status);
		return FALSE;
	}

	ZeroMemory(User, sizeof(User));
	ZeroMemory(Domain, sizeof(Domain));

	status = CredUIParseUserNameA(UserName, User, sizeof(User), Domain, sizeof(Domain));
	//WLog_ERR(TAG, "User: %s Domain: %s Password: %s", User, Domain, Password);
	*username = _strdup(User);
	if (!(*username))
	{
		WLog_ERR(TAG, "strdup failed", status);
		return FALSE;
	}

	if (strlen(Domain) > 0)
		*domain = _strdup(Domain);
	else
		*domain = _strdup("\0");

	if (!(*domain))
	{
		free(*username);
		WLog_ERR(TAG, "strdup failed", status);
		return FALSE;
	}

	*password = _strdup(Password);
	if (!(*password))
	{
		free(*username);
		free(*domain);
		return FALSE;
	}

	return TRUE;
}