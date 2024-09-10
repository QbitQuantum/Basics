        bool is_network_path(const std::wstring& path)
        {
            wchar_t buff[MAX_PATH];
            return
#if defined(ONECORE)
                PathIsUNCEx(path.c_str(), nullptr)
#else
                PathIsUNC(path.c_str())
#endif
                || (GetVolumePathName(path.c_str(), buff, MAX_PATH) && GetDriveType(buff) == DRIVE_REMOTE);
        }