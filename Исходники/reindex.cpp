int wmain(int argc,  wchar_t *argv[])
{
    // initialize COM before doing anything else, since the IShellLibrary API depends on COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        CMetaCommand::PFNCREATECOMMAND rgMainCmds[] =
        {
            CMetaCommand::Create<CReindexMatchingFileTypeCommand>,
            CMetaCommand::Create<CReindexMatchingMimeTypeCommand>,
            CMetaCommand::Create<CReindexMatchingWhereClauseCommand>,
        };
        {
            PCWSTR pszExeName = PathFindFileNameW(CONSUME_NEXT_ARG(argv, argc));
            CMetaCommand main(pszExeName, L"Reindexes the files that match the requirements specified. \nreindex <command> -? will give you the usage for each command", rgMainCmds, ARRAYSIZE(rgMainCmds));
            main.Execute(const_cast<PCWSTR *>(argv), argc);
        }
        CoUninitialize();
    }

    return 0;
}