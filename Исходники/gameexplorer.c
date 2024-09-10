/*******************************************************************************
 *  GAMEUX_RegisterGame
 *
 * Internal helper function. Registers game associated with given GDF binary in
 * Game Explorer. Implemented in gameexplorer.c
 *
 * Parameters:
 *  sGDFBinaryPath                  [I]     path to binary containing GDF file in
 *                                          resources
 *  sGameInstallDirectory           [I]     path to directory, where game installed
 *                                          it's files.
 *  installScope                    [I]     scope of game installation
 *  pInstanceID                     [I/O]   pointer to game instance identifier.
 *                                          If pointing to GUID_NULL, then new
 *                                          identifier will be generated automatically
 *                                          and returned via this parameter
 */
static HRESULT GAMEUX_RegisterGame(LPCWSTR sGDFBinaryPath,
        LPCWSTR sGameInstallDirectory,
        GAME_INSTALL_SCOPE installScope,
        GUID *pInstanceID)
{
    HRESULT hr = S_OK;
    struct GAMEUX_GAME_DATA GameData;

    TRACE("(%s, %s, 0x%x, %s)\n", debugstr_w(sGDFBinaryPath), debugstr_w(sGameInstallDirectory), installScope, debugstr_guid(pInstanceID));

    GAMEUX_initGameData(&GameData);
    GameData.sGDFBinaryPath = HeapAlloc(GetProcessHeap(), 0, (lstrlenW(sGDFBinaryPath)+1)*sizeof(WCHAR));
    lstrcpyW(GameData.sGDFBinaryPath, sGDFBinaryPath);
    GameData.sGameInstallDirectory = HeapAlloc(GetProcessHeap(), 0, (lstrlenW(sGameInstallDirectory)+1)*sizeof(WCHAR));
    lstrcpyW(GameData.sGameInstallDirectory, sGameInstallDirectory);
    GameData.installScope = installScope;

    /* generate GUID if it was not provided by user */
    if(IsEqualGUID(pInstanceID, &GUID_NULL))
        hr = CoCreateGuid(pInstanceID);

    GameData.guidInstanceId = *pInstanceID;

    /* load data from GDF binary */
    if(SUCCEEDED(hr))
    {
        struct parse_gdf_thread_param thread_param;
        HANDLE thread;
        DWORD ret;

        thread_param.GameData = &GameData;
        if(!(thread = CreateThread(NULL, 0, GAMEUX_ParseGDFBinary, &thread_param, 0, &ret)))
        {
            ERR("Failed to create thread.\n");
            hr = E_FAIL;
            goto done;
        }
        ret = WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        if(ret != WAIT_OBJECT_0)
        {
            ERR("Wait failed (%#x).\n", ret);
            hr = E_FAIL;
            goto done;
        }
        hr = thread_param.hr;
    }

    /* save data to registry */
    if(SUCCEEDED(hr))
        hr = GAMEUX_WriteRegistryRecord(&GameData);

done:
    GAMEUX_uninitGameData(&GameData);
    TRACE("returning 0x%08x\n", hr);
    return hr;
}