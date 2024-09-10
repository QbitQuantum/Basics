static bool get_file_time(const std::string &filename, uint32_t *dostime)
{
    // Don't fail when building with -Werror
    (void) filename;
    (void) dostime;

#ifdef _WIN32
    FILETIME ft_local;
    HANDLE h_find;
    WIN32_FIND_DATAW ff32;

    auto w_filename = utf8_to_wcs(filename);
    if (!w_filename) {
        return false;
    }

    h_find = FindFirstFileW(w_filename.value().c_str(), &ff32);

    if (h_find != INVALID_HANDLE_VALUE)
    {
        FileTimeToLocalFileTime(&ff32.ftLastWriteTime, &ft_local);
        FileTimeToDosDateTime(&ft_local,
                              reinterpret_cast<LPWORD>(dostime) + 1,
                              reinterpret_cast<LPWORD>(dostime) + 0);
        FindClose(h_find);
        return true;
    } else {
        LOGE("%s: FindFirstFileW() failed: %s",
             filename.c_str(), ec_from_win32().message().c_str());
    }
#elif defined unix || defined __APPLE__ || defined __ANDROID__
    struct stat sb;
    struct tm t;

    if (stat(filename.c_str(), &sb) == 0) {
        time_t mtime = sb.st_mtime;
        if (!localtime_r(&mtime, &t)) {
            LOGE("localtime() failed");
            return false;
        }

        *dostime = tm_to_dosdate(&t);

        return true;
    } else {
        LOGE("%s: stat() failed: %s", filename.c_str(), strerror(errno));
    }
#endif
    return false;
}