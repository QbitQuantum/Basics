//============================================================================
static void FileSrvIpAddressCallback (
    ENetError       result,
    void *          param,
    const wchar_t     addr[]
) {
    NetCliGateKeeperDisconnect();

    if (IS_NET_ERROR(result)) {
        plString msg = plString::Format("FileSrvIpAddressRequest failed: %S", NetErrorToString(result));
        plStatusLog::AddLineS("patcher.log", msg.c_str());

        s_patchResult = result;
        s_downloadComplete = true;
    }
    
    // Start connecting to the server
    const char* caddr = hsWStringToString(addr);
    NetCliFileStartConnect(&caddr, 1, true);
    delete[] caddr;

    PathGetProgramDirectory(s_newPatcherFile, arrsize(s_newPatcherFile));
    GetTempFileNameW(s_newPatcherFile, kPatcherExeFilename, 0, s_newPatcherFile);
    plFileUtils::RemoveFile(s_newPatcherFile);

    NetCliFileManifestRequest(ManifestCallback, nil, s_manifest);
}