bool	CAGuard::WaitFor(UInt64 inNanos)
{
	bool theAnswer = false;

#if TARGET_OS_MAC
	ThrowIf(!pthread_equal(pthread_self(), mOwner), CAException(1), "CAGuard::WaitFor: A thread has to have locked a guard be for it can wait");

	#if	Log_TimedWaits
		DebugMessageN1("CAGuard::WaitFor: waiting %.0f", (Float64)inNanos);
	#endif

	struct timespec	theTimeSpec;
	static const UInt64	kNanosPerSecond = 1000000000ULL;
	if(inNanos >= kNanosPerSecond)
	{
		theTimeSpec.tv_sec = static_cast<UInt32>(inNanos / kNanosPerSecond);
		theTimeSpec.tv_nsec = static_cast<UInt32>(inNanos % kNanosPerSecond);
	}
	else
	{
		theTimeSpec.tv_sec = 0;
		theTimeSpec.tv_nsec = static_cast<UInt32>(inNanos);
	}
	
	#if	Log_TimedWaits || Log_Latency || Log_Average_Latency
		UInt64	theStartNanos = CAHostTimeBase::GetCurrentTimeInNanos();
	#endif

	mOwner = 0;

	#if	Log_WaitOwnership
		DebugPrintfRtn(DebugPrintfFileComma "%p %.4f: CAGuard::WaitFor: thread %p is waiting on %s, owner: %p\n", pthread_self(), ((Float64)(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000000.0), pthread_self(), mName, mOwner);
	#endif

	OSStatus theError = pthread_cond_timedwait_relative_np(&mCondVar, &mMutex, &theTimeSpec);
	ThrowIf((theError != 0) && (theError != ETIMEDOUT), CAException(theError), "CAGuard::WaitFor: Wait got an error");
	mOwner = pthread_self();
	
	#if	Log_TimedWaits || Log_Latency || Log_Average_Latency
		UInt64	theEndNanos = CAHostTimeBase::GetCurrentTimeInNanos();
	#endif
	
	#if	Log_TimedWaits
		DebugMessageN1("CAGuard::WaitFor: waited  %.0f", (Float64)(theEndNanos - theStartNanos));
	#endif
	
	#if	Log_Latency
		DebugMessageN1("CAGuard::WaitFor: latency  %.0f", (Float64)((theEndNanos - theStartNanos) - inNanos));
	#endif
	
	#if	Log_Average_Latency
		++mAverageLatencyCount;
		mAverageLatencyAccumulator += (theEndNanos - theStartNanos) - inNanos;
		if(mAverageLatencyCount >= 50)
		{
			DebugMessageN2("CAGuard::WaitFor: average latency  %.3f ns over %ld waits", mAverageLatencyAccumulator / mAverageLatencyCount, mAverageLatencyCount);
			mAverageLatencyCount = 0;
			mAverageLatencyAccumulator = 0.0;
		}
	#endif

	#if	Log_WaitOwnership
		DebugPrintfRtn(DebugPrintfFileComma "%p %.4f: CAGuard::WaitFor: thread %p waited on %s, owner: %p\n", pthread_self(), ((Float64)(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000000.0), pthread_self(), mName, mOwner);
	#endif

	theAnswer = theError == ETIMEDOUT;
#elif TARGET_OS_WIN32
	ThrowIf(GetCurrentThreadId() != mOwner, CAException(1), "CAGuard::WaitFor: A thread has to have locked a guard be for it can wait");

	#if	Log_TimedWaits
		DebugMessageN1("CAGuard::WaitFor: waiting %.0f", (Float64)inNanos);
	#endif

	//	the time out is specified in milliseconds(!)
	UInt32 theWaitTime = static_cast<UInt32>(inNanos / 1000000ULL);

	#if	Log_TimedWaits || Log_Latency || Log_Average_Latency
		UInt64	theStartNanos = CAHostTimeBase::GetCurrentTimeInNanos();
	#endif

	mOwner = 0;

	#if	Log_WaitOwnership
		DebugPrintfRtn(DebugPrintfFileComma "%lu %.4f: CAGuard::WaitFor: thread %lu is waiting on %s, owner: %lu\n", GetCurrentThreadId(), ((Float64)(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000000.0), GetCurrentThreadId(), mName, mOwner);
	#endif
	
	ReleaseMutex(mMutex);
	HANDLE theHandles[] = { mMutex, mEvent };
	OSStatus theError = WaitForMultipleObjects(2, theHandles, true, theWaitTime);
	ThrowIf((theError != WAIT_OBJECT_0) && (theError != WAIT_TIMEOUT), CAException(GetLastError()), "CAGuard::WaitFor: Wait got an error");
	mOwner = GetCurrentThreadId();
	ResetEvent(mEvent);
	
	#if	Log_TimedWaits || Log_Latency || Log_Average_Latency
		UInt64	theEndNanos = CAHostTimeBase::GetCurrentTimeInNanos();
	#endif
	
	#if	Log_TimedWaits
		DebugMessageN1("CAGuard::WaitFor: waited  %.0f", (Float64)(theEndNanos - theStartNanos));
	#endif
	
	#if	Log_Latency
		DebugMessageN1("CAGuard::WaitFor: latency  %.0f", (Float64)((theEndNanos - theStartNanos) - inNanos));
	#endif
	
	#if	Log_Average_Latency
		++mAverageLatencyCount;
		mAverageLatencyAccumulator += (theEndNanos - theStartNanos) - inNanos;
		if(mAverageLatencyCount >= 50)
		{
			DebugMessageN2("CAGuard::WaitFor: average latency  %.3f ns over %ld waits", mAverageLatencyAccumulator / mAverageLatencyCount, mAverageLatencyCount);
			mAverageLatencyCount = 0;
			mAverageLatencyAccumulator = 0.0;
		}
	#endif

	#if	Log_WaitOwnership
		DebugPrintfRtn(DebugPrintfFileComma "%lu %.4f: CAGuard::WaitFor: thread %lu waited on %s, owner: %lu\n", GetCurrentThreadId(), ((Float64)(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000000.0), GetCurrentThreadId(), mName, mOwner);
	#endif

	theAnswer = theError == WAIT_TIMEOUT;
#endif

	return theAnswer;
}