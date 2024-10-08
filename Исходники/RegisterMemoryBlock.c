int
wmain (
    int argc,
    const wchar_t* argv[],
    const wchar_t* envp[]
)
{
    HRESULT hr = E_FAIL;
    PSTATE_BLOCK SecondStateBlock = NULL;


    UNREFERENCED_PARAMETER (argc);
    UNREFERENCED_PARAMETER (argv);
    UNREFERENCED_PARAMETER (envp);


    //
    // Tell WER to collect the memory occupied by g_StateBlock as part of the dump file.
    //
    hr = WerRegisterMemoryBlock (&g_StateBlock, sizeof (STATE_BLOCK));

    if (FAILED (hr)) {
        wprintf (L"WerRegisterMemoryBlock has failed: 0x%08X\n", hr);
        return -1;
    }

    wprintf (L"Registered the global state block for collection.\n");

    //
    // Allocate a second state block from the heap, and register that as well.
    // Link up the second state block to the global one, so we can easily reach the pointer from the dump file.
    //
    SecondStateBlock = (PSTATE_BLOCK) malloc (sizeof (STATE_BLOCK));
    g_StateBlock.SecondStateBlock = SecondStateBlock;

    //
    // Put some strings in the state blocks.
    //
    if (SecondStateBlock) {
        hr = WerRegisterMemoryBlock (SecondStateBlock, sizeof (STATE_BLOCK));

        if (FAILED (hr)) {
            wprintf (L"WerRegisterMemoryBlock has failed: 0x%08X\n", hr);
            return -1;
        }

        wprintf (L"Registered the second state block for collection.\n");

        wcscpy_s (SecondStateBlock->Text, 256, L"Second state block is in the dump.");
        SecondStateBlock->SecondStateBlock = NULL;
    }

    wcscpy_s (g_StateBlock.Text, 256, L"First state block is in the dump.");

    //
    // Crash this application by writing to a NULL pointer.
    //
    wprintf (L"Crashing the application...\n");
    fflush (stdout);

    *((int*)NULL) = 0;


    return 0;
}