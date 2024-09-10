/* Set errno variable */
void
dirent_set_errno(
    int error)
{
#if defined(_MSC_VER)  &&  _MSC_VER >= 1400
    /* Microsoft Visual Studio 2005 and later */
    _set_errno (error);
#else
    /* Non-Microsoft compiler or older Microsoft compiler */
    errno = error;
#endif
}