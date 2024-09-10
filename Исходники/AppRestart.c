int
wmain (
    int argc,
    const wchar_t* argv[],
    const wchar_t* envp[]
)
{
    HRESULT hr = E_FAIL;
    int i;


    UNREFERENCED_PARAMETER (envp);


    //
    // Have we been launched as part of a restart?
    //
    if (argc >= 2 &&
            0 == _wcsicmp (argv[1], L"/restarted")) {

        wprintf (L"The application has been restarted.\n");
        wprintf (L"Press ENTER to exit.\n");
        getwc (stdin);
        return 0;
    }

    //
    // Otherwise, we are being run normally.
    //

    //
    // Register the application for restart.
    //
    hr = RegisterApplicationRestart (L"/restarted",
                                     0);

    if (FAILED (hr)) {
        wprintf (L"RegisterApplicationRestart failed with 0x%08X\n", hr);
        return -1;
    }

    wprintf (L"Successfully registered this process for restart.\n");

    //
    // Wait at least 60 seconds before crashing, so this process becomes eligible for restart.
    //
    wprintf (L"Waiting 62 seconds...");

    for (i = 0; i < 62; ++i) {
        wprintf (L" %d", i);

        Sleep (1000);
    }

    wprintf (L"\n");

    //
    // Crash the application by writing to a NULL pointer.
    //
    wprintf (L"Crashing the application...\n");
    fflush (stdout);

    *((int*)NULL) = 0;


    return 0;
}