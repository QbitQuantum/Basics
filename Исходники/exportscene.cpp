ExportScene::ExportScene()
: ExportFrame(),
  m_pDCCTransformer( nullptr )
{
    m_Information.ExportTime = _time64( nullptr );
    CHAR strDomain[50];
    size_t BufferSize = ARRAYSIZE(strDomain);
    getenv_s( &BufferSize, strDomain, ARRAYSIZE(strDomain), "USERDOMAIN" );
    CHAR strUsername[50];
    getenv_s( &BufferSize, strUsername, ARRAYSIZE(strUsername), "USERNAME" );
    CHAR strTemp[256];
    sprintf_s( strTemp, "%s\\%s", strDomain, strUsername );
    m_Information.UserName = strTemp;
    CHAR strComputerName[100];
    BufferSize = ARRAYSIZE(strComputerName);
    getenv_s( &BufferSize, strComputerName, ARRAYSIZE(strComputerName), "COMPUTERNAME" );
    m_Information.MachineName = strComputerName;
    OSVERSIONINFO OSVersion = { 0 };
    OSVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
#pragma prefast (disable : 28159)
#pragma warning (suppress : 4996)
    GetVersionEx( &OSVersion );
    sprintf_s( strTemp, "Windows NT %u.%u build %u", OSVersion.dwMajorVersion, OSVersion.dwMinorVersion, OSVersion.dwBuildNumber );
    m_Information.PlatformName = strTemp;
}