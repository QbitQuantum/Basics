void InfoCPU::Update()
{
	PDH_FMT_COUNTERVALUE value;

	if (mcanReadCpu)
	{
		if ((mlastSampleTime + 1000) < GetTickCount())
		{
			mlastSampleTime = GetTickCount();

			PdhCollectQueryData(mqueryHandle);

			PdhGetFormattedCounterValue(mcounterHandle, PDH_FMT_LONG, NULL, &value);

			mcpuUsage = value.longValue;
		}
	}

	return;
}