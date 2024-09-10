void ScreensaverAllow(bool allow)
{
    EXECUTION_STATE flags = ES_CONTINUOUS;
    if (!allow)
        flags |= ES_DISPLAY_REQUIRED;
    SetThreadExecutionState(flags);
}