// ============================================================================
// CWidgetEntry::Active()
// Is widget running? 0 if not, non zero if running.
//
// @since 3.1
// ============================================================================
//
TInt CWidgetEntry::ActiveL()
{
    if ( iActive )
    {
        // check that WidgetUI didn't crash, this assumes all widgets
        // in the registry are running under WidgetUI
        RWsSession wsSession;
        User::LeaveIfError( wsSession.Connect() );
        CleanupClosePushL( wsSession );
        TApaTaskList taskList( wsSession );
        TApaTask task = taskList.FindApp( KUidWidgetUi );
        if ( EFalse == task.Exists() )
        {
            // widget UI crashed, reset active
            iActive = 0;
        }
        CleanupStack::PopAndDestroy( &wsSession );
    }
    return iActive;
}