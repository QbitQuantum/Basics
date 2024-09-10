extern "C" unsigned char * __cdecl _mbsninc_l(
        const unsigned char *string,
        size_t ccnt,
        _locale_t plocinfo
        )
{
    if (string == nullptr)
        return nullptr;

    return const_cast<unsigned char*>(string) + (unsigned int)_mbsnbcnt_l(string, ccnt, plocinfo);
}