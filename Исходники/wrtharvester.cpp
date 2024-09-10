// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
//
TBool CWrtHarvester::CheckTaskExistsL()
    {
    TUid widgetAppUid( TUid::Uid( KWidgetAppUid ) );
    RWsSession wsSession;    
        
    // Create Window server session
    User::LeaveIfError( wsSession.Connect() );
    
    TApaTaskList taskList( wsSession );
    TApaTask task = taskList.FindApp( widgetAppUid );
    return task.Exists()?ETrue:EFalse;
    }