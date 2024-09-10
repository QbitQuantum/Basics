file::offset_type ufs_file_base::_size()
{
#ifdef BOOST_MSVC
    struct _stat64 st;
    stxxl_check_ge_0(_fstat64(file_des, &st), io_error);
#else
    struct stat st;
    stxxl_check_ge_0(::fstat(file_des, &st), io_error);
#endif
    return st.st_size;
}