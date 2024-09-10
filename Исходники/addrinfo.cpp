void dbload()
{
    // If the file doesn't exist, there is no DB to load
    if(!FileExists(dbpath))
        return;

    dprintf("Loading database...");
    DWORD ticks = GetTickCount();

    // Multi-byte (UTF8) file path converted to UTF16
    WString databasePathW = StringUtils::Utf8ToUtf16(dbpath);

    // Decompress the file if compression was enabled
    bool useCompression = !settingboolget("Engine", "DisableCompression");
    LZ4_STATUS lzmaStatus = LZ4_INVALID_ARCHIVE;
    {
        lzmaStatus = LZ4_decompress_fileW(databasePathW.c_str(), databasePathW.c_str());

        // Check return code
        if(useCompression && lzmaStatus != LZ4_SUCCESS && lzmaStatus != LZ4_INVALID_ARCHIVE)
        {
            dputs("\nInvalid database file!");
            return;
        }
    }

    // Open the file for reading by the JSON parser
    FILE* jsonFile = nullptr;
    long jsonFileSize = 0;

    if(_wfopen_s(&jsonFile, databasePathW.c_str(), L"rb"))
    {
        dputs("\nFailed to open database file!");
        return;
    }

    // Get the current file size
    fseek(jsonFile, 0, SEEK_END);
    jsonFileSize = ftell(jsonFile);
    fseek(jsonFile, 0, SEEK_SET);

    // Verify that the file size is greater than 0.
    // This corrects a bug when a file exists, but there is no data inside.
    JSON root = nullptr;

    if(jsonFileSize > 0)
        root = json_loadf(jsonFile, 0, 0);

    // Release the file handle and re-compress
    fclose(jsonFile);

    if(lzmaStatus != LZ4_INVALID_ARCHIVE && useCompression)
        LZ4_compress_fileW(databasePathW.c_str(), databasePathW.c_str());

    // Validate JSON load status
    if(!root)
    {
        dputs("\nInvalid database file (JSON)!");
        return;
    }

    // Finally load all structures
    CommentCacheLoad(root);
    LabelCacheLoad(root);
    BookmarkCacheLoad(root);
    FunctionCacheLoad(root);
    LoopCacheLoad(root);
    BpCacheLoad(root);

    // Free root
    json_decref(root);
    dprintf("%ums\n", GetTickCount() - ticks);
}