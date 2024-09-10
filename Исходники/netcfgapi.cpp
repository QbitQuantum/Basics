HRESULT HrInstallNetComponent (IN INetCfg *pnc,
                               IN LPCWSTR lpszComponentId,
                               IN const GUID    *pguidClass,
                               IN LPCWSTR lpszInfFullPath)
{
    DWORD     dwError;
    HRESULT   hr = S_OK;
    WCHAR*     Drive = NULL;
    WCHAR*     Dir = NULL;
    WCHAR*     DirWithDrive = NULL;

    do
    {
        //
        // If full path to INF has been specified, the INF
        // needs to be copied using Setup API to ensure that any other files
        // that the primary INF copies will be correctly found by Setup API
        //

        if ( lpszInfFullPath ) {

            //
            // Allocate memory to hold the strings
            //
            Drive = (WCHAR*)CoTaskMemAlloc(_MAX_DRIVE * sizeof(WCHAR));
            if (NULL == Drive)
            {
                hr = E_OUTOFMEMORY;
                break;
            }
            ZeroMemory(Drive, _MAX_DRIVE * sizeof(WCHAR));

            Dir = (WCHAR*)CoTaskMemAlloc(_MAX_DIR * sizeof(WCHAR));
            if (NULL == Dir)
            {
                hr = E_OUTOFMEMORY;
                break;
            }
            ZeroMemory(Dir, _MAX_DRIVE * sizeof(WCHAR));

            DirWithDrive = (WCHAR*)CoTaskMemAlloc((_MAX_DRIVE + _MAX_DIR) * sizeof(WCHAR));
            if (NULL == DirWithDrive)
            {
                hr = E_OUTOFMEMORY;
                break;
            }               
            ZeroMemory(DirWithDrive, (_MAX_DRIVE + _MAX_DIR) * sizeof(WCHAR));

            //
            // Get the path where the INF file is.
            //

            _wsplitpath_s ( lpszInfFullPath,
                Drive,
                _MAX_DRIVE,
                Dir,
                _MAX_DIR,
                NULL,
                0,
                NULL,
                0);

            StringCchCopyW ( DirWithDrive,
                _MAX_DRIVE + _MAX_DIR,
                Drive );
            StringCchCatW ( DirWithDrive,
                _MAX_DRIVE + _MAX_DIR,
                Dir );

            //
            // Copy the INF file and other files referenced in the INF file.
            //

            if ( !SetupCopyOEMInfW(lpszInfFullPath,
                                   DirWithDrive,  // Other files are in the
                                                  // same dir. as primary INF
                                   SPOST_PATH,    // First param is path to INF
                                   0,             // Default copy style
                                   NULL,          // Name of the INF after
                                                  // it's copied to %windir%\inf
                                   0,             // Max buf. size for the above
                                   NULL,          // Required size if non-null
                                   NULL) ) {      // Optionally get the filename
                                                  // part of Inf name after it is copied.
                dwError = GetLastError();

                hr = HRESULT_FROM_WIN32( dwError );
            }
        }

        if ( S_OK == hr ) {

            //
            // Install the network component.
            //

            hr = HrInstallComponent( pnc,
                                     lpszComponentId,
                                     pguidClass );
            if ( hr == S_OK ) {

                //
                // On success, apply the changes
                //

                hr = pnc->Apply();
            }
        }

    #pragma warning(disable:4127) /* Conditional expression is constant */
    } while (false);

    if (Drive != NULL)
    {
        CoTaskMemFree(Drive);
        Drive = NULL;
    }
    if (Dir != NULL)
    {
        CoTaskMemFree(Dir);
        Dir = NULL;
    }
    if (DirWithDrive != NULL)
    {
        CoTaskMemFree(DirWithDrive);
        DirWithDrive = NULL;
    }    

    return hr;
}