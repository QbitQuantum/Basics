void IntegrityRestoreFileL(const TDesC& aPath, CIntegrityTreeLeaf* aLeaf, RFs& aFs, 
								RLoader& /*aLoader*/, CFileMan& /*aFileMan*/)
	{
	RBuf name;
	name.CreateL(aPath, KMaxFileName);
	CleanupClosePushL(name);
	name.Append(aLeaf->Name());

	// find the peer file, and check it's a backup.
	CIntegrityTreeLeaf* peer = aLeaf->Peer();
	if (peer->Type() != EBackupFile)
		{
		User::Leave(KErrCorrupt);
		}
	
	TParsePtrC parse(peer->Journal());
	RBuf backup;
	backup.CreateL(parse.DriveAndPath(), KMaxFileName);
	CleanupClosePushL(backup);
	backup.Append(parse.Name());
	backup.Append(KPathDelimiter);
	backup.Append(peer->Name());

	TInt err = aFs.MkDirAll(name);
	if(err != KErrNone && err != KErrAlreadyExists)
		{
		User::Leave(err);
		}
			
	err = aFs.Rename(backup, name);
	if (err != KErrNone)
		{
		VerifyDeletionErrorL(err);
		// we may have already moved it back during a previous recovery
		// attempt, check for its presence in the original location
		TEntry restoredEntry;
		User::LeaveIfError(aFs.Entry(name, restoredEntry));
		}
	else
		{
		// prune the backup directory tree if possible.
		RemoveDirectoryTreeL(aFs, backup);
		}
	CleanupStack::PopAndDestroy(2, &name);	// backup
	}