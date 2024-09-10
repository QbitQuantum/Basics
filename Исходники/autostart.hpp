				/// <summary>
				/// Checks whether application is registered for autostart
				/// </summary>
				/// <param name="pszAppName">Application name</param>
				/// <returns></returns>
				BOOL isProgramRegisteredForStartup(PCWSTR pszAppName)
				{
					HKEY hKey = NULL;
					LONG lResult = 0;
					BOOL fSuccess = TRUE;
					DWORD dwRegType = REG_SZ;
					wchar_t szPathToExe[MAX_PATH] = {};
					DWORD dwSize = sizeof(szPathToExe);

					lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

					fSuccess = (lResult == 0);

					if (fSuccess)
					{
						lResult = RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
						fSuccess = (lResult == 0);
					}

					if (fSuccess)
					{
						fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;
					}

					if (hKey != NULL)
					{
						RegCloseKey(hKey);
						hKey = NULL;
					}

					return fSuccess;
				}