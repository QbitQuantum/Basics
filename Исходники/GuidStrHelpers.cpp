GUID Inf2ClassGUID( __inout std::wstring& pathName, __out std::wstring& classStr ) {

    GUID ClassGUID;
    wchar_t ClassName[1+MAX_CLASS_NAME_LEN];
    std::vector< wchar_t > InfPath( 0 );
    DWORD pathSize = MAX_PATH;
    ClassName[MAX_CLASS_NAME_LEN] = L'\0';

    while ( pathSize > InfPath.size() ) {

        InfPath.resize( 1 + pathSize );

        pathSize = GetFullPathName(pathName.c_str(), static_cast<DWORD>(InfPath.size()) ,&InfPath[0], NULL);

        if ( 0 == pathSize ) {
            HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );
            LogResult( hr, "GetFullPathName('%ls') Failed", pathName.c_str() );
            throw hr;
        }
    }

    //
    // Use the INF File to extract the Class GUID.
    //
    if (!SetupDiGetINFClassW(&InfPath[0],&ClassGUID,ClassName,sizeof(ClassName)/sizeof(ClassName[0]),0))
    {
        HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );
        LogResult( hr, "SetupDiGetINFClass('%ls') Failed", &InfPath[0] );
        throw hr;
    }

    pathName = &InfPath[0];
    classStr = ClassName;
    return ClassGUID;

} //GUID Inf2ClassGUID( __in const std::wstring& pathName )