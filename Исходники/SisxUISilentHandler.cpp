// -----------------------------------------------------------------------------
// CSisxUISilentHandler::BringToForeground
// Swithces application to foreground or background. Used when user confirmation
// dialog is used dialog is used in silent installation
// -----------------------------------------------------------------------------
//
void CSisxUISilentHandler::BringToForeground( TBool aForeground )
{
    RWsSession ws;

    if ( ws.Connect() == KErrNone )
    {
        CleanupClosePushL(ws);
        TApaTaskList tasklist(ws);

        if ( aForeground )
        {
            TApaTask task = tasklist.FindApp( TUid::Uid(KSWInstSvrUid) );
            if ( task.Exists() )
            {
                task.BringToForeground();
            }
        }
        else
        {
            TApaTask task = tasklist.FindApp( TUid::Uid(KSWInstSvrUid) );
            if ( task.Exists() )
            {
                task.SendToBackground();
            }
        }

        CleanupStack::PopAndDestroy(); //ws
    }
}