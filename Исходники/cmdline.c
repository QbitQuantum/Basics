VOID
WINAPI
InitCommandLines(VOID)
{
    PRTL_USER_PROCESS_PARAMETERS Params;

    /* get command line */
    Params = NtCurrentPeb()->ProcessParameters;
    RtlNormalizeProcessParams (Params);

    /* initialize command line buffers */
    CommandLineStringW.Length = Params->CommandLine.Length;
    CommandLineStringW.MaximumLength = CommandLineStringW.Length + sizeof(WCHAR);
    CommandLineStringW.Buffer = RtlAllocateHeap(GetProcessHeap(),
                                                HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY,
                                                CommandLineStringW.MaximumLength);
    if (CommandLineStringW.Buffer == NULL)
    {
        return;
    }

    RtlInitAnsiString(&CommandLineStringA, NULL);

    /* Copy command line */
    RtlCopyUnicodeString(&CommandLineStringW,
                         &(Params->CommandLine));
    CommandLineStringW.Buffer[CommandLineStringW.Length / sizeof(WCHAR)] = 0;

    /* convert unicode string to ansi (or oem) */
    if (bIsFileApiAnsi)
        RtlUnicodeStringToAnsiString(&CommandLineStringA,
                                     &CommandLineStringW,
                                     TRUE);
    else
        RtlUnicodeStringToOemString(&CommandLineStringA,
                                    &CommandLineStringW,
                                    TRUE);

    CommandLineStringA.Buffer[CommandLineStringA.Length] = 0;

    bCommandLineInitialized = TRUE;
}