static void CreateIdentifyingEvent()
{
    char buf[32];
    auto pid = GetCurrentProcessId();
    snprintf(buf, sizeof buf, "Teippi #%d", pid);
    CreateEventA(NULL, FALSE, FALSE, buf);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        // Maybe should silently abort patching?
        MessageBoxA(0, "Second copy of Teippi has been loaded to same process.\n\
Crashing is very likely.", "Very important warning", 0);
    }