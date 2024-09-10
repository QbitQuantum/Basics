int is_ignored_process()
{
    wchar_t process_path[MAX_PATH];
    GetModuleFileNameW(NULL, process_path, MAX_PATH);
    GetLongPathNameW(process_path, process_path, MAX_PATH);

    for (uint32_t idx = 0; g_ignored_processpaths[idx] != NULL; idx++) {
        if(!wcsicmp(g_ignored_processpaths[idx], process_path)) {
            return 1;
        }
    }
    return 0;
}