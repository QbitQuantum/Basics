bool FPerforceConnection::GetWorkspaceList(const FPerforceConnectionInfo& InConnectionInfo, FOnIsCancelled InOnIsCanceled, TArray<FString>& OutWorkspaceList, TArray<FText>& OutErrorMessages)
{
	if(bEstablishedConnection)
	{
		TArray<FString> Params;
		bool bAllowWildHosts = !GIsBuildMachine;
		Params.Add(TEXT("-u"));
		Params.Add(InConnectionInfo.UserName);

		FP4RecordSet Records;
		bool bConnectionDropped = false;
		bool bCommandOK = RunCommand(TEXT("clients"), Params, Records, OutErrorMessages, InOnIsCanceled, bConnectionDropped);

		if (bCommandOK)
		{
			FString ApplicationPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::GameDir()).ToLower();

			FString LocalHostName = InConnectionInfo.HostOverride;
			if(LocalHostName.Len() == 0)
			{
				// No host override, check environment variable
				TCHAR P4HostEnv[256];
				FPlatformMisc::GetEnvironmentVariable(TEXT("P4HOST"), P4HostEnv, ARRAY_COUNT(P4HostEnv));
				LocalHostName = P4HostEnv;
			}

			if (LocalHostName.Len() == 0)
			{
				// no host name, use local machine name
				LocalHostName = FString(FPlatformProcess::ComputerName()).ToLower();
			}
			else
			{
				LocalHostName = LocalHostName.ToLower();
			}

			for (int32 Index = 0; Index < Records.Num(); ++Index)
			{
				const FP4Record& ClientRecord = Records[Index];
				FString ClientName = ClientRecord("client");
				FString HostName = ClientRecord("Host");
				FString ClientRootPath = ClientRecord("Root").ToLower();

				//this clientspec has to be meant for this machine ( "" hostnames mean any host can use ths clientspec in p4 land)
				bool bHostNameMatches = (LocalHostName == HostName.ToLower());
				bool bHostNameWild = (HostName.Len() == 0);

				if( bHostNameMatches || (bHostNameWild && bAllowWildHosts) )
				{
					// A workspace root could be "null" which allows the user to map depot locations to different drives.
					// Allow these workspaces since we already allow workspaces mapped to drive letters.
					const bool bIsNullClientRootPath = (ClientRootPath == TEXT("null"));

					//make sure all slashes point the same way
					ClientRootPath = ClientRootPath.Replace(TEXT("\\"), TEXT("/"));
					ApplicationPath = ApplicationPath.Replace(TEXT("\\"), TEXT("/"));

					if (!ClientRootPath.EndsWith(TEXT("/")))
					{
						ClientRootPath += TEXT("/");
					}

					// Only allow paths that are ACTUALLY legit for this application
					if (bIsNullClientRootPath || ApplicationPath.Contains(ClientRootPath) )
					{
						OutWorkspaceList.Add(ClientName);
					}
					else
					{
						UE_LOG(LogSourceControl, Error, TEXT(" %s client specs rejected due to root directory mismatch (%s)"), *ClientName, *ClientRootPath);
					}

					//Other useful fields: Description, Owner, Host

				}
				else
				{
					UE_LOG(LogSourceControl, Error, TEXT(" %s client specs rejected due to host name mismatch (%s)"), *ClientName, *HostName);
				}
			}
		}

		return bCommandOK;
	}

	return false;
}