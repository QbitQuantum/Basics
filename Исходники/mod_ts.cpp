bool mod_ts::getProcesses(vector<KIWI_WTS_PROCESS_INFO> * mesProcesses, wstring * server)
{
	bool reussite = false;

	PWTS_PROCESS_INFO tabProcess;
	DWORD nbProcess = 0;
	HANDLE hServer = NULL;

	if(openServer(&hServer, server))
	{
		if(reussite = WTSEnumerateProcesses(hServer, 0, 1, &tabProcess, &nbProcess) != 0)
		{
			for(DWORD i = 0; i < nbProcess; i++)
			{
				KIWI_WTS_PROCESS_INFO a = {
					tabProcess[i].SessionId,
					tabProcess[i].ProcessId,
					tabProcess[i].pProcessName
				};

				wstring user;
				wstring domain;
				if(mod_secacl::sidToName(tabProcess[i].pUserSid, &user, &domain, server))
				{
					a.userSid.assign(domain);
					a.userSid.push_back(L'\\');
					a.userSid.append(user);
				}
				else if(!mod_secacl::sidToStrSid(tabProcess[i].pUserSid, &a.userSid))
				{
					if(tabProcess[i].pUserSid)
					{
						a.userSid.assign(L"erreur SID ; ");
						a.userSid.append(mod_system::getWinError());
					}
					else
						a.userSid.assign(L"n.a.");
				}

				mesProcesses->push_back(a);
			}
			WTSFreeMemory(tabProcess);
		}
		closeServer(hServer);
	}
	
	return reussite;
}