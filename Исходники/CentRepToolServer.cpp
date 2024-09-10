void CCentRepToolSession::PerformRFSL()
{
	RDEBUG("CentRepToolSession: Restore factory setting operation started");
	//RFS tasks in centrep tool
	// 1. restory setting enforcements
	// 2. remove backup and temp files from private directory
	
	
	//clean private directory
	RFs rfs;
	TInt err = rfs.Connect();
	if( err != KErrNone )
		{
		RDEBUG_2("**** CCentRepToolSession::PerformRFSL() - failed to connect to RFs: %d", err );
		return;
		}
		
	CleanupClosePushL( rfs);
	
	TBuf<100> privatePath;
	err = rfs.PrivatePath( privatePath);
	
	if ( err == KErrNone)
	{
		//remove files from private directory, also backups
		CFileMan* file = CFileMan::NewL( rfs);
		
		privatePath.Append(_L("*.*"));
		err = file->Delete( privatePath, CFileMan::ERecurse);
		delete file;
	}
	
	CleanupStack::PopAndDestroy( &rfs);	
	
	RDEBUG("CentRepToolSession: Restore factory setting operation finished");
}