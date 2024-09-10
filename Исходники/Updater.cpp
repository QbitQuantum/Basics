int P3DUpdateManager::CheckForUpdates(const char* bugServer)
{
    if (!CVe_updates.GetBool()) return false;

    char *query = new char[128];
    char *outResult = new char[1024];

    sprintf(query, "%s/?a=d&v1=%d&v2=%d&v3=%d&v4=%d", bugServer, P3DVER_1, P3DVER_2, P3DVER_3, P3DVER_4);
    //do
    //{
    HINTERNET hInet = InternetOpen("P3DUP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET hFile = InternetOpenUrl(hInet, query, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hInet || !hFile) return 0;
    DWORD size;
    outResult[0]=0;
    if (!InternetReadFile(hFile, outResult, 1023, &size))
        return 0;
    outResult[size]=0;
    if (!InternetCloseHandle(hFile)) return 0;
    if (!InternetCloseHandle(hInet)) return 0;
    //}while(outResult[0]==0);

    // zjisti pocet updatu
    unsigned int lastPos=0;
    for (unsigned int i=0; i<strlen(outResult); i++)
    {
        if (outResult[i]==';')
        {
            char* tmpChar = new char[i-lastPos+1];
            strncpy(tmpChar, &outResult[lastPos], i-lastPos);
            tmpChar[i-lastPos]=0;
            m_pUpdLinks.push_back(tmpChar);

            lastPos = i+1;
            m_nUpdates++;
        }
    }

    delete[] query;
    delete[] outResult;

    return m_nUpdates;
    return 0;
}