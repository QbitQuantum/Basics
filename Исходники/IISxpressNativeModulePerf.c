ULONG
PerfAutoInitialize(
    void
)
{
    ULONG Status = ERROR_SUCCESS;

    Status = PerfStartProvider(
            (LPGUID) & ProviderGuid_IISxpressNativeModuleperf_1,
            (PERFLIBREQUEST) ControlCallback_IISxpressNativeModuleperf_1,
            & hDataSource_IISxpressNativeModuleperf_1);
    if (Status != ERROR_SUCCESS) {
        goto Cleanup;
    }

    Status = PerfSetCounterSetInfo(
            hDataSource_IISxpressNativeModuleperf_1,
            (PPERF_COUNTERSET_INFO) & CtrSet_IISxpressNativeModuleperf_1_1,
            dwCtrSet_IISxpressNativeModuleperf_1_1);
    if (Status != ERROR_SUCCESS) {
        goto Cleanup;
    }

Cleanup:
    if (Status != ERROR_SUCCESS) {
        PerfStopProvider(hDataSource_IISxpressNativeModuleperf_1);
    }
    return Status;
}