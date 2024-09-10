bool mod_crypto::CertCTXtoPFX(PCCERT_CONTEXT certCTX, wstring pfxFile, wstring password)
{
	bool retour = false;

	HCERTSTORE hTempStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL, CERT_STORE_CREATE_NEW_FLAG, NULL); 
	PCCERT_CONTEXT  pCertContextCopy = NULL;

	if(CertAddCertificateContextToStore(hTempStore, certCTX, CERT_STORE_ADD_NEW, &pCertContextCopy))
	{
		CRYPT_DATA_BLOB bDataBlob = {0, NULL};
		if(PFXExportCertStoreEx(hTempStore, &bDataBlob, password.c_str(), NULL, EXPORT_PRIVATE_KEYS | REPORT_NOT_ABLE_TO_EXPORT_PRIVATE_KEY))
		{
			bDataBlob.pbData = new BYTE[bDataBlob.cbData]; 
			if(PFXExportCertStoreEx(hTempStore, &bDataBlob, password.c_str(), NULL, EXPORT_PRIVATE_KEYS | REPORT_NOT_ABLE_TO_EXPORT_PRIVATE_KEY))
			{
				HANDLE hFile = CreateFile(pfxFile.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
				if(hFile && hFile != INVALID_HANDLE_VALUE)
				{
					DWORD dwBytesWritten;
					if(WriteFile(hFile, bDataBlob.pbData, bDataBlob.cbData, &dwBytesWritten, NULL) && (bDataBlob.cbData == dwBytesWritten))
					{
						retour = FlushFileBuffers(hFile) != 0;
					}
					CloseHandle(hFile);
				}
			}
			delete[] bDataBlob.pbData;
		}
		CertFreeCertificateContext(pCertContextCopy);
	}
	CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);

	return retour;
}