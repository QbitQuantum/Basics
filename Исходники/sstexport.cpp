// usage: DumpCertsFromSst <output directory> <SST file 1> ... <SST file n>
int _tmain(int argc, _TCHAR* argv[])
{
SECURITY_ATTRIBUTES sa;   
memset(&sa, 0, sizeof(SECURITY_ATTRIBUTES));
sa.nLength = sizeof(SECURITY_ATTRIBUTES);
sa.bInheritHandle = FALSE;  

	if(argc < 2)
	{
	std::cout << "At least one argument must be provided: sstFile1 sstFile2 ... sstFileN etc" << std::endl;
	return 0;
	}

	for(int ii = 1; ii < argc; ++ii)
	{
	HANDLE       hFile = NULL;
	HCERTSTORE   hFileStore = NULL;
	LPCWSTR      pszFileName = argv[ii];

	//Open file
	hFile = CreateFile(pszFileName, GENERIC_READ, 0, &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);                      

		if(INVALID_HANDLE_VALUE == hFile)
		{
		std::wcout << "Failed to open file: " << pszFileName  << std::endl;
		continue;
		}
		else
		{
		std::wcout << "Processing file: " << pszFileName  << std::endl;
		}

	//open certificate store
	hFileStore = CertOpenStore(CERT_STORE_PROV_FILE, 0, NULL, CERT_STORE_READONLY_FLAG, hFile);

		if(NULL == hFileStore)
		{
		CloseHandle(hFile);
		continue;
		}

	int count = 0;
	PCCERT_CONTEXT pPrevCertContext = NULL;
	pPrevCertContext = CertEnumCertificatesInStore(hFileStore, pPrevCertContext);

		while(NULL != pPrevCertContext)
		{
		if(WriteToFileWithHashAsFilename(pPrevCertContext)) ++count;
		pPrevCertContext = CertEnumCertificatesInStore(hFileStore, pPrevCertContext);
		}

	std::wcout << "Wrote " << count << " certificates" << std::endl;
	CloseHandle(hFile);
	CertCloseStore(hFileStore, 0);
	}

return 1;
}