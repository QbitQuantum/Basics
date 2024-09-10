//////////////////////////////////////////////////////////
//
// RequiresAltTabFix
//
// Return true if there might be an alt-tab black screen problem when using gta_sa.exe
//
//////////////////////////////////////////////////////////
bool RequiresAltTabFix( void )
{
    // Exception for optimus because of better hi-perf detection when using gta_sa.exe
    if ( GetApplicationSettingInt( "nvhacks", "optimus" ) )
        return false;

    // Check for problem combo of: Windows 10 + NVidia card + full screen
    if ( IsWindows10OrGreater() && GetApplicationSettingInt( "nvhacks", "nvidia" ) )
    {
        // Slighty hacky way of checking in-game settings
        SString strCoreConfig;
        FileLoad( CalcMTASAPath( PathJoin( "mta", "config", "coreconfig.xml" ) ), strCoreConfig );
        int iWindowed        = atoi( strCoreConfig.SplitRight( "<display_windowed>" ) );
        int iFullscreenStyle = atoi( strCoreConfig.SplitRight( "<display_fullscreen_style>" ) );
        if ( iWindowed == 0 && iFullscreenStyle == 0 )   // 0=FULLSCREEN_STANDARD
            return true;        
    }
    return false;
}