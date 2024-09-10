UInt32	CAPThread::GetScheduledPriority()
{
#if TARGET_OS_MAC
    return CAPThread::getScheduledPriority( mPThread, CAPTHREAD_SCHEDULED_PRIORITY );
#elif TARGET_OS_WIN32
	UInt32 theAnswer = 0;
	if(mThreadHandle != NULL)
	{
		theAnswer = GetThreadPriority(mThreadHandle);
	}
	return theAnswer;
#endif
}