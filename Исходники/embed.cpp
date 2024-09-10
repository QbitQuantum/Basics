int wmain(int argc, wchar_t* argv[])
{
	if(argc != 4)
		printUsage(argv[0]);

	const wchar_t* destinationName = argv[1];
	const wchar_t* classesName = argv[2];
	const wchar_t* mainClassName = argv[3];
	
	writeDestinationFile(destinationName);
	
	if(HANDLE hDest = BeginUpdateResourceW(destinationName, TRUE))
	{
		std::vector<std::wstring> strings;
		strings.resize(RESID_MAIN_CLASS + 1);
		strings.at(RESID_MAIN_CLASS) = mainClassName;
		
		writeStringResources(hDest, strings);
		
		std::vector<char> jarFile;
		readFile(&jarFile, classesName);
		UpdateResourceW(hDest, reinterpret_cast<LPCWSTR>(RT_RCDATA), RESID_BOOT_JAR, LANG_NEUTRAL, &jarFile.at(0), jarFile.size());
		
		EndUpdateResource(hDest, FALSE);
	}
	

	return 0;
}