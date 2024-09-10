static BOOL
collect_profile(PDH_profile *prof)
{

	BOOL ret = FALSE;
	PDH_FMT_COUNTERVALUE counter_val;
	PDH_STATUS rval;

	__try {
		if ((rval=PdhCollectQueryData(prof->hQuery)) == ERROR_SUCCESS) {
			if (PdhGetFormattedCounterValue(prof->hCounter,
				PDH_FMT_LONG, NULL, &counter_val) == ERROR_SUCCESS) {
				if (counter_val.CStatus == ERROR_SUCCESS) {
					prof->value = counter_val.longValue;
					ret = TRUE;
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
		ret = FALSE;
	}
	return (ret);
}