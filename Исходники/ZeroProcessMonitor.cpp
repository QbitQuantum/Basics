float ZeroProcessMonitor::GetCpuUsage() {
	// CPU 사용량 정보 수집
	PDH_STATUS pdhStatus = PdhCollectQueryData(cpuUsageQuery);

	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return -1;
	}

	// CPU 사용량 정보 처리
	PDH_FMT_COUNTERVALUE fmtValue;

	pdhStatus = PdhGetFormattedCounterValue(cpuUsageCounter, PDH_FMT_DOUBLE, NULL, &fmtValue);

	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return -1;
	}

	return static_cast<float>(fmtValue.doubleValue);
}