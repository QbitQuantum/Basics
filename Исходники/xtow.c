wchar_t * __cdecl _ui64tow (
        unsigned __int64 val,
        wchar_t *buf,
        int radix
        )
{
        char astring[I64_SIZE_LENGTH];

        _ui64toa (val, astring, radix);
#if defined(_NTSUBSET_)
        mbstowcs(buf, astring, I64_SIZE_LENGTH);
#else
        MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, astring, -1,
                            buf, I64_SIZE_LENGTH);
#endif
        return (buf);
}