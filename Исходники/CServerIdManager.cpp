///////////////////////////////////////////////////////////////
//
// CServerIdManagerImpl::GetConnectionPrivateDirectory
//
//
//
///////////////////////////////////////////////////////////////
SString CServerIdManagerImpl::GetConnectionPrivateDirectory ( bool bPreviousVer )
{
    // Get ServerId for this connection
    SString strServerId = g_pCore->GetNetwork ()->GetCurrentServerId ( bPreviousVer );

    // If ServerId is invalid, use the temp dir
    if ( strServerId.length () < 10 )
        return bPreviousVer ? "" : m_strTempErrorDir;

    // Otherwise fetch the server unique dir
    const CServerIdInfo& info = GetServerIdInfo ( strServerId );
    return PathJoin ( m_strServerIdLookupBaseDir, info.strDir );
}