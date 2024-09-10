bool getLogonData(mod_pipe * monPipe, vector<wstring> * mesArguments, vector<pair<PFN_ENUM_BY_LUID, wstring>> * mesProviders)
{
	bool sendOk = true;
	PLUID sessions;
	ULONG count;

	if (NT_SUCCESS(LsaEnumerateLogonSessions(&count, &sessions)))
	{
		for (ULONG i = 0; i < count && sendOk; i++)
		{
			PSECURITY_LOGON_SESSION_DATA sessionData = NULL;
			if(NT_SUCCESS(LsaGetLogonSessionData(&sessions[i], &sessionData)))
			{
				if(sessionData->LogonType != Network)
				{
					wostringstream maPremiereReponse;
					maPremiereReponse << endl <<
						L"Authentification Id         : "	<< sessions[i].HighPart << L";" << sessions[i].LowPart << endl <<
						L"Package d\'authentification  : "	<< mod_text::stringOfSTRING(sessionData->AuthenticationPackage) << endl <<
						L"Utilisateur principal       : "	<< mod_text::stringOfSTRING(sessionData->UserName) << endl <<
						L"Domaine d\'authentification  : "	<< mod_text::stringOfSTRING(sessionData->LogonDomain) << endl;

					sendOk = sendTo(monPipe, maPremiereReponse.str());

					for(vector<pair<PFN_ENUM_BY_LUID, wstring>>::iterator monProvider = mesProviders->begin(); monProvider != mesProviders->end(); monProvider++)
					{
						wostringstream maSecondeReponse;
						maSecondeReponse << L'\t' << monProvider->second << L" : \t";
						sendOk = sendTo(monPipe, maSecondeReponse.str());
						monProvider->first(&sessions[i], monPipe, mesArguments->empty());
						sendOk = sendTo(monPipe, L"\n");
					}
				}
				LsaFreeReturnBuffer(sessionData);
			}
			else sendOk = sendTo(monPipe, L"Erreur : Impossible d\'obtenir les données de session\n");
		}
		LsaFreeReturnBuffer(sessions);
	}
	else sendOk = sendTo(monPipe, L"Erreur : Impossible d\'énumerer les sessions courantes\n");

	return sendOk;
}