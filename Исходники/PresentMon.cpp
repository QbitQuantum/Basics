static void UpdateProcessInfo_Realtime(ProcessInfo& info, uint64_t now, uint32_t thisPid)
{
    if (now - info.mLastRefreshTicks > 1000) {
        info.mLastRefreshTicks = now;
        char path[MAX_PATH] = "<error>";
        HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, thisPid);
        if (h) {
            GetModuleFileNameExA(h, NULL, path, sizeof(path) - 1);
            std::string name = PathFindFileNameA(path);
            if (name != info.mModuleName) {
                info.mChainMap.clear();
                info.mModuleName = name;
            }
            CloseHandle(h);
        } else {
            info.mChainMap.clear();
        }
    }
    // remove chains without recent updates
    map_erase_if(info.mChainMap, [now](const std::pair<const uint64_t, SwapChainData>& entry) {
        return now - entry.second.mLastUpdateTicks > CHAIN_TIMEOUT_THRESHOLD_TICKS;
    });
}