unsigned int __cdecl _mbctokata_l(
    unsigned int c,
    _locale_t plocinfo
) {
    if (_ismbchira_l(c, plocinfo)) {
        c += 0xa1;

        if (c >= 0x837f) {
            c++;
        }
    }

    return (c);
}