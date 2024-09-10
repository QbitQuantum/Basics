static unsigned long getlastwaketime(void) {
    ULONGLONG lastwake;

    if (CallNtPowerInformation(LastWakeTime, NULL, 0, &lastwake, sizeof(lastwake)) == 0) {
        return (unsigned long)(lastwake/(1000000000/100));
    } else {
        return (unsigned long)(GetTickCount64()/1000);
    }
}