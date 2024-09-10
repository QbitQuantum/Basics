double getCpuLoad(){
    PDH_HCOUNTER Counter;
	DWORD dwType;
	PDH_FMT_COUNTERVALUE Value;
	double ret = 0;
	PDH_HQUERY cpu_load_query = NULL;
	
	if(PdhOpenQuery(NULL, 0, &cpu_load_query) == ERROR_SUCCESS) {
		if(PdhAddCounter(cpu_load_query, "\\Processor(_Total)\\% Processor Time", 0, &Counter) == ERROR_SUCCESS &&
		PdhCollectQueryData(cpu_load_query) == ERROR_SUCCESS &&
		PdhGetFormattedCounterValue(Counter, PDH_FMT_DOUBLE, &dwType, &Value) == ERROR_SUCCESS) {
			ret = (Value.doubleValue * getCpuNum()) / 100.0;
		}
		if (cpu_load_query) PdhCloseQuery(cpu_load_query);
	}
	return ret;
}