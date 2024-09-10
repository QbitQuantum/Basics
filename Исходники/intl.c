VOID
ParseSetupInf(VOID)
{
    INFCONTEXT InfContext;
    WCHAR szBuffer[30];

    if (!SetupFindFirstLineW(hSetupInf,
                             L"Unattend",
                             L"LocaleID",
                             &InfContext))
    {
        SetupCloseInfFile(hSetupInf);
        DPRINT1("SetupFindFirstLine failed\n");
        return;
    }

    if (!SetupGetStringFieldW(&InfContext, 1, szBuffer,
                              sizeof(szBuffer) / sizeof(WCHAR), NULL))
    {
        SetupCloseInfFile(hSetupInf);
        DPRINT1("SetupGetStringField failed\n");
        return;
    }

    UnattendLCID = wcstoul(szBuffer, NULL, 16);
    IsUnattendedSetupEnabled = 1;
    SetupCloseInfFile(hSetupInf);
}