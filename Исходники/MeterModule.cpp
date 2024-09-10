HRESULT MeterModule::GetCurrentThreadCycleTime(bool getInProgressStats, ULONG64 *applicationTime, ULONG64 *totalTime)
{
	ErrorIf(NULL == applicationTime);
	ErrorIf(NULL == totalTime);

	ErrorIf(0 == QueryThreadCycleTime(this->thread, totalTime));

	if (this->startThreadCycleTime == 0 || !getInProgressStats)
	{
		*applicationTime = this->threadCycleTime;
	}
	else
	{
		*applicationTime = this->threadCycleTime + *totalTime - this->startThreadCycleTime;
	}

	return S_OK;
Error:
	return E_FAIL;
}