const int FConnection::startConnection(const StringBuffer& aIAPName)
{
    LOG.info("Starting new connection...");
    LOG.debug("Looking for '%s' IAP name", aIAPName.c_str());

    iLastError = KErrNone;
    StringBuffer errMsg;
    TCommDbConnPref prefs;

    prefs.SetDirection(ECommDbConnectionDirectionUnknown);


    if (aIAPName == "Default") {
        //
        // Use the default IAP without prompting the user
        //
        prefs.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
        prefs.SetIapId(0);
    }
    else if (aIAPName.empty() || aIAPName == "Ask") {
        //
        // Prompt user for IAP selection
        //
    }
    else {
        //
        // Search for the desired IAP. If not found, will prompt the user.
        //
        TInt iapID = GetIAPIDFromName(aIAPName);
        if (iapID >= 0) {
            LOG.debug("SetDialogPreference");
            prefs.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
            prefs.SetIapId(iapID);
        }
        else {
            LOG.debug("IAP '%s' not found!", aIAPName.c_str());
        }
    }


/*
 * **** TODO: check if we need this! ****
 In S60 3rd Edition, enabling/disabling the inactivity timer will require
 the NetworkControl capability, which is only accessed via Symbian
 partner.
 */
//#if !defined(__SERIES60_3X__) || defined(__S60_3X_NET_CTRL__)
//    // Disable inactivity timer, otherwise inactive connection is closed
//    // within few seconds if there are no activity (e.g sockets)
//    iConnection.SetOpt(KCOLProvider, KConnDisableTimers, ETrue);
//#endif


    // Opens the connection
    openConnection();

    // Start connection
    iLastError = iConnection.Start(prefs);
    if (iLastError != KErrNone) {
        errMsg.sprintf("FConnection error: unable to start connection (code %d)", iLastError);
        LOG.debug("Goto retry");
        goto retry;
    }

    // Save the IAP ID & name of the active connection.
    // Query the CommDb database for the IAP ID in use.
    _LIT(KIAPSettingName, "IAP\\Id");
    iConnection.GetIntSetting(KIAPSettingName, iIAP);
    iIAPName = GetIAPNameFromID(iIAP);
    LOG.debug("Current active IAP ID = %d, name = '%s'", iIAP, iIAPName.c_str());
    //
    // TODO: should we persist the iIAPName in the config, here?
    //

    iRetryConnection = 0;
    return 0;


retry:

    LOG.error("%s", errMsg.c_str());

    if (iIAPName.empty() || iIAPName == "Ask") {
        LOG.debug("Connection error and no IAP stored: don't retry");
        return iLastError;
    }

    LOG.debug("About to retry...");
    if (iRetryConnection < MAX_RETRY_CONNECTION) {
        iRetryConnection ++;
        LOG.info("Retry connection (%d time)...", iRetryConnection);
        startConnection(iIAPName);
    }
    else {
        LOG.error("FConnection: %d connection failed", iRetryConnection);
    }
    return iLastError;
}