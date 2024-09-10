/* returns host keyboard mapping. used to initialize the keyboard map when
   starting with a black (default) config, so an educated guess works good
   enough most of the time :)

   FIXME: add more languages, constants are defined in winnt.h

   https://msdn.microsoft.com/en-us/library/windows/desktop/dd318693%28v=vs.85%29.aspx
*/
int kbd_arch_get_host_mapping(void)
{
    int n;
    int maps[KBD_MAPPING_NUM] = {
        KBD_MAPPING_US, KBD_MAPPING_UK, KBD_MAPPING_DE, KBD_MAPPING_DA,
        KBD_MAPPING_NO, KBD_MAPPING_FI, KBD_MAPPING_IT };
    int langids[KBD_MAPPING_NUM] = {
        MAKELANGID(LANG_ENGLISH,   SUBLANG_ENGLISH_US),
        MAKELANGID(LANG_ENGLISH,   SUBLANG_ENGLISH_UK),
        MAKELANGID(LANG_GERMAN,    SUBLANG_GERMAN),
        MAKELANGID(LANG_DANISH,    SUBLANG_DANISH_DENMARK),
        MAKELANGID(LANG_NORWEGIAN, SUBLANG_NORWEGIAN_BOKMAL),
        MAKELANGID(LANG_FINNISH,   SUBLANG_FINNISH_FINLAND),
        MAKELANGID(LANG_ITALIAN,   SUBLANG_ITALIAN)
    };
    int lang = (int)GetKeyboardLayout(0);

    /* try full match first */
    lang &= 0xffff; /* lower 16 bit contain the language id */
    for (n = 0; n < KBD_MAPPING_NUM; n++) {
        if (lang == langids[n]) {
            return maps[n];
        }
    }
    /* try only primary language */
    lang &= 0x3ff; /* lower 10 bit contain the primary language id */
    for (n = 0; n < KBD_MAPPING_NUM; n++) {
        if (lang == (langids[n] & 0x3ff)) {
            return maps[n];
        }
    }
    return KBD_MAPPING_US;
}