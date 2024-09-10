static bool CheckPackages( RageFileDriverZip &fileDriver )
{
    int iErr;
    RageFileBasic *pFile = fileDriver.Open( "smzip.ctl", RageFile::READ, iErr );
    if( pFile == NULL )
        return true;

    IniFile ini;
    ini.ReadFile( *pFile );

    int version = 0;
    ini.GetValue( "SMZIP", "Version", version );
    if( version != 1 )
        return true;

    int cnt = 0;
    ini.GetValue( "Packages", "NumPackages", cnt );

    vector<RString> vsDirectories;
    for( int i = 0; i < cnt; ++i )
    {
        RString path;
        if( !ini.GetValue( "Packages", ssprintf("%i", i), path) )
            continue;

        /* Does this directory exist? */
        if( !FILEMAN->IsADirectory(path) )
            continue;

        if( !SMPackageUtil::IsValidPackageDirectory(path) )
            continue;

        vsDirectories.push_back(path);
    }

    if( vsDirectories.empty() )
        return true;

    {
        UninstallOld UninstallOldDlg;
        UninstallOldDlg.m_sPackages = join("\r\n", vsDirectories);
        int nResponse = UninstallOldDlg.DoModal();
        if( nResponse == IDCANCEL )
            return false;	// cancelled
        if( nResponse == IDIGNORE )
            return true;
    }

    char cwd_[MAX_PATH];
    _getcwd(cwd_, MAX_PATH);
    RString cwd(cwd_);
    if( cwd[cwd.size()-1] != '\\' )
        cwd += "\\";

    for( int i = 0; i < (int)vsDirectories.size(); ++i )
    {
        RString sDir = vsDirectories[i];
        sDir += "/";
        if( !DeleteRecursive(sDir) )	// error deleting
        {
            return false;
        }
    }

    return true;
}