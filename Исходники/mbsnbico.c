extern "C" int __cdecl _mbsnbicoll(
    const unsigned char* s1,
    const unsigned char* s2,
    size_t n
) {
    return _mbsnbicoll_l(s1, s2, n, NULL);
}