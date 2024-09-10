// Load the device module
bool Win32LoadSecModule(SECURE *sec)
{
	SEC_DATA_WIN32 *w;
	HINSTANCE hInst;
	CK_FUNCTION_LIST_PTR api = NULL;
	CK_RV (*get_function_list)(CK_FUNCTION_LIST_PTR_PTR);
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}

	if (sec->Dev->Id == 9)
	{
		char username[MAX_SIZE];
		DWORD size;
		// Because the device driver of Juki-Net needs the contents 
		// of the Software\JPKI registry key on HKLU of SYSTEM,
		// if there is no key, copy the key from the value of other user
//		if (MsRegIsValue(REG_CURRENT_USER, "Software\\JPKI", "Name") == false ||
//			MsRegIsValue(REG_CURRENT_USER, "Software\\JPKI", "RWType") == false)
		size = sizeof(username);
		GetUserName(username, &size);
		if (StrCmpi(username, "System") == 0)
		{
			TOKEN_LIST *t = MsRegEnumKey(REG_USERS, NULL);

			if (t != NULL)
			{
				UINT i;

				for (i = 0;i < t->NumTokens;i++)
				{
					char tmp[MAX_PATH];

					if (StrCmpi(t->Token[i], ".DEFAULT") != 0 && StrCmpi(t->Token[i], "S-1-5-18") != 0)
					{
						Format(tmp, sizeof(tmp), "%s\\Software\\JPKI", t->Token[i]);

						if (MsRegIsValue(REG_USERS, tmp, "Name") && MsRegIsValue(REG_USERS, tmp, "RWType"))
						{
							char *name = MsRegReadStr(REG_USERS, tmp, "Name");
							char *port = MsRegReadStr(REG_USERS, tmp, "Port");
							UINT type = MsRegReadInt(REG_USERS, tmp, "RWType");

							MsRegWriteStr(REG_CURRENT_USER, "Software\\JPKI", "Name", name);
							MsRegWriteStr(REG_CURRENT_USER, "Software\\JPKI", "Port", port);
							MsRegWriteInt(REG_CURRENT_USER, "Software\\JPKI", "RWType", type);

							Free(name);
							Free(port);
							break;
						}
					}
				}

				FreeToken(t);
			}
		}
	}

	// Load the Library
	hInst = Win32SecureLoadLibraryEx(sec->Dev->ModuleName, 0);
	if (hInst == NULL)
	{
		// Failure
		return false;
	}

	// Get the API
	get_function_list = (CK_RV (*)(CK_FUNCTION_LIST_PTR_PTR))
		GetProcAddress(hInst, "C_GetFunctionList");

	if (get_function_list == NULL)
	{
		// Failure
		FreeLibrary(hInst);
		return false;
	}

	get_function_list(&api);
	if (api == NULL)
	{
		// Failure
		FreeLibrary(hInst);
		return false;
	}

	sec->Data = ZeroMalloc(sizeof(SEC_DATA_WIN32));
	w = sec->Data;

	w->hInst = hInst;
	sec->Api = api;

	return true;
}