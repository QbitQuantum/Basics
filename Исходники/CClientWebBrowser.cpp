bool CClientWebBrowser::Events_OnResourceFileCheck ( const SString& strPath )
{
    // If no resource is set, we do not require to verify the file
    if ( !m_pResource )
        return true;
    
    auto pFile = g_pClientGame->GetResourceManager ()->GetDownloadableResourceFile ( strPath.ToLower() );

    // If we did not download this file, it has been script or user generated, nothing to verify for us
    if ( pFile == nullptr )
        return true;

    pFile->GenerateClientChecksum ();
    return pFile->DoesClientAndServerChecksumMatch ();
}