bool zz_vfs_local::get_mtime (const char * file_name, uint64 * t) const
{
    struct __stat64 st;

    if (_stat64(file_name, &st) != 0) {
        return false;
    }
    *t = st.st_mtime;
    return true;
}