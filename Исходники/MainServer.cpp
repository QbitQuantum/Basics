/* 
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
*/
TInt CExPolicy_Server::KillTasks(TUid& aUid)
{		
	TInt RetErr(KErrNone);
	
	RWsSession wsSession;
	RetErr= wsSession.Connect();
	if(RetErr == KErrNone)
	{
		TApaTaskList taskList( wsSession );
		TApaTask task = taskList.FindApp(aUid);

		if( task.Exists() ) 
		{
			task.KillTask();
		}		
	}

	wsSession.Close();
	
	return RetErr;
}