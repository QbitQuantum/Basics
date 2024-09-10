JNIEXPORT jdouble JNICALL Java_org_krakenapps_winapi_PerformanceCounter_nextValue(JNIEnv *env, jobject obj, jint queryHandle, jint counterHandle) {
	PDH_HQUERY phQuery = (PDH_HQUERY)queryHandle;
	PDH_HCOUNTER phCounter = (PDH_HCOUNTER)counterHandle;
	PDH_FMT_COUNTERVALUE pValue;
	PDH_STATUS stat = 0;

	stat = PdhCollectQueryData(phQuery);
	if(stat != ERROR_SUCCESS) {
		fprintf(stderr, "PdhCollectQueryData: 0x%x\n", stat);
		return 0;
	}

	stat = PdhGetFormattedCounterValue(phCounter, PDH_FMT_DOUBLE, NULL, &pValue);
	if(stat != ERROR_SUCCESS) {
		fprintf(stderr, "PdhGetFormattedCounterValue: 0x%x\n", stat);
		return 0;
	}

	return pValue.doubleValue;
}