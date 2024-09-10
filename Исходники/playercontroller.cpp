void PlayerController::GoToNowPlaying()
{
    if (playerLaunched)
    {
 //Launch player
        RWsSession wsSession;
        User::LeaveIfError( wsSession.Connect() );
        TApaTaskList list(wsSession);
        TApaTask task = list.FindApp(KMusicPlayerAppUid);
        CMPXParameter* param = new ( ELeave ) CMPXParameter();
        CleanupStack::PushL( param );
        param->iType.iUid = KMPXPluginTypePlaybackUid;
        param->iCmdForward = EMPXCmdFwdNone;
        CBufBase* buffer =
                CBufFlat::NewL(3 );
        CleanupStack::PushL( buffer );
        RBufWriteStream writeStream( *buffer );
        CleanupClosePushL( writeStream );
        param->ExternalizeL( writeStream );
        writeStream.CommitL();
        buffer->Compress();
        CleanupStack::PopAndDestroy( &writeStream );
        if ( task.Exists() )
            {
            wsSession.SendMessageToWindowGroup( task.WgId(), KAppUidMusicPlayerX,
                        buffer->Ptr( 0 ) );


            }
        else
            {
            RApaLsSession ls;
            CleanupClosePushL( ls );
            User::LeaveIfError( ls.Connect() );
            TApaAppInfo appInfo;
            User::LeaveIfError( ls.GetAppInfo( appInfo, KAppUidMusicPlayerX ) );
            CApaCommandLine* apaCommandLine = CApaCommandLine::NewLC();
            apaCommandLine->SetExecutableNameL( appInfo.iFullName );
            apaCommandLine->SetTailEndL( buffer->Ptr( 0 ) );
            User::LeaveIfError( ls.StartApp( *apaCommandLine ) );
            CleanupStack::PopAndDestroy(); // apaCommandLine
            CleanupStack::PopAndDestroy(); // ls
            }
        CleanupStack::PopAndDestroy( buffer );
        CleanupStack::PopAndDestroy( param );
        wsSession.Close();
    }
    else if (radioLaunched)
    {
        RApaLsSession ls;
        CleanupClosePushL( ls );
        User::LeaveIfError( ls.Connect() );
        TApaAppInfo appInfo;
        User::LeaveIfError( ls.GetAppInfo( appInfo, KRadioUid ) );
        CApaCommandLine* apaCommandLine = CApaCommandLine::NewLC();
        apaCommandLine->SetExecutableNameL( appInfo.iFullName );
        User::LeaveIfError( ls.StartApp( *apaCommandLine ) );
        CleanupStack::PopAndDestroy(); // apaCommandLine
        CleanupStack::PopAndDestroy(); // ls
    }
}