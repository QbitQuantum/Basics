// If the RAS autodial service is running, use it. Otherwise, dial
// the default RAS connection. There are two possible RAS dialogs:
// one that dials a single entry, and one that lets the user choose which
// to dial. If there is only one connection entry in the phone book, or
// there are multiple entries but one is defined as the default, we'll use
// the single entry dial dialog. If there are multiple connection entries,
// and none is specified as default, we'll bring up the diallog which lets
// the user select the connection entry to use.
//
// Return values:
//  NS_OK: dialing was successful and caller should retry
//  all other values indicate that the caller should not retry
nsresult nsAutodial::DialDefault(const char16_t* hostName)
{
    mDontRetryUntil = 0;

    if (mAutodialBehavior == AUTODIAL_NEVER)
    {
        return NS_ERROR_FAILURE;    // don't retry the network error
    }

    // If already a RAS connection, bail.
    if (IsRASConnected())
    {
        LOGD(("Autodial: Not dialing: active connection."));
        return NS_ERROR_FAILURE;    // don't retry
    }

    // If no dialup connections configured, bail.
    if (mNumRASConnectionEntries <= 0)
    {
        LOGD(("Autodial: Not dialing: no entries."));
        return NS_ERROR_FAILURE;    // don't retry
    }


    // If autodial service is running, let it dial. In order for it to dial more
    // reliably, we have to add the target address to the autodial database.
    // This is the only way the autodial service dial if there is a network
    // adapter installed. But even then it might not dial. We have to assume that
    // it will though, or we could end up with two attempts to dial on the same
    // network error if the user cancels the first one: one from the service and
    // one from us.
    // See http://msdn.microsoft.com/library/default.asp?url=/library/en-us/rras/ras4over_3dwl.asp
    if (mAutodialBehavior == AUTODIAL_USE_SERVICE)
    {
        AddAddressToAutodialDirectory(hostName);
        return NS_ERROR_FAILURE;    // don't retry
    }

    // Do the dialing ourselves.
    else
    {
        // If a default dial entry is configured, use it.
        if (mDefaultEntryName[0] != '\0') 
        {
            LOGD(("Autodial: Dialing default: %s.",mDefaultEntryName));

            RASDIALDLG rasDialDlg;
            memset(&rasDialDlg, 0, sizeof(rasDialDlg));
            rasDialDlg.dwSize = sizeof(rasDialDlg);

            BOOL dialed = 
             RasDialDlgW(nullptr, mDefaultEntryName, nullptr, &rasDialDlg);

            if (!dialed)
            {
                if (rasDialDlg.dwError != 0)
                {
                    LOGE(("Autodial ::RasDialDlg failed: Error: %d.", 
                     rasDialDlg.dwError));
                }
                else
                {
                    mDontRetryUntil = PR_IntervalNow() + PR_SecondsToInterval(NO_RETRY_PERIOD_SEC);
                    LOGD(("Autodial: User cancelled dial."));
                }
                return NS_ERROR_FAILURE;    // don't retry
            }

            LOGD(("Autodial: RAS dialup connection successful."));
        }

        // If no default connection specified, open the dialup dialog that lets
        // the user specifiy which connection to dial.
        else
        {
            LOGD(("Autodial: Prompting for phonebook entry."));

            RASPBDLG rasPBDlg;
            memset(&rasPBDlg, 0, sizeof(rasPBDlg));
            rasPBDlg.dwSize = sizeof(rasPBDlg);
 
            BOOL dialed = RasPhonebookDlgW(nullptr, nullptr, &rasPBDlg);

            if (!dialed)
            {
                if (rasPBDlg.dwError != 0)
                {
                    LOGE(("Autodial: ::RasPhonebookDlg failed: Error = %d.", 
                     rasPBDlg.dwError));
                }
                else
                {
                    mDontRetryUntil = PR_IntervalNow() + PR_SecondsToInterval(NO_RETRY_PERIOD_SEC);
                    LOGD(("Autodial: User cancelled dial."));
                }

                return NS_ERROR_FAILURE;    // don't retry
            }

            LOGD(("Autodial: RAS dialup connection successful."));
        }
    }

    // Retry because we just established a dialup connection.
    return NS_OK;
}