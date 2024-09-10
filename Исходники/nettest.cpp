bool TestWininet(std::string url){
    HINTERNET hNet = InternetOpenA(NULL,
                                   INTERNET_OPEN_TYPE_PRECONFIG,
                                   NULL,
                                   NULL,
                                   0);
    if (hNet == NULL)
    {
        std::cout << "InternetOpenA error :" << ::GetLastError() << std::endl;
        return false;
    }

	// 默认TIMEOUT时间2秒
    static DWORD dwTimeout = 2000;
	static DWORD dwRetries = 3;
    InternetSetOptionA(hNet, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeout, sizeof(DWORD));
    InternetSetOptionA(hNet, INTERNET_OPTION_CONNECT_RETRIES, &dwRetries, sizeof(DWORD));

    HINTERNET hUrlFile = InternetOpenUrlA(hNet, 
                                          url.c_str(), 
                                          NULL,
                                          0,
                                          INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_RELOAD,
                                          0);
    if (hUrlFile == NULL)
    {        
        std::cout << url << "InternetOpenUrlA error :" << ::GetLastError() << std::endl;
 		InternetCloseHandle(hNet);
        return false;
    }
    
 	InternetCloseHandle(hUrlFile);
    InternetCloseHandle(hNet) ;
    return true;
}