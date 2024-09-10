// From MWidgetCallbacks
// ----------------------------------------------------------------------------
// CWidgetClient::launchApplicationL
//
//
//
// ----------------------------------------------------------------------------
//
void CWidgetClient::launchApplicationL(const TUid& aUid, const TDesC& aParam)
{
    RApaLsSession apaLsSession;
    TApaTaskList taskList(CEikonEnv::Static()->WsSession());
    TApaTask task = taskList.FindApp(aUid);

    if ( task.Exists() ) {

        task.BringToForeground();
        if ( aParam.Length() > 0 ) {
            HBufC8* param8 = HBufC8::NewLC( aParam.Length() );
            param8->Des().Append( aParam );
            task.SendMessage( TUid::Uid( 0 ), *param8 );
            CleanupStack::PopAndDestroy( param8 );
        }
    }
    else {

        TInt eConnect = KErrNone;
        if ( !apaLsSession.Handle() ) {
            eConnect = apaLsSession.Connect();
        }

        if ( eConnect == KErrNone ) {
            TThreadId threadId;
            apaLsSession.StartDocument( aParam, aUid, threadId );
            apaLsSession.Close();
        }
    }

}