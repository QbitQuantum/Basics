bool LoadSessionData(
    IN MRABase& _db,
    IN MAKFC_CString databaseKey, 
    OUT MAKFC_CString& sDevId, 
    OUT MAKFC_CString& sA, 
    OUT MAKFC_CString& sSessionKey, 
    OUT MAKFC_CString& ts)
{
    gigabase::dbArray<gigabase::byte> data;
    if ( !_db.ReadRawData( tstring(databaseKey.NetStrW()), L"", ICQ_PARTNERS_LOGIN_DATA, data ) )
    {
        return false;
    }

    MAKFC_CString sCookies = (LPCWSTR) data.get();
    if ( !sCookies.Len() )
        return false;

    int iStart1 = 0;
    MAKFC_CString sToken1;

    while ( ( sToken1 = sCookies.Tokenize( L";", iStart1 ) ).GetLength() )
    {
        int iStart2 = 0;
        MAKFC_CString sLeft = sToken1.Tokenize( L"=", iStart2 );
        MAKFC_CString sRight = sToken1.Mid( iStart2 );

        if ( sLeft == L"k" )
            sDevId = sRight;
        else if ( sLeft == L"a" )
            sA = sRight;
        else if ( sLeft == L"session_key" )
            sSessionKey = sRight;
        else if ( sLeft == L"time_offset" )
        {
            __int64 offset = _wtoi64( sRight );
            time_t tt = 0;
            FileTimeToUnixTime( &tt, CFileTime( CFileTime::GetCurrentTime().GetTime() - offset ) );
            ts.Format( L"%d", (DWORD) tt );
        }
    }

    return true;
}