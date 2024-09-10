std::wstring find_swtor_log_path() {
    std::wstring path;
    
    wchar_t base_loc[MAX_PATH * 2]{};
    if ( SHGetSpecialFolderPathW(nullptr, base_loc, CSIDL_PERSONAL, FALSE) ) {
        path = base_loc;
        path += L"\\Star Wars - The Old Republic\\CombatLogs";
    }

    return path;
}