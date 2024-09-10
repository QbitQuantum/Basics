void gsiEnterCriticalSection(GSICriticalSection *theCrit) 
{ 
	// If we're not already in it, wait for it
	if (GetThreadId() != theCrit->mOwnerThread)
	{
		gsiWaitForSemaphore(theCrit->mSemaphore, 0);
		theCrit->mOwnerThread = GetThreadId();
	}

	// Increment entry count
	theCrit->mEntryCount++;
}