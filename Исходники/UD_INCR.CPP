//
// Implement the asynchronous step in terms of the synchronous form
//
EXPORT_C void CDbSyncIncremental::Next(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus)
	{
	TRequestStatus* pStatus=&aStatus;
	TRAPD(r,r=NextL(aStep.operator()()));	// MSVC issue!!! cannot use aStep() directly
	User::RequestComplete(pStatus,r);
	}