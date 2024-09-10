void TraceDone(void)
{
    CloseTrace();
    if (g_LogFile) { delete g_LogFile; g_LogFile = NULL; }
}