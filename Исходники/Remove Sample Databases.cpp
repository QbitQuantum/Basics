// Adds a line of wide text to the log file of the installer.
void WriteMsiLogEntry(MSIHANDLE hInstall, const wchar_t * pszMessage)
{
#ifdef TEST_HARNESS
    if (!hInstall)
    {
        MessageBoxW(NULL, pszMessage, L"Test harness message", 0);
        return;
    }
#endif

    PMSIHANDLE hRecord = MsiCreateRecord(1);
    // field 0 is the template
    MsiRecordSetStringW(hRecord, 0, L"RemoveSampleDatabases: [1]");
    // field 1, to be placed in [1] placeholder
    MsiRecordSetStringW(hRecord, 1, pszMessage);
    // send message to running installer
    MsiProcessMessage(hInstall, INSTALLMESSAGE_INFO, hRecord);
}