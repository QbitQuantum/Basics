bool InstallChecker::verifyPackage( const QString &filePath, bool withUI )
{
    std::wstring path = QDir::toNativeSeparators( filePath ).toStdWString();

    BinaryCertificate c( path );
    if( c.subjectName() != "Estonian Informatics Centre" )
        return false;

    WINTRUST_FILE_INFO FileData;
    memset(&FileData, 0, sizeof(FileData));
    FileData.cbStruct = sizeof(WINTRUST_FILE_INFO);
    FileData.pcwszFilePath = path.c_str();
    GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;

    WINTRUST_DATA WinTrustData;
    memset(&WinTrustData, 0, sizeof(WinTrustData));
    WinTrustData.cbStruct = sizeof(WinTrustData);
    WinTrustData.dwUIChoice = withUI ? WTD_UI_ALL : WTD_UI_NONE;
    WinTrustData.fdwRevocationChecks = WTD_REVOKE_NONE;

    WinTrustData.dwUnionChoice = WTD_CHOICE_FILE;
    WinTrustData.dwProvFlags = WTD_SAFER_FLAG;
    WinTrustData.pFile = &FileData;

    switch( WinVerifyTrust( 0, &WVTPolicyGUID, &WinTrustData ) )
    {
    case ERROR_SUCCESS:
        return true;
    default:
        return false;
    }
}