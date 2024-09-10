extern "C" unsigned int __cdecl _mbsnextc_l(
    const unsigned char* s,
    _locale_t plocinfo
) {
    unsigned int  next = 0;
    _LocaleUpdate _loc_update(plocinfo);
    /* validation section */
    _VALIDATE_RETURN(s != NULL, EINVAL, 0);

    /* don't skip forward 2 if the leadbyte is followed by EOS (dud string)
       also don't assert as we are too low-level
    */
    if (_ismbblead_l(*s, _loc_update.GetLocaleT()) && s[1] != '\0') {
        next = ((unsigned int) * s++) << 8;
    }

    next += (unsigned int) * s;
    return (next);
}