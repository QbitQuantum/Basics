/**
 * Executes a sepcified .INF section to install/uninstall drivers and/or services.
 *
 * @return  Exit code (EXIT_OK, EXIT_FAIL)
 * @param   pszSection          Section to execute; usually it's "DefaultInstall".
 * @param   iMode               Execution mode to use (see MSDN).
 * @param   pszInf              Full qualified path of the .INF file to use.
 */
int ExecuteInfFile(const _TCHAR *pszSection, int iMode, const _TCHAR *pszInf)
{
    _tprintf(_T("Installing from INF-File: %ws (Section: %ws) ...\n"),
             pszInf, pszSection);

    UINT uErrorLine = 0;
    HINF hINF = SetupOpenInfFile(pszInf, NULL, INF_STYLE_WIN4, &uErrorLine);
    if (hINF != INVALID_HANDLE_VALUE)
    {
        PVOID pvQueue = SetupInitDefaultQueueCallback(NULL);

        BOOL fSuccess = SetupInstallFromInfSection(NULL,
                                                    hINF,
                                                    pszSection,
                                                    SPINST_ALL,
                                                    HKEY_LOCAL_MACHINE,
                                                    NULL,
                                                    SP_COPY_NEWER_OR_SAME | SP_COPY_NOSKIP,
                                                    vboxDrvInstExecuteInfFileCallback,
                                                    pvQueue,
                                                    NULL,
                                                    NULL
                                                    );
        if (fSuccess)
        {
            _tprintf (_T( "File installation stage successful\n"));

            fSuccess = SetupInstallServicesFromInfSection(hINF,
                                                          L"DefaultInstall.Services",
                                                          0 /* Flags */);
            if (fSuccess)
            {
                _tprintf (_T( "Service installation stage successful. Installation completed\n"));
            }
            else
            {
                DWORD dwErr = GetLastError();
                switch (dwErr)
                {
                    case ERROR_SUCCESS_REBOOT_REQUIRED:
                        _tprintf (_T( "A reboot is required to complete the installation\n"));
                        break;

                    case ERROR_SECTION_NOT_FOUND:
                        break;

                    default:
                        _tprintf (_T( "Error %ld while installing service\n"), dwErr);
                        break;
                }
            }
        }
        else
            _tprintf (_T( "Error %ld while installing files\n"), GetLastError());

        if (pvQueue)
            SetupTermDefaultQueueCallback(pvQueue);

        SetupCloseInfFile(hINF);
    }
    else
        _tprintf (_T( "Unable to open %ws: %ld (error line %u)\n"),
                  pszInf, GetLastError(), uErrorLine);

    return EXIT_OK;
}