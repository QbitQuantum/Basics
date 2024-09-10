/**
 * Sends data to the Web Service.
 *
 * @param InputData
 * A std::string containing all the data, which is going to be submitted as HTTP POST data.
 *
 * @return
 * Returns a pointer to a char array containing the data received from the Web Service.
 * The caller needs to free that pointer.
 */
PCHAR
CWebService::DoRequest(const string& InputData)
{
    const WCHAR szHeaders[] = L"Content-Type: application/x-www-form-urlencoded";

    auto_array_ptr<char> Data;
    DWORD DataLength;

    /* Post our test results to the web service */
    m_hHTTPRequest = HttpOpenRequestW(m_hHTTP, L"POST", szServerFile, NULL, NULL, NULL, INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);

    if(!m_hHTTPRequest)
        FATAL("HttpOpenRequestW failed\n");

    Data.reset(new char[InputData.size() + 1]);
    strcpy(Data, InputData.c_str());

    if(!HttpSendRequestW(m_hHTTPRequest, szHeaders, wcslen(szHeaders), Data, InputData.size()))
        FATAL("HttpSendRequestW failed\n");

    /* Get the response */
    if(!InternetQueryDataAvailable(m_hHTTPRequest, &DataLength, 0, 0))
        FATAL("InternetQueryDataAvailable failed\n");

    Data.reset(new char[DataLength + 1]);

    if(!InternetReadFile(m_hHTTPRequest, Data, DataLength, &DataLength))
        FATAL("InternetReadFile failed\n");

    Data[DataLength] = 0;

    return Data.release();
}