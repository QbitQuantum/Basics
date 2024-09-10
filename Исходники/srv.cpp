DWORD CServer::GetGroupCount()
{
    DWORD dwGroupCount=0;
    HANDLE hToken = INVALID_HANDLE_VALUE;
    hToken = GetToken();
    if(hToken!=INVALID_HANDLE_VALUE)
    {
        DWORD dwNeeded=0;
        BOOL bRes=GetTokenInformation(hToken,
                                      TokenStatistics,
                                      NULL,
                                      0,
                                      &dwNeeded
                                      );
        if(bRes==FALSE && GetLastError()==ERROR_INSUFFICIENT_BUFFER)
        {
            TOKEN_STATISTICS* pBuffer=reinterpret_cast<TOKEN_STATISTICS*>( new BYTE[dwNeeded]);
            if(pBuffer!=NULL)
            {
                BOOL bRes=GetTokenInformation(hToken,
                                              TokenStatistics,
                                              (LPVOID)pBuffer,
                                              dwNeeded,
                                              &dwNeeded
                                              );
                if(bRes==TRUE)
                {
                    dwGroupCount=pBuffer->GroupCount;
                }
            }
            delete[] pBuffer;
        }
        CloseHandle(hToken);
    }
    return dwGroupCount;
}