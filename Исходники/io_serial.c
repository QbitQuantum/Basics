static int fb_hSerialWaitSignal( HANDLE hDevice, DWORD dwMask, DWORD dwResult, DWORD dwTimeout )
{
    DWORD dwStartTime = GET_MSEC_TIME();
    DWORD dwModemStatus = 0;

    if( !GetCommModemStatus( hDevice, &dwModemStatus ) )
        return FALSE;

    while ( ((GET_MSEC_TIME() - dwStartTime) <= dwTimeout)
            && ((dwModemStatus & dwMask)!=dwResult) )
    {
        if( !GetCommModemStatus( hDevice, &dwModemStatus ) )
            return FALSE;
    }
    return ((dwModemStatus & dwMask)==dwResult);
}