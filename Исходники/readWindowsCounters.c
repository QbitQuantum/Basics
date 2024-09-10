uint64_t readSingleCounter(char* path)
{
    PDH_HQUERY Query = NULL;
    PDH_HCOUNTER Counter;
	DWORD dwType;
	PDH_RAW_COUNTER Value;
	LONGLONG ret = 0;

    if(PdhOpenQuery(NULL, 0, &Query) == ERROR_SUCCESS) {
		if(PdhAddCounter(Query, path, 0, &Counter) == ERROR_SUCCESS &&
		   PdhCollectQueryData(Query) == ERROR_SUCCESS &&
		   PdhGetRawCounterValue(Counter, &dwType, &Value) == ERROR_SUCCESS) {
			ret = Value.FirstValue;
		}
        if (Query) PdhCloseQuery(Query);
    }
	return (uint64_t)ret;
}