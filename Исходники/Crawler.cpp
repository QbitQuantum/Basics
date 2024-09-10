//THIE MODULE WILL DOWNLOAD THE WEBPAGE IN THE FORM OF HTML FORMAT 
void Crawler::downloader(wstring url)
{
	CoInitialize(NULL);
	//CONVERSION OF WSTRING FORMAT TO LPCWSTR FORMAT 
	LPCWSTR _url = url.c_str();
	//FUNCTION CALL FOR DOWNLOADING THE WEBPAGE FROM THE GIVEN URL
	HRESULT result = URLDownloadToFileW(NULL, _url,cachePath, 0, NULL);
	if (SUCCEEDED(result))
	{
		cout << "FILE DOWNLOAD COMPLETE" << endl;
	}
	else
	{
		cout << "FILE DOWNLOAD ERROR" << endl;
	}
}