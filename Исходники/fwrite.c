size_t
fwrite(const void* a, size_t size, size_t nelem, FILE* str)
{
    size_t ns = (size * nelem);
    size_t n;

    if ((ns == 0) || (a == NULL) || (str == NULL))
        return 0;

    _LOCK_FILE(str);

#if (BYTES_PER_WORD==1)
    n = _writebinary(a,ns,str);
#else

    if (str->_Mode & M_BINARY) {
        n = _writebinary(a,ns,str);
    } else {
        n = _writechar(a,ns,str);
    }
#endif

    _UNLOCK_FILE(str);

    return n / size;

}