// ----------------------------------------------------------------------------------------
// CTerminalControlServer::StartProcessByUidL
// ----------------------------------------------------------------------------------------
void CTerminalControlServer::StartProcessByUidL ( const TUid& aUID )
{
    RDEBUG("CTerminalControlServer::StartProcessByUidL");

    RApaLsSession apaLs;
    User::LeaveIfError( apaLs.Connect() );
    CleanupClosePushL( apaLs );

    TThreadId threadId;
    TInt error = apaLs.StartDocument(_L(""), aUID, threadId);
    User::LeaveIfError( error );

    CleanupStack::PopAndDestroy( &apaLs );
}