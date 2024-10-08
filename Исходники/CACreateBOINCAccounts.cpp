/////////////////////////////////////////////////////////////////////
// 
// Function:    
//
// Description: 
//
/////////////////////////////////////////////////////////////////////
UINT CACreateBOINCAccounts::OnExecution()
{
    tstring          strBOINCMasterAccountUsername;
    tstring          strBOINCMasterAccountPassword;
    tstring          strBOINCProjectAccountUsername;
    tstring          strBOINCProjectAccountPassword;
    tstring          strComputerName;
    tstring          strProductType;
    tstring          strDataDirectory;
    tstring          strEnableProtectedApplicationExecution;
    PSID             pSid;
    NET_API_STATUS   nasReturnValue;
    BOOL             bCreateBOINCMasterAccount = FALSE;
    BOOL             bCreateBOINCProjectAccount = FALSE;
    BOOL             bBOINCMasterAccountCreated = FALSE;
    BOOL             bBOINCProjectAccountCreated = FALSE;
    BOOL             bBOINCMasterAccountModified = FALSE;
    BOOL             bBOINCProjectAccountModified = FALSE;
    UINT             uiReturnValue = -1;

    uiReturnValue = GetProperty( _T("BOINC_MASTER_USERNAME"), strBOINCMasterAccountUsername );
    if ( uiReturnValue ) return uiReturnValue;

    uiReturnValue = GetProperty( _T("BOINC_MASTER_PASSWORD"), strBOINCMasterAccountPassword );
    if ( uiReturnValue ) return uiReturnValue;

    uiReturnValue = GetProperty( _T("BOINC_PROJECT_USERNAME"), strBOINCProjectAccountUsername );
    if ( uiReturnValue ) return uiReturnValue;

    uiReturnValue = GetProperty( _T("BOINC_PROJECT_PASSWORD"), strBOINCProjectAccountPassword );
    if ( uiReturnValue ) return uiReturnValue;

    uiReturnValue = GetProperty( _T("ComputerName"), strComputerName );
    if ( uiReturnValue ) return uiReturnValue;

    uiReturnValue = GetProperty( _T("MsiNTProductType"), strProductType );
    if ( uiReturnValue ) return uiReturnValue;

    uiReturnValue = GetProperty( _T("ENABLEPROTECTEDAPPLICATIONEXECUTION3"), strEnableProtectedApplicationExecution );
    if ( uiReturnValue ) return uiReturnValue;



    // Only create a new account or change the password on an existing account
    //   if the user hasn't explicitly defined an account
    if (strBOINCMasterAccountUsername.empty() && strBOINCMasterAccountPassword.empty()) bCreateBOINCMasterAccount = true;
    if (strBOINCMasterAccountUsername == _T("boinc_master")) bCreateBOINCMasterAccount = true;
    if (strProductType == tstring(_T("2")) && (strBOINCMasterAccountUsername == (tstring(_T("boinc_master_")) + strComputerName))) bCreateBOINCMasterAccount = true;

    if (bCreateBOINCMasterAccount) {

        LogMessage(
            INSTALLMESSAGE_INFO,
            NULL, 
            NULL,
            NULL,
            NULL,
            _T("Using automatic account creation and management of 'boinc_master' account")
        );

        // Determine what the real values of the usernames should be based off
        //   of the inputs
        //
        if (strBOINCMasterAccountUsername.empty()) {
            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Generating 'boinc_master' account name")
            );
            if (strProductType == tstring(_T("2"))) {                    // Domain Controller
                strBOINCMasterAccountUsername = _T("boinc_master_") + strComputerName;
            } else {
                strBOINCMasterAccountUsername = _T("boinc_master");
            }
        }


        // Generate random passwords if needed
        //
        if (strBOINCMasterAccountPassword.empty()) {
            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Generating 'boinc_master' password")
            );
            GenerateRandomPassword(strBOINCMasterAccountPassword, 12);
            strBOINCMasterAccountPassword = _T("!") + strBOINCMasterAccountPassword;
        }


        // Create the 'boinc_master' account if needed, otherwise just update the password.
        //
        if(GetAccountSid(NULL, strBOINCMasterAccountUsername.c_str(), &pSid)) {   // Check if user exists

            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Resetting 'boinc_master' password")
            );

            // Account already exists, just change the password
            //
            USER_INFO_1003 ui;
            DWORD          dwParameterError;

            ui.usri1003_password = (LPWSTR)strBOINCMasterAccountPassword.c_str();

            nasReturnValue = NetUserSetInfo(
                NULL,
                strBOINCMasterAccountUsername.c_str(),
                1003,
                (LPBYTE)&ui,
                &dwParameterError
            );

            if (NERR_Success != nasReturnValue) {
                LogMessage(
                    INSTALLMESSAGE_ERROR,
                    NULL, 
                    NULL,
                    NULL,
                    nasReturnValue,
                    _T("Failed to reset password on the 'boinc_master' account.")
                );
                return ERROR_INSTALL_FAILURE;
            }
        } else {

            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Creating 'boinc_master' account")
            );

            // Account does not exist, create it
            //
            USER_INFO_1 ui;
            DWORD       dwParameterError;

            ui.usri1_name = (LPWSTR)strBOINCMasterAccountUsername.c_str();
            ui.usri1_password = (LPWSTR)strBOINCMasterAccountPassword.c_str();
            ui.usri1_comment = _T("Account used to execute BOINC as a system service");
            ui.usri1_priv = USER_PRIV_USER;
            ui.usri1_home_dir = NULL;
            ui.usri1_comment = NULL;
            ui.usri1_flags = UF_SCRIPT | UF_PASSWD_CANT_CHANGE | UF_DONT_EXPIRE_PASSWD;
            ui.usri1_script_path = NULL;

            nasReturnValue = NetUserAdd(
                NULL,
                1,
                (LPBYTE)&ui,
                &dwParameterError
            );

            if (NERR_Success != nasReturnValue) {
                LogMessage(
                    INSTALLMESSAGE_INFO,
                    NULL, 
                    NULL,
                    NULL,
                    nasReturnValue,
                    _T("NetUserAdd retval")
                );
                LogMessage(
                    INSTALLMESSAGE_INFO,
                    NULL, 
                    NULL,
                    NULL,
                    dwParameterError,
                    _T("NetUserAdd dwParameterError")
                );
                LogMessage(
                    INSTALLMESSAGE_ERROR,
                    NULL, 
                    NULL,
                    NULL,
                    nasReturnValue,
                    _T("Failed to create the 'boinc_master' account.")
                );
                return ERROR_INSTALL_FAILURE;
            }

            bBOINCMasterAccountCreated = TRUE;
        }
        if(pSid != NULL) {
            HeapFree(GetProcessHeap(), 0, pSid);
            pSid = NULL;
        }

        bBOINCMasterAccountModified = TRUE;
    }

    // Only create a new account or change the password on an existing account
    //   if the user hasn't explicitly defined an account
    if (strBOINCProjectAccountUsername.empty() && strBOINCProjectAccountPassword.empty()) bCreateBOINCProjectAccount = true;
    if (strBOINCProjectAccountUsername == _T("boinc_project")) bCreateBOINCProjectAccount = true;
    if (strProductType == tstring(_T("2")) && (strBOINCProjectAccountUsername == (tstring(_T("boinc_project_")) + strComputerName))) bCreateBOINCProjectAccount = true;

    if (bCreateBOINCProjectAccount) {

        LogMessage(
            INSTALLMESSAGE_INFO,
            NULL, 
            NULL,
            NULL,
            NULL,
            _T("Using automatic account creation and management of 'boinc_project' account")
        );

        // Determine what the real values of the usernames should be based off
        //   of the inputs
        //
        if (strBOINCProjectAccountUsername.empty()) {
            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Generating 'boinc_project' account name")
            );
            if (strProductType == tstring(_T("2"))) {                    // Domain Controller
                strBOINCProjectAccountUsername = _T("boinc_project_") + strComputerName;
            } else {
                strBOINCProjectAccountUsername = _T("boinc_project");
            }
        }


        // Generate random passwords if needed
        //
        if (strBOINCProjectAccountPassword.empty()) {
            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Generating 'boinc_project' password")
            );
            GenerateRandomPassword(strBOINCProjectAccountPassword, 12);
            strBOINCProjectAccountPassword = _T("!") + strBOINCProjectAccountPassword;
        }


        // Create the 'boinc_project' account if needed, otherwise just update the password.
        //
        if(GetAccountSid(NULL, strBOINCProjectAccountUsername.c_str(), &pSid)) {   // Check if user exists

            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Resetting 'boinc_project' password")
            );

            // Account already exists, just change the password
            //
            USER_INFO_1003 ui;
            DWORD          dwParameterError;

            ui.usri1003_password = (LPWSTR)strBOINCProjectAccountPassword.c_str();

            nasReturnValue = NetUserSetInfo(
                NULL,
                strBOINCProjectAccountUsername.c_str(),
                1003,
                (LPBYTE)&ui,
                &dwParameterError
            );

            if (NERR_Success != nasReturnValue) {
                LogMessage(
                    INSTALLMESSAGE_ERROR,
                    NULL, 
                    NULL,
                    NULL,
                    nasReturnValue,
                    _T("Failed to reset password on the 'boinc_project' account.")
                );
                return ERROR_INSTALL_FAILURE;
            }
        } else {

            LogMessage(
                INSTALLMESSAGE_INFO,
                NULL, 
                NULL,
                NULL,
                NULL,
                _T("Creating 'boinc_project' account")
            );

            // Account does not exist, create it
            //
            USER_INFO_1 ui;
            DWORD       dwParameterError;

            ui.usri1_name = (LPWSTR)strBOINCProjectAccountUsername.c_str();
            ui.usri1_password = (LPWSTR)strBOINCProjectAccountPassword.c_str();
            ui.usri1_comment = _T("Account used to execute BOINC applications");
            ui.usri1_priv = USER_PRIV_USER;
            ui.usri1_home_dir = NULL;
            ui.usri1_comment = NULL;
            ui.usri1_flags = UF_SCRIPT | UF_PASSWD_CANT_CHANGE | UF_DONT_EXPIRE_PASSWD;
            ui.usri1_script_path = NULL;

            nasReturnValue = NetUserAdd(
                NULL,
                1,
                (LPBYTE)&ui,
                &dwParameterError
            );

            if (NERR_Success != nasReturnValue) {
                LogMessage(
                    INSTALLMESSAGE_INFO,
                    NULL, 
                    NULL,
                    NULL,
                    nasReturnValue,
                    _T("NetUserAdd retval")
                );
                LogMessage(
                    INSTALLMESSAGE_INFO,
                    NULL, 
                    NULL,
                    NULL,
                    dwParameterError,
                    _T("NetUserAdd dwParameterError")
                );
                LogMessage(
                    INSTALLMESSAGE_ERROR,
                    NULL, 
                    NULL,
                    NULL,
                    nasReturnValue,
                    _T("Failed to create the 'boinc_project' account.")
                );
                return ERROR_INSTALL_FAILURE;
            }

            bBOINCProjectAccountCreated = TRUE;
        }
        if(pSid != NULL) {
            HeapFree(GetProcessHeap(), 0, pSid);
            pSid = NULL;
        }

        bBOINCProjectAccountModified = TRUE;
    }


    SetProperty( _T("BOINC_MASTER_USERNAME"), strBOINCMasterAccountUsername );
    if (bBOINCMasterAccountModified) {
        SetProperty( _T("BOINC_MASTER_ISUSERNAME"), tstring(_T(".\\") + strBOINCMasterAccountUsername) );
    } else {
        SetProperty( _T("BOINC_MASTER_ISUSERNAME"), strBOINCMasterAccountUsername );
    }
    SetProperty( _T("BOINC_MASTER_PASSWORD"), strBOINCMasterAccountPassword, false );

    SetProperty( _T("BOINC_PROJECT_USERNAME"), strBOINCProjectAccountUsername );
    if (bBOINCProjectAccountModified) {
        SetProperty( _T("BOINC_PROJECT_ISUSERNAME"), tstring(_T(".\\") + strBOINCProjectAccountUsername) );
    } else {
        SetProperty( _T("BOINC_PROJECT_ISUSERNAME"), strBOINCProjectAccountUsername );
    }
    SetProperty( _T("BOINC_PROJECT_PASSWORD"), strBOINCProjectAccountPassword, false );

    if (bBOINCMasterAccountCreated || bBOINCProjectAccountCreated) {
        RebootWhenFinished();
    }

    return ERROR_SUCCESS;
}