/*Returns full path to file.
TODO: Check if the file is older than 5-10 minutes, if not just return file path
*/
std::string SteamWebAPI::getSteamXML(std::string URL, std::string filename){
	std::string path = std::string("C:\\Windows\\Temp\\").append(filename);

	HANDLE file = CreateFile(s2ws(path).c_str(),(GENERIC_READ | GENERIC_WRITE), 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//check to see if the file is still relatively new, new meaning ~10 minutes here
	//this looks sloppy and needs refactored
	if(GetLastError() != 183){
		std::cout << "file had to be created" << std::endl;
	}
	else if(!pastThreshold(file)){
		std::cout << "file is not past time threshhold" << std::endl;
		CloseHandle(file);
		return path;
	}
	else
		std::cout << "Creating new file" << std::endl;


	HINTERNET hOpen = InternetOpen(L"DotaRain", NULL, NULL, NULL, NULL);
	HINTERNET hURL = InternetOpenUrl(hOpen, s2ws(URL).c_str(), NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, NULL);

	DWORD dwBytesRead =0;
	DWORD dwBytesWritten = 0;
	do {
		char* lpBuffer = new char[2000];
		ZeroMemory(lpBuffer, 2000);
		InternetReadFile(hURL, (LPVOID)lpBuffer, 2000, &dwBytesRead);
		WriteFile(file, (LPVOID)lpBuffer, dwBytesRead, &dwBytesWritten, NULL);
		delete[] lpBuffer;
		lpBuffer = NULL;
	} while (dwBytesRead);

	InternetCloseHandle(hURL);
	InternetCloseHandle(hOpen);
	CloseHandle(file);
	return path;
}