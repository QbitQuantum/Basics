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

	status = CredUIPromptForCredentialsA(&wfUiInfo, wfTargetName, NULL, 0,
		UserName, CREDUI_MAX_USERNAME_LENGTH + 1,
		Password, CREDUI_MAX_PASSWORD_LENGTH + 1, &fSave, dwFlags);

	if (status != NO_ERROR)
	{
		fprintf(stderr, "CredUIPromptForCredentials unexpected status: 0x%08X\n", status);
		return FALSE;
	}

	ZeroMemory(User, sizeof(User));
	ZeroMemory(Domain, sizeof(Domain));

	status = CredUIParseUserNameA(UserName, User, sizeof(User), Domain, sizeof(Domain));

	//fprintf(stderr, "User: %s Domain: %s Password: %s\n", User, Domain, Password);

	*username = _strdup(User);

	if (strlen(Domain) > 0)
		*domain = _strdup(Domain);

	*password = _strdup(Password);

	return TRUE;
}