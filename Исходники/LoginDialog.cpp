bool DisplayLoginForm(const wchar_t** wusername, const wchar_t** wpassword)
{
	CREDUI_INFOW info;
	static WCHAR username[CREDUI_MAX_USERNAME_LENGTH * sizeof(WCHAR)] = { 0 };
	static WCHAR password[CREDUI_MAX_PASSWORD_LENGTH * sizeof(WCHAR)] = { 0 };
	DWORD uLen = CREDUI_MAX_USERNAME_LENGTH;
	DWORD pLen = CREDUI_MAX_PASSWORD_LENGTH;
	LPVOID outStuff;
	ULONG outSize = 0;
	ULONG outPackage = 0;
	BOOL save = false;
	memset(&info, 0, sizeof(info));
	info.cbSize = sizeof(info);
	info.pszCaptionText = L"Authentication for Ultimatium";
	info.pszMessageText = L"Please log in using your forum credentials.";
	HRESULT result = CredUIPromptForWindowsCredentialsW(&info, 0, &outPackage, NULL, 0, &outStuff, &outSize, NULL, CREDUIWIN_GENERIC);
	if (result == ERROR_SUCCESS)
	{
		CredUnPackAuthenticationBufferW(0, outStuff, outSize, username, &uLen, NULL, 0, password, &pLen);
		*wusername = username;
		*wpassword = password;
	}
	return (result == ERROR_SUCCESS);
}