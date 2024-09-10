void SCTStatistics::CalculateCpuStats()
{
	PDH_FMT_COUNTERVALUE value; 

	if(mCanReadCpu)
	{
		if((mLastSampleTime + 1000) < GetTickCount())
		{
			mLastSampleTime = GetTickCount(); 

			PdhCollectQueryData(mQueryHandle);
        
			PdhGetFormattedCounterValue(mCounterHandle, PDH_FMT_LONG, NULL, &value);

			mCpuUsage = value.longValue;
		}
	}
}