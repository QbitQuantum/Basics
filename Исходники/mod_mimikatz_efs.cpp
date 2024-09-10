bool mod_mimikatz_efs::infos(vector<wstring> * arguments)
{
	if(!arguments->empty())
	{
		PENCRYPTION_CERTIFICATE_HASH_LIST pHashes = NULL;

		if(QueryUsersOnEncryptedFile(arguments->front().c_str(), &pHashes) == ERROR_SUCCESS)
		{
			wcout << L"User (s) reported : " << pHashes->nCert_Hash << endl;
			printInfos(pHashes);
			FreeEncryptionCertificateHashList(pHashes);
		}
		else wcout << L"Error QueryUsersOnEncryptedFile : " << mod_system::getWinError() << endl;

		if(QueryRecoveryAgentsOnEncryptedFile(arguments->front().c_str(), &pHashes) == ERROR_SUCCESS)
		{
			wcout << L"Agent(s) covering  : " << pHashes->nCert_Hash << endl;
			printInfos(pHashes);
			FreeEncryptionCertificateHashList(pHashes);
		}
		else wcout << L"Error QueryRecoveryAgentsOnEncryptedFile : " << mod_system::getWinError() << endl;

	}
	return true;
}