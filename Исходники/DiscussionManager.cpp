void CDiscussion::SetDiscussionIdL(const TDesC& aDiscussionId) {
	// Rename existing cache file
	RFs aSession = CCoeEnv::Static()->FsSession();
	TFileName aOldFilePath = GetFileName(aSession);
	
	if(iDiscussionId) {
		delete iDiscussionId;
	}
	
	iDiscussionId = aDiscussionId.AllocL();
	
	TFileName aNewFilePath = GetFileName(aSession);
	
	if(aNewFilePath.Compare(aOldFilePath) != 0) {
		aSession.Rename(aOldFilePath, aNewFilePath);
	}
}