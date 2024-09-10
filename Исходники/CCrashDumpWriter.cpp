void CCrashDumpWriter::DumpMiniDump ( _EXCEPTION_POINTERS* pException, CExceptionInformation* pExceptionInformation )
{
    WriteDebugEvent ( "CCrashDumpWriter::DumpMiniDump" );

    // Try to load the DLL in our directory
    HMODULE hDll = NULL;
    char szDbgHelpPath [MAX_PATH];
    if ( GetModuleFileNameA ( NULL, szDbgHelpPath, MAX_PATH ) )
    {
        char* pSlash = _tcsrchr ( szDbgHelpPath, '\\' );
        if ( pSlash )
        {
            _tcscpy ( pSlash + 1, "DBGHELP.DLL" );
            hDll = LoadLibrary ( szDbgHelpPath );
        }
    }

    // If we couldn't load the one in our dir, load any version available
    if ( !hDll )
    {
        hDll = LoadLibrary( "DBGHELP.DLL" );
    }

    if ( !hDll )
        AddReportLog( 9201, "CCrashDumpWriter::DumpMiniDump - Could not load DBGHELP.DLL" );

    // We could load a dll?
    if ( hDll )
    {
        // Grab the MiniDumpWriteDump proc address
        MINIDUMPWRITEDUMP pDump = reinterpret_cast < MINIDUMPWRITEDUMP > ( GetProcAddress( hDll, "MiniDumpWriteDump" ) );
        if ( !pDump )
            AddReportLog( 9202, "CCrashDumpWriter::DumpMiniDump - Could not find MiniDumpWriteDump" );

        if ( pDump )
        {
            // Create the file
            HANDLE hFile = CreateFile ( CalcMTASAPath ( "mta\\core.dmp" ), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
            if ( hFile == INVALID_HANDLE_VALUE )
                AddReportLog( 9203, SString( "CCrashDumpWriter::DumpMiniDump - Could not create '%s'", *CalcMTASAPath ( "mta\\core.dmp" ) ) );

            if ( hFile != INVALID_HANDLE_VALUE )
            {
                // Create an exception information struct
                _MINIDUMP_EXCEPTION_INFORMATION ExInfo;
                ExInfo.ThreadId = GetCurrentThreadId ();
                ExInfo.ExceptionPointers = pException;
                ExInfo.ClientPointers = FALSE;

                // Write the dump
                BOOL bResult = pDump ( GetCurrentProcess(), GetCurrentProcessId(), hFile, (MINIDUMP_TYPE)( MiniDumpNormal | MiniDumpWithIndirectlyReferencedMemory ), &ExInfo, NULL, NULL );

                if ( !bResult )
                    AddReportLog( 9204, SString( "CCrashDumpWriter::DumpMiniDump - MiniDumpWriteDump failed (%08x)", GetLastError() ) );
                else
                    WriteDebugEvent ( "CCrashDumpWriter::DumpMiniDump - MiniDumpWriteDump succeeded" );

                // Close the dumpfile
                CloseHandle ( hFile );

                // Grab the current time
                // Ask windows for the system time.
                SYSTEMTIME SystemTime;
                GetLocalTime ( &SystemTime );

                // Create the dump directory
                CreateDirectory ( CalcMTASAPath ( "mta\\dumps" ), 0 );
                CreateDirectory ( CalcMTASAPath ( "mta\\dumps\\private" ), 0 );

                SString strModuleName = pExceptionInformation->GetModuleBaseName ();
                strModuleName = strModuleName.ReplaceI ( ".dll", "" ).Replace ( ".exe", "" ).Replace ( "_", "" ).Replace ( ".", "" ).Replace ( "-", "" );
                if ( strModuleName.length () == 0 )
                    strModuleName = "unknown";

                SString strMTAVersionFull = SString ( "%s.%s", MTA_DM_BUILDTAG_LONG, *GetApplicationSetting ( "mta-version-ext" ).SplitRight ( ".", NULL, -2 ) );
                SString strSerialPart = GetApplicationSetting ( "serial" ).substr ( 0, 5 );
                uint uiServerIP = GetApplicationSettingInt ( "last-server-ip" );
                uint uiServerPort = GetApplicationSettingInt ( "last-server-port" );
                int uiServerTime = GetApplicationSettingInt ( "last-server-time" );
                int uiServerDuration = _time32 ( NULL ) - uiServerTime;
                uiServerDuration = Clamp ( 0, uiServerDuration + 1, 0xfff );

                // Get path to mta dir
                SString strPathCode;
                {
                    std::vector < SString > parts;
                    PathConform ( CalcMTASAPath ( "" ) ).Split ( PATH_SEPERATOR, parts );
                    for ( uint i = 0 ; i < parts.size () ; i++ )
                    {
                        if ( parts[i].CompareI ( "Program Files" ) )
                            strPathCode += "Pr";
                        else
                        if ( parts[i].CompareI ( "Program Files (x86)" ) )
                            strPathCode += "Px";
                        else
                        if ( parts[i].CompareI ( "MTA San Andreas" ) )
                            strPathCode += "Mt";
                        else
                        if ( parts[i].BeginsWithI ( "MTA San Andreas" ) )
                            strPathCode += "Mb";
                        else
                            strPathCode += parts[i].Left ( 1 ).ToUpper ();
                    }
                }

                // Ensure filename parts match up with EDumpFileNameParts
                SString strFilename ( "mta\\dumps\\private\\client_%s_%s_%08x_%x_%s_%08X_%04X_%03X_%s_%04d%02d%02d_%02d%02d.dmp",
                                             strMTAVersionFull.c_str (),
                                             strModuleName.c_str (),
                                             pExceptionInformation->GetAddressModuleOffset (),
                                             pExceptionInformation->GetCode () & 0xffff,
                                             strPathCode.c_str (),
                                             uiServerIP,
                                             uiServerPort,
                                             uiServerDuration,
                                             strSerialPart.c_str (),
                                             SystemTime.wYear,
                                             SystemTime.wMonth,
                                             SystemTime.wDay,
                                             SystemTime.wHour,
                                             SystemTime.wMinute
                                           );

                SString strPathFilename = CalcMTASAPath ( strFilename );

                // Copy the file
                CopyFile ( CalcMTASAPath ( "mta\\core.dmp" ), strPathFilename, false );

                // For the dump uploader
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "none" );
                SetApplicationSetting ( "diagnostics", "last-dump-save", strPathFilename );

                // Try to append pool sizes info to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-pools" );
                CBuffer poolInfo;
                GetPoolInfo ( poolInfo );
                AppendToDumpFile ( strPathFilename, poolInfo, 'POLs', 'POLe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-pools" );

                // Try to append d3d state info to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-d3d" );
                CBuffer d3dInfo;
                GetD3DInfo ( d3dInfo );
                AppendToDumpFile ( strPathFilename, d3dInfo, 'D3Ds', 'D3De' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-d3d" );

                // Try to append crash averted stats to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-crash-averted" );
                CBuffer crashAvertedStats;
                GetCrashAvertedStats ( crashAvertedStats );
                AppendToDumpFile ( strPathFilename, crashAvertedStats, 'CASs', 'CASe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-crash-averted" );

                // Try to append log info to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-log" );
                CBuffer logInfo;
                GetLogInfo ( logInfo );
                AppendToDumpFile ( strPathFilename, logInfo, 'LOGs', 'LOGe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-log" );

                // Try to append dx info to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-misc" );
                CBuffer dxInfo;
                GetDxInfo ( dxInfo );
                AppendToDumpFile ( strPathFilename, dxInfo, 'DXIs', 'DXIe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-misc" );

                // Try to append misc info to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-misc" );
                CBuffer miscInfo;
                GetMiscInfo ( miscInfo );
                AppendToDumpFile ( strPathFilename, miscInfo, 'MSCs', 'MSCe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-misc" );

                // Try to append memory info to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-mem" );
                CBuffer memInfo;
                GetMemoryInfo ( memInfo );
                AppendToDumpFile ( strPathFilename, memInfo, 'MEMs', 'MEMe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-mem" );

                // Try to logfile.txt to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-logfile" );
                CBuffer logfileContent;
                logfileContent.LoadFromFile( CalcMTASAPath( PathJoin( "mta", "logs", "logfile.txt" ) ) );
                AppendToDumpFile ( strPathFilename, logfileContent, 'LOGs', 'LOGe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-logfile" );

                // Try to report.log to dump file
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "try-report" );
                CBuffer reportLogContent;
                reportLogContent.LoadFromFile( PathJoin( GetMTADataPath(), "report.log" ) );
                AppendToDumpFile ( strPathFilename, reportLogContent, 'REPs', 'REPe' );
                SetApplicationSetting ( "diagnostics", "last-dump-extra", "added-report" );
            }
        }

        // Free the DLL again
        FreeLibrary ( hDll );
    }

    // Auto-fixes

    // Check if crash was in volumetric shadow code
    if ( ms_uiInCrashZone == 1 || ms_uiInCrashZone == 2 )
    {
        CVARS_SET( "volumetric_shadows", false );
        CCore::GetSingleton().SaveConfig();
        AddReportLog( 9205, "Disabled volumetric shadows" );
    }

    CNet* pNet = CCore::GetSingleton().GetNetwork();
    if ( pNet )
        pNet->PostCrash();    
}