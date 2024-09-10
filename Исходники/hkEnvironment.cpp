DWORD WINAPI OnGetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize)
{
	//typedef DWORD (WINAPI* OnGetEnvironmentVariableA_t)(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize);
	ORIGINAL_KRNL(GetEnvironmentVariableA);
	DWORD lRc = 0;

	if (lpName)
	{
		if ((lstrcmpiA(lpName, ENV_CONEMUANSI_VAR_A) == 0)
			|| (lstrcmpiA(lpName, ENV_CONEMUHWND_VAR_A) == 0)
			|| (lstrcmpiA(lpName, ENV_CONEMUDIR_VAR_A) == 0)
			|| (lstrcmpiA(lpName, ENV_CONEMUBASEDIR_VAR_A) == 0)
			)
		{
			CheckVariables();
		}
		else if (lstrcmpiA(lpName, ENV_CONEMUANSI_VAR_A) == 0)
		{
			CheckAnsiConVar(ENV_CONEMUANSI_VAR_W);
		}
		else if (lstrcmpiA(lpName, ENV_ANSICON_DEF_VAR_A) == 0)
		{
			CheckAnsiConVar(ENV_ANSICON_DEF_VAR_W);
		}
		else if (lstrcmpiA(lpName, ENV_ANSICON_VER_VAR_A) == 0)
		{
			if (lpBuffer && ((INT_PTR)nSize > lstrlenA(ENV_ANSICON_VER_VALUE)))
			{
				lstrcpynA(lpBuffer, ENV_ANSICON_VER_VALUE, nSize);
				lRc = lstrlenA(ENV_ANSICON_VER_VALUE);
			}
			goto wrap;
		}
	}

	lRc = F(GetEnvironmentVariableA)(lpName, lpBuffer, nSize);
wrap:
	return lRc;
}