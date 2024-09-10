JNIEXPORT jdouble JNICALL Java_org_hyperic_hq_plugin_mssql_PDH_pdhGetRawCounterValue(JNIEnv *env, jclass, jlong counter) {
    HCOUNTER  h_counter = (HCOUNTER)counter;
    PDH_RAW_COUNTER raw_value;
	DWORD type;

	PDH_STATUS status = PdhGetRawCounterValue(h_counter, &type, &raw_value);

    if (status != ERROR_SUCCESS) {
        plugin_throw_exception(env, get_error_message(status));
        return 0;
    }

	return (jdouble)raw_value.FirstValue;
}