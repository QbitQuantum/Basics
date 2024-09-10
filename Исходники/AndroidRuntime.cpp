void AndroidRuntime::exit(int code)
{
    if (mExitWithoutCleanup) {
        ALOGI("VM exiting with result code %d, cleanup skipped.", code);
        ::_exit(code);
    } else {
        ALOGI("VM exiting with result code %d.", code);
        onExit(code);
        ::exit(code);
    }
}