int
wmain (
    int argc,
    const wchar_t* argv[],
    const wchar_t* envp[]
)
{
    UNREFERENCED_PARAMETER (argc);
    UNREFERENCED_PARAMETER (argv);
    UNREFERENCED_PARAMETER (envp);


    //
    // Set-up a SEH frame.
    //
    __try {

        wprintf (L"Calling RaiseFailFastException...\n");
        fflush (stdout);

        //
        // Raise an exception in a fail-fast manner.
        //
        RaiseFailFastException (NULL,
                                NULL,
                                FAIL_FAST_GENERATE_EXCEPTION_ADDRESS);

    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        //
        // This should not be executed, since RaiseFailFastException will bypass this handler.
        //
        wprintf (L"This handler should NOT have been called!\n");
    }

    return 0;
}