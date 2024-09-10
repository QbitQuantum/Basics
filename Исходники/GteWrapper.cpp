void Memcpy(wchar_t* target, wchar_t const* source, size_t count)
{
#if defined(WIN32)
    errno_t result = wmemcpy_s(target, count, source, count);
    (void)result;  // 0 on success
#else
    wmemcpy(target, source, count);
#endif
}