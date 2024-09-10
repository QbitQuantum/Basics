int _CRTAPI1  Z_spawnlpe (int Arg1,const char* Arg2,const char* Arg3, DWORD64ARGS)
{

    int RetVal;

    SHORT sTimerHandle;
    ULONG ulElapsedTime;

    if (fInitDone == FALSE) {
        ApfInitDll();
    }
    TimerOpen(&sTimerHandle, MICROSECONDS);
    TimerInit(sTimerHandle);
    //
    // Call the api
    //
    RetVal = _spawnlpe(Arg1,Arg2,Arg3, ARGS64);
    //
    // Get the elapsed time
    //
    ulElapsedTime = TimerRead(sTimerHandle);
    ApfRecordInfo(I__spawnlpe, ulElapsedTime - ApfData[I_CALIBRATE].ulFirstTime);
    TimerClose(sTimerHandle);

    return(RetVal);
}