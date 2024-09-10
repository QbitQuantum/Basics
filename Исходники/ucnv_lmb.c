static void
_LMBCSGetUnicodeSet(const UConverter *cnv,
                   USet *set,
                   UConverterUnicodeSet which,
                   UErrorCode *pErrorCode) {
    /* all but U+F6xx, see LMBCS explanation above (search for F6xx) */
    uset_addRange(set, 0, 0xf5ff);
    uset_addRange(set, 0xf700, 0x10ffff);
}