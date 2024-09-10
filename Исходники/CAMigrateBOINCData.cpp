/////////////////////////////////////////////////////////////////////
// 
// Function:    
//
// Description: 
//
/////////////////////////////////////////////////////////////////////
UINT CAMigrateBOINCData::OnInstall()
{
    tstring     strCustomActionData;
    tstring     strMigratingDirectory;
    tstring     strInstallDirectory;
    tstring     strDataDirectory;
    tstring     strMessage;
    ULONGLONG   ullFileSize = 0;
    ULONGLONG   ullDirectorySize = 0;
    ULONGLONG   ullBytesTransfered = 0;
    UINT        uiReturnValue = -1;

    LogMessage(
        INSTALLMESSAGE_INFO,
        NULL, 
        NULL,
        NULL,
        NULL,
        _T("CAMigrateBOINCData::OnInstall -- Function Begin")
    );

    // CustomActionData is a pipe seperated string which contains whether
    //   this interation of the installer is migrating the BOINC data, the
    //   installer directory, and the data directory.
    //
    // Ex: <MigrationStatus>|<InstallDirectory>|<DataDrectory>
    //
    uiReturnValue = GetProperty( _T("CustomActionData"), strCustomActionData );
    if ( uiReturnValue ) return uiReturnValue;

    strMigratingDirectory = 
        strCustomActionData.substr(0, strCustomActionData.find(_T("|")));

    strMessage = _T("CAMigrateBOINCData::OnInstall -- strMigratingDirectory: '");
    strMessage += strMigratingDirectory;
    strMessage += _T("'");

    LogMessage(
        INSTALLMESSAGE_INFO,
        NULL, 
        NULL,
        NULL,
        NULL,
        strMessage.c_str()
    );

    strInstallDirectory = 
        strCustomActionData.substr(
            strCustomActionData.find(_T("|")) + 1,
            strCustomActionData.find(_T("|"), (strCustomActionData.find(_T("|")) + 1)) - 5
        );

    strMessage = _T("CAMigrateBOINCData::OnInstall -- strInstallDirectory: '");
    strMessage += strInstallDirectory;
    strMessage += _T("'");

    LogMessage(
        INSTALLMESSAGE_INFO,
        NULL, 
        NULL,
        NULL,
        NULL,
        strMessage.c_str()
    );

    strDataDirectory = 
        strCustomActionData.substr(strCustomActionData.rfind(_T("|")) + 1, strCustomActionData.length() - strCustomActionData.rfind(_T("|")) - 1);

    strMessage = _T("CAMigrateBOINCData::OnInstall -- strDataDirectory: '");
    strMessage += strDataDirectory;
    strMessage += _T("'");

    LogMessage(
        INSTALLMESSAGE_INFO,
        NULL, 
        NULL,
        NULL,
        NULL,
        strMessage.c_str()
    );


    // Are we migrating data?
    if ( _T("TRUE") == strMigratingDirectory )
    {
        // Determine how we should setup the progress bar.
        GetFileDirectorySizes( strInstallDirectory, ullFileSize, ullDirectorySize );

        // Reset the progress bar
        MsiRecordSetInteger(m_phProgressRec, 1, 0);
        MsiRecordSetInteger(m_phProgressRec, 2, (INT)((ullDirectorySize/1024)/1024));
        MsiRecordSetInteger(m_phProgressRec, 3, 0);
        MsiProcessMessage(m_hMSIHandle, INSTALLMESSAGE_PROGRESS, m_phProgressRec);

        // Tell the installer to use explicit progress messages.
        MsiRecordSetInteger(m_phProgressRec, 1, 1);
        MsiRecordSetInteger(m_phProgressRec, 2, 1);
        MsiRecordSetInteger(m_phProgressRec, 3, 0);
        MsiProcessMessage(m_hMSIHandle, INSTALLMESSAGE_PROGRESS, m_phProgressRec);

        // Migrate the data files
        if (!MoveFiles( strInstallDirectory, strDataDirectory, ullBytesTransfered ))
        {
            LogMessage(
                INSTALLMESSAGE_FATALEXIT,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Failed to migrate BOINC data files to the data directory.")
                );
            return ERROR_INSTALL_FAILURE;
        }
    }

    LogMessage(
        INSTALLMESSAGE_INFO,
        NULL, 
        NULL,
        NULL,
        NULL,
        _T("CAMigrateBOINCData::OnInstall -- Function End")
    );

    return ERROR_SUCCESS;
}