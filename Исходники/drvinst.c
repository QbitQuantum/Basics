int __cdecl	
_tmain( 
    int argc, 
    TCHAR* argv[] 
    )
{
    TCHAR DestPath[MAX_PATH];
    ULONG Size = MAX_PATH;
    TCHAR * InfPath = NULL;
	TCHAR DriverPackageInfPath[MAX_PATH];
    DWORD Ret;
    TCHAR Option;
    BOOL NeedRebootDev = FALSE;
    BOOL NeedRebootDrvPkg = FALSE;
    DWORD Flags = 0;  
    LPTSTR lpFilePart;
    int i;
    DWORD dw;
    Size = MAX_PATH;
    
    _tprintf( TEXT("Driver Installer Sample Program\n") ); 
    if( argc < 3 )
    {
        _tprintf( TEXT("USAGE: drvinst /i /c /r /g <inf-filename> [Flag(s)]\n") );
        _tprintf( TEXT("\nOptions:\n"));
        _tprintf( TEXT("/i : re-install driver package and devices if presented.\n") );
        _tprintf( TEXT("/u : uninstall devices and driver package.\n") );
        _tprintf( TEXT("/g : get installed driver package path.\n") );

        _tprintf( TEXT("\n<inf-filename> : path to the inf file.\n") );
        _tprintf( TEXT("\nFlags:\n"));
        _tprintf( TEXT("DRIVER_PACKAGE_REPAIR:                 0x00000001 ( 1)\n"));
        _tprintf( TEXT("DRIVER_PACKAGE_SILENT:                 0x00000002 ( 2)\n"));
        _tprintf( TEXT("DRIVER_PACKAGE_FORCE:                  0x00000004 ( 4)\n"));
        _tprintf( TEXT("DRIVER_PACKAGE_ONLY_IF_DEVICE_PRESENT: 0x00000008 ( 8)\n"));
        _tprintf( TEXT("DRIVER_PACKAGE_LEGACY:                 0x00000010 (16)\n"));
        _tprintf( TEXT("DRIVER_PACKAGE_DELETE_FILES:           0x00000020 (32)\n"));
        
        return 0;
    }

    //
    // Get command line choices
    //

    //
    // The code suppresses the warning 28193 for the call to _totlower.
    // This suppression is done because that function has a check return
    // annotation on it.  However, it doesn't return an error code
    // and the check return annotation is really being used to indicate
    // that the return value of the function should be looked at and/or 
    // assigned to a variable. The check return annotation means the return
    // value should always be checked in all code paths.  The return value is
    // assigned to a variable, but the return in the for loop could cause
    // this function to exit before Option is ever examined.  For that case,
    // the code doesn't need to check the value of Option so the warning
    // is being suppressed
    //
#pragma warning( suppress: 28193)
    Option = (TCHAR)_totlower(argv[1][1]);
	InfPath = argv[2];

    for ( i = 3; i<argc; i++ ){
        dw = _ttol( argv[i] );
        //
        // Either an error occurred during conversion of a flags parameter 
        // into a long or a flag of 0 was specified.  Either way,
        // this is invalid input.
        //
        if (0 == dw)
        {
            _tprintf( TEXT("An invalid flag was specified.") );
            
            return 0;
        }

        Flags |= dw;
    }


    GetFullPathName( InfPath, MAX_PATH, DriverPackageInfPath, &lpFilePart);  
    
    _tprintf( TEXT("INFO: Option \"/%c\"\n"), Option );    
    _tprintf( TEXT("INFO: Input file \"%s\"\n"), DriverPackageInfPath );
    _tprintf( TEXT("INFO: Flags 0x%X (%u)\n\n"), Flags, Flags );

    
    DIFXAPISetLogCallback( LogCallback, (PVOID)NULL );
    
    Ret = ERROR_SUCCESS;

    if ( TEXT('u') == Option )
    {
        _tprintf( TEXT("INFO: uninstalling devices.\n"));

        if ( TRUE == RemoveDevices( &NeedRebootDev ) ) {
            _tprintf( TEXT("SUCCESS: uninstalled devices.\n") );

        }
        else {
            _tprintf( TEXT("ERROR: failed.\n") );
            Ret = !ERROR_SUCCESS;
        }

        if ( ERROR_SUCCESS == Ret ) {
            _tprintf( TEXT("INFO: uninstalling driver package.\n"));    

            Ret = DriverPackageUninstall(  
                        DriverPackageInfPath,
                        Flags,
                        NULL,
                        &NeedRebootDrvPkg);

            if( ERROR_SUCCESS == Ret ){
                _tprintf( TEXT("SUCCESS: uninstalled driver package %s.\n"), DriverPackageInfPath );
            } else {
                _tprintf( TEXT("ERROR: failed with error code 0x%X\n"), Ret );
            }
        
            if ( NeedRebootDev || NeedRebootDrvPkg ) {
                _tprintf( TEXT("INFO: Machine will have to be rebooted to complete uninstall.") );
            }
        }
    }
    else if ( TEXT('i') == Option )
    {
        _tprintf( TEXT("DRVINST: installing drivers.\n"));
        
        /* http://msdn.microsoft.com/en-us/library/windows/hardware/ff552293(v=vs.85).aspx
           
        */
        
        // step1 - Checking for In-Progress Installations
        if ( WAIT_OBJECT_0 != CMP_WaitNoPendingInstallEvents ( 0 ) ) {
        	_tprintf( TEXT("ERROR: There are pending installation activities or some error happened when checking CMP_WaitNoPendingInstallEvents\n") );
					goto final_main;
        }
        
        /*
           step2 - Determine whether a device is plugged in.
           step3 - Preinstall driver packages
        	 If we use DIFx API, will save our time, otherwise we must follow the MSDN regarding step2 and step3
        	 
        */
        Ret = DriverPackageInstall( 
                    DriverPackageInfPath, 
                    Flags,
                    NULL,
                    &NeedRebootDrvPkg);

        if( ERROR_SUCCESS == Ret ){
            _tprintf( TEXT("SUCCESS: installed package %s.\n"), DriverPackageInfPath );
        } else if (ERROR_NO_MORE_ITEMS == Ret){
            _tprintf( TEXT("INFO: All devices found already have a better driver than what is contained in the specified inf file. To force an install, use the ForceIfNotBetter flag.\n"));
        } else if (ERROR_NO_SUCH_DEVINST == Ret){
            _tprintf( TEXT("INFO: There aren't any live devnodes with the DeviceId contained in the INF.\n"));
        }
        else{
            _tprintf( TEXT("ERROR: failed with error code 0x%X\n"), Ret );
        }

        if (NeedRebootDrvPkg){
            _tprintf( TEXT("INFO: Machine will have to be rebooted to complete install.") );
        }
    }
    else if ( TEXT('g') == Option )
    {  
        _tprintf( TEXT("TEST: getting driver package path.\n")); 
        Ret = DriverPackageGetPath( DriverPackageInfPath, DestPath, &Size );
        if ( ERROR_SUCCESS==Ret ){
            _tprintf( TEXT("INFO: INF path is %s\n"), DestPath );    
        } else {
            _tprintf( TEXT("ERROR: failed with error code 0x%X\n"), Ret );
        }
    } else {
        _tprintf( TEXT("ERROR: invalid command line option /%c.\n"), Option );
    }

final_main:
    DIFXAPISetLogCallback( NULL, (PVOID)NULL );
    
    return 1;
}