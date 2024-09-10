void CVersitTest::StreamInL()
//Convert the iVersit into stream format, save it as "TTVersitIn"
//and internalize it as a CVersitParser
	{
	RFs fsSession; 
	User::LeaveIfError(fsSession.Connect());
	CFileStore* store = CDirectFileStore::ReplaceLC(fsSession,_L("c:\\TTVersit2"),EFileWrite);
	store->SetTypeL(KDirectFileStoreLayoutUid);
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(*store);
	TInt length=iVersit.Length();
	for (TInt ii=0; ii<length; ii++)
		outstream.WriteInt8L(iVersit[ii]);
	outstream.CommitL();
	CleanupStack::PopAndDestroy();
	store->SetRootL(id);
	store->CommitL();
	CleanupStack::PopAndDestroy();
	store = CDirectFileStore::OpenLC(fsSession,_L("c:\\TTVersit2"),EFileRead); //retrieve stream
	RStoreReadStream instream;
	instream.OpenLC(*store,store->Root());
	iParser->InternalizeL(instream);
	CleanupStack::PopAndDestroy(2); //store + stream
	}