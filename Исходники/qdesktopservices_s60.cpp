static void handleOtherSchemesL(const TDesC& aUrl)
{
    // Other schemes are at the moment passed to WEB browser
    HBufC* buf16 = HBufC::NewLC(aUrl.Length() + KBrowserPrefix.iTypeLength);
    buf16->Des().Copy(KBrowserPrefix); // Prefix used to launch correct browser view
    buf16->Des().Append(aUrl);

    TApaTaskList taskList(CEikonEnv::Static()->WsSession());
    TApaTask task = taskList.FindApp(KUidBrowser);
    if (task.Exists()){
        // Switch to existing browser instance
        task.BringToForeground();
        HBufC8* param8 = HBufC8::NewLC(buf16->Length());
        param8->Des().Append(buf16->Des());
        task.SendMessage(TUid::Uid( 0 ), *param8); // Uid is not used
        CleanupStack::PopAndDestroy(param8);
    } else {
        // Start a new browser instance
        RApaLsSession appArcSession;
        User::LeaveIfError(appArcSession.Connect());
        CleanupClosePushL<RApaLsSession>(appArcSession);
        TThreadId id;
        appArcSession.StartDocument(*buf16, KUidBrowser, id);
        CleanupStack::PopAndDestroy(); // appArcSession
    }

    CleanupStack::PopAndDestroy(buf16);
}