///////////////////////////////////////////////////////////////
//
// CResourceChecker::CheckLuaFileForIssues
//
//
//
///////////////////////////////////////////////////////////////
void CResourceChecker::CheckLuaFileForIssues ( const string& strPath, const string& strFileName, const string& strResourceName, bool bClientScript )
{
    // Load the original file into a string
    SString strFileContents;

    // Open the file
    FileLoad ( strPath, strFileContents );
    if ( strFileContents.length () == 0 )
        return;

    // Update decrypt version requirements, and do no more checking if encrypted
    if ( CheckLuaDecryptRequirements( strFileContents, strFileName, strResourceName, bClientScript ) )
        return;

    // Check if a compiled script
    bool bCompiledScript = IsLuaCompiledScript( strFileContents.c_str(), strFileContents.length() );

    // Process
    if ( strFileContents.length () > 1000000 )
        CLogger::LogPrintf ( "Please wait...\n" );

    // Ouput warnings...
    if ( m_bUpgradeScripts == false )
    {
        CheckLuaSourceForIssues ( strFileContents, strFileName, strResourceName, bClientScript, bCompiledScript, ECheckerMode::WARNINGS );
    }
    else
    // ..or do an upgrade (if not compiled)
    if ( m_bUpgradeScripts == true && !bCompiledScript )
    {
        string strNewFileContents;
        CheckLuaSourceForIssues ( strFileContents, strFileName, strResourceName, bClientScript, bCompiledScript, ECheckerMode::UPGRADE, &strNewFileContents );

        // Has contents changed?
        if ( strNewFileContents.length () > 0 && strNewFileContents != strFileContents )
        {
            // Rename original to lua.old
            if( !RenameBackupFile( strPath, ".old" ) )
                return;

            // Save new content
            if ( FILE* pFile = fopen ( strPath.c_str (), "wb" ) )
            {
                fwrite ( strNewFileContents.c_str (), 1, strNewFileContents.length (), pFile );
                fclose ( pFile );
                CLogger::LogPrintf ( "Upgrading %s:%s ...........done\n", strResourceName.c_str (), strFileName.c_str () );

                m_upgradedFullPathList.push_back( strPath );
            }
        }
    }
}