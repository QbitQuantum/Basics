//////////////////////////////////////////////////////////
//
// CheckDataFiles
//
// Basic check for some essential files
//
//////////////////////////////////////////////////////////
void CheckDataFiles( void )
{
    const SString strMTASAPath = GetMTASAPath();
    const SString strGTAPath = GetGTAPath();

    const char* dataFilesFiles [] = { "MTA\\cgui\\images\\background_logo.png"
                                     ,"MTA\\cgui\\images\\radarset\\up.png"
                                     ,"MTA\\cgui\\images\\busy_spinner.png"
                                     ,"MTA\\cgui\\images\\rect_edge.png"
                                     ,"MTA\\D3DX9_42.dll"
                                     ,"MTA\\D3DCompiler_42.dll"
                                     ,"MTA\\bass.dll"
                                     ,"MTA\\bass_fx.dll"
                                     ,"MTA\\tags.dll"
                                     ,"MTA\\sa.dat"
                                     ,"MTA\\XInput9_1_0_mta.dll"
                                     ,"MTA\\vea.dll"};

    for ( uint i = 0 ; i < NUMELMS( dataFilesFiles ) ; i++ )
    {
        if ( !FileExists ( PathJoin( strMTASAPath, dataFilesFiles [ i ] ) ) )
        {
            DisplayErrorMessageBox ( _("Load failed. Please ensure that the latest data files have been installed correctly."), _E("CL16"), "mta-datafiles-missing" );
            return ExitProcess( EXIT_ERROR );
        }
    }

    if ( FileSize ( PathJoin( strMTASAPath, "MTA", "bass.dll" ) ) != 0x0001A440 )
    {
        DisplayErrorMessageBox ( _("Load failed. Please ensure that the latest data files have been installed correctly."), _E("CL17"), "mta-datafiles-missing" );
        return ExitProcess( EXIT_ERROR );
    }

    // Check for client file
    if ( !FileExists ( PathJoin( strMTASAPath, CHECK_DM_CLIENT_NAME ) ) )
    {
        DisplayErrorMessageBox ( SString(_("Load failed. Please ensure that %s is installed correctly."),CHECK_DM_CLIENT_NAME), _E("CL18"), "client-missing" );
        return ExitProcess( EXIT_ERROR );
    }

    // Make sure the gta executable exists
    if ( !FileExists( PathJoin( strGTAPath, MTA_GTAEXE_NAME ) ) )
    {
        DisplayErrorMessageBox ( SString ( _("Load failed. Could not find gta_sa.exe in %s."), strGTAPath.c_str () ), _E("CL20"), "gta_sa-missing" );
        return ExitProcess( EXIT_ERROR );
    }

    // Make sure important dll's do not exist in the wrong place
    const char* dllCheckList[] = { "xmll.dll", "cgui.dll", "netc.dll", "libcurl.dll", "pthread.dll" };
    for ( int i = 0 ; i < NUMELMS ( dllCheckList ); i++ )
    {
        if ( FileExists( PathJoin( strGTAPath, dllCheckList[i] ) ) )
        {
            DisplayErrorMessageBox ( SString ( _("Load failed. %s exists in the GTA directory. Please delete before continuing."), dllCheckList[i] ), _E("CL21"), "file-clash" );
            return ExitProcess( EXIT_ERROR );
        }    
    }

    // Check main exe has the correct name
    if ( GetLaunchFilename().CompareI( MTA_EXE_NAME ) == false )
    {
        SString strMessage( _("Main file has an incorrect name (%s)"), *GetLaunchFilename() );
        int iResponse = MessageBoxUTF8 ( NULL, strMessage, _("Error")+_E("CL33"), MB_RETRYCANCEL | MB_ICONERROR | MB_TOPMOST  );
        ReleaseSingleInstanceMutex ();
        if ( iResponse == IDRETRY )
            ShellExecuteNonBlocking( "open", PathJoin ( strMTASAPath, MTA_EXE_NAME ) );            
        return ExitProcess( EXIT_ERROR );
    }

    // Check for possible virus file changing activities
    if ( !VerifyEmbeddedSignature( PathJoin( strMTASAPath, MTA_EXE_NAME ) ) )
    {
        SString strMessage( _("Main file is unsigned. Possible virus activity.\n\nSee online help if MTA does not work correctly.") );
        #if MTASA_VERSION_BUILD > 0 && defined(MTA_DM_CONNECT_TO_PUBLIC) && !defined(MTA_DEBUG)
            DisplayErrorMessageBox( strMessage, _E("CL29"), "maybe-virus1" );
        #endif
    }

    struct {
        const char* szMd5;
        const char* szFilename;
    } integrityCheckList[] = { { "9586E7BE6AE8016932038932D1417241", "bass.dll", },
                               { "B2E49F0C22C8B7D92D615F942BA19353", "bass_aac.dll", },
                               { "569C60F8397C34034E685A303B7404C0", "bass_ac3.dll", },
                               { "0E44BCAC0E940DB2BFB13448E96E4B29", "bass_fx.dll", },
                               { "50AF8A7D49E83A723ED0F70FB682DCFB", "bassflac.dll", },
                               { "BEBA64522AA8265751187E38D1FC0653", "bassmidi.dll", },
                               { "99F4F38007D347CEED482B7C04FDD122", "bassmix.dll", },
                               { "7B52BE6D702AA590DB57A0E135F81C45", "basswma.dll", }, 
                               { "38D7679D3B8B6D7F16A0AA9BF2A60043", "tags.dll", },
                               { "309D860FC8137E5FE9E7056C33B4B8BE", "vea.dll", },
                               { "0602F672BA595716E64EC4040E6DE376", "vog.dll", },
                               { "B37D7DF4A1430DB65AD3EA84801F9EC3", "vvo.dll", },
                               { "47FF3EE45DE53528F1AFD9F5982DF8C7", "vvof.dll", },
                               { "ADFB6D7B61E301761C700652B6FE7CCD", "XInput9_1_0_mta.dll", }, };
    for ( int i = 0 ; i < NUMELMS ( integrityCheckList ); i++ )
    {
        SString strMd5 = CMD5Hasher::CalculateHexString( PathJoin( strMTASAPath, "mta", integrityCheckList[i].szFilename ) );
        if ( !strMd5.CompareI( integrityCheckList[i].szMd5 ) )
        {
            DisplayErrorMessageBox( _("Data files modified. Possible virus activity.\n\nSee online help if MTA does not work correctly."), _E("CL30"), "maybe-virus2" );
            break;
        }    
    }

    // Check for asi files
    {
        bool bFoundInGTADir = !FindFiles( PathJoin( strGTAPath, "*.asi" ), true, false ).empty();
        bool bFoundInMTADir = !FindFiles( PathJoin( strMTASAPath, "mta", "*.asi" ), true, false ).empty();
        if ( bFoundInGTADir || bFoundInMTADir )
        {
            DisplayErrorMessageBox (_( ".asi files are in the 'MTA:SA' or 'GTA: San Andreas' installation directory.\n\n"
                                       "Remove these .asi files if you experience problems with MTA:SA." ), _E("CL28"), "asi-files" );
        }
    }

    // Warning if d3d9.dll exists in the GTA install directory
    if ( FileExists( PathJoin ( strGTAPath, "d3d9.dll" ) ) )
    {
        ShowD3dDllDialog ( g_hInstance, PathJoin ( strGTAPath, "d3d9.dll" ) );
        HideD3dDllDialog ();
    }

    // Remove old log files saved in the wrong place
    SString strMtaDir = PathJoin( strMTASAPath, "mta" );
    if ( strGTAPath.CompareI( strMtaDir ) == false )
    {
        FileDelete( PathJoin( strGTAPath, "CEGUI.log" ) );
        FileDelete( PathJoin( strGTAPath, "logfile.txt" ) );
        FileDelete( PathJoin( strGTAPath, "shutdown.log" ) );
    }
}