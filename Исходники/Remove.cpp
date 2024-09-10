//////////////////////////////////////////////////////////////////////////////
// RemoveUserAccount
//
//     Attempts to remove a user account on the local machine according
//       to the "instructions" provided in the CustomActionData property
//
//     As a deferred custom action, you do not have access to the database.
//       The only source of information comes from a property that an immediate
//       custom action can set to provide the information you need.  This
//       property is written into the script
//
                                                           UINT __stdcall RemoveUserAccount(MSIHANDLE hInstall)
{
    // determine mode in which we are called
    BOOL bRollback = MsiGetMode(hInstall, MSIRUNMODE_ROLLBACK); // true for rollback, else regular deferred version (for uninstall)

    BOOL fSuccess = FALSE;

    // id's for error and warning messages
    const int iRemoveError = 25003;
    const int iRemoveWarning = 25004;

    // Grab the CustomActionData property
    DWORD cchCAData = 0;

    if (ERROR_MORE_DATA == MsiGetPropertyW(hInstall, IPROPNAME_CUSTOMACTIONDATA, L"", &cchCAData))
    {
        WCHAR* wszCAData = new WCHAR[++cchCAData]; // add 1 for null-terminator which is not included in size on return
        if (wszCAData)
        {
            if (ERROR_SUCCESS == MsiGetPropertyW(hInstall, IPROPNAME_CUSTOMACTIONDATA, wszCAData, &cchCAData))
            {
                // send ActionData message (template in ActionText table)
                // send ActionData message (template in ActionText table)
                PMSIHANDLE hRec = MsiCreateRecord(1);
                if (!hRec
                        || ERROR_SUCCESS != MsiRecordSetStringW(hRec, 1, wszCAData))
                {
                    delete [] wszCAData;
                    return ERROR_INSTALL_FAILURE;
                }

                int iRet = MsiProcessMessage(hInstall, INSTALLMESSAGE_ACTIONDATA, hRec);
                if (IDCANCEL == iRet || IDABORT == iRet)
                {
                    delete [] wszCAData;
                    return ERROR_INSTALL_USEREXIT;
                }

                //
                // Call the NetUserDel function,
                //
                NET_API_STATUS nStatus = NetUserDel(NULL /*local machine*/, wszCAData /*user name*/);

                if (NERR_Success != nStatus)
                {
                    PMSIHANDLE hRecErr = MsiCreateRecord(3);
                    if ( !hRecErr
                            || ERROR_SUCCESS != MsiRecordSetStringW(hRecErr, 2, wszCAData))
                    {
                        delete [] wszCAData;
                        return ERROR_INSTALL_FAILURE;
                    }

                    // In rollback mode, NERR_UserNotFound means cancel button depressed in middle of deferred CA trying to create this account
                    if (bRollback && NERR_UserNotFound == nStatus)
                    {
                        fSuccess = TRUE;
                    }
                    else if (NERR_UserNotFound == nStatus)
                    {
                        // treat this as a warning, but success since we are attempting to delete and it is not present
                        if (ERROR_SUCCESS != MsiRecordSetInteger(hRecErr, 1, iRemoveWarning))
                        {
                            delete [] wszCAData;
                            return ERROR_INSTALL_FAILURE;
                        }

                        // just pop up an OK button
                        // OPTIONALLY, could specify multiple buttons and cancel
                        // install based on user selection by handling the return value
                        // from MsiProcessMessage, but here we are ignoring the MsiProcessMessage return
                        MsiProcessMessage(hInstall, INSTALLMESSAGE(INSTALLMESSAGE_WARNING|MB_ICONWARNING|MB_OK), hRecErr);
                        fSuccess = TRUE;
                    }
                    else
                    {
                        if (ERROR_SUCCESS == MsiRecordSetInteger(hRecErr, 1, iRemoveError)
                                && ERROR_SUCCESS == MsiRecordSetInteger(hRecErr, 3, nStatus))
                        {
                            // returning failure anyway, so ignoring MsiProcessMessage return
                            MsiProcessMessage(hInstall, INSTALLMESSAGE_ERROR, hRecErr);
                        }
                    }
                }
                else // NERR_Success
                {
                    fSuccess = TRUE;
                }
            }

            delete [] wszCAData;
        }
    }

    return fSuccess ? ERROR_SUCCESS : ERROR_INSTALL_FAILURE;
}