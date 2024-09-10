BOOL QueryPerfData(printInfoStruct& pI)
{
	PDH_HQUERY hQuery = NULL;
	PDH_HCOUNTER hCounter = NULL;
	PDH_FMT_COUNTERVALUE_ITEM *pDisplayValues = NULL;
	DWORD dwBufferSize = 0, dwItemCount = 0;

	if (pI.wsFullPath.empty()) {
		std::wcout << "No performance counter path given!\n";
		return FALSE;
	}

	PDH_STATUS status = PdhOpenQuery(NULL, NULL, &hQuery);
	if (FAILED(status))
		goto die;

	status = PdhAddCounter(hQuery, pI.wsFullPath.c_str(), NULL, &hCounter);
	if (FAILED(status))
		goto die;

	status = PdhCollectQueryData(hQuery);
	if (FAILED(status))
		goto die;

	/* 
	/* Most counters need two queries to provide a value.
	/* Those which need only one will return the second.
	 */
	Sleep(pI.dwPerformanceWait);

	status = PdhCollectQueryData(hQuery);
	if (FAILED(status))
		goto die;

	status = PdhGetFormattedCounterArray(hCounter, pI.dwRequestedType,
										 &dwBufferSize, &dwItemCount, pDisplayValues);
	if (status != PDH_MORE_DATA)
		goto die;

	pDisplayValues = reinterpret_cast<PDH_FMT_COUNTERVALUE_ITEM*>(new BYTE[dwBufferSize]);
	status = PdhGetFormattedCounterArray(hCounter, pI.dwRequestedType,
										 &dwBufferSize, &dwItemCount, pDisplayValues);

	if (FAILED(status))
		goto die;

	switch (pI.dwRequestedType)
	{
	case (PDH_FMT_LONG):
		pI.dValue = pDisplayValues[0].FmtValue.longValue;
	case (PDH_FMT_LARGE) :
		pI.dValue = pDisplayValues[0].FmtValue.largeValue;
	default:
		pI.dValue = pDisplayValues[0].FmtValue.doubleValue;
	}

	delete[]pDisplayValues;

	return TRUE;

die:
	FormatPDHError(status);
	delete[]pDisplayValues;
	return FALSE;
}