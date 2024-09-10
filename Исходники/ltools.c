/**
 * @param: the string (at stack -1)
 * @return: the quoted string (push to stack -1)
 */
static int l_repr_string(lua_State *L)
{
    size_t size;
    const char *src = lua_tolstring(L, -1, &size);
    /* calculate the single-quote vs. double-quote */
    size_t single_quote=0, double_quote=0;
    for (size_t i=0; i<size; i++) {
        if (src[i] == '"')
            ++double_quote;
        if (src[i] == '\'')
            ++single_quote;
    }
    char quote = (double_quote > single_quote) ? '\'' : '"';
    wchar_t wstr[size+1];
    size_t retsize = mbstowcs(wstr, src, size+1);

    /* start of luaL_Buffer */
    luaL_Buffer b;
    luaL_buffinit(L, &b);
    luaL_addchar(&b, quote);

    /* if not a valid utf-8 string we use isprint() to check printable char */
    if (retsize == (size_t)-1) {
        for (; size--; src++) {
            switch (*src) {
            case '\\':
                luaL_addlstring(&b, "\\\\", 2);
                break;
            case '\r':
                luaL_addlstring(&b, "\\r", 2);
                break;
            case '\n':
                luaL_addlstring(&b, "\\n", 2);
                break;
            default:
                if (*src == quote) {
                    luaL_addchar(&b, '\\');
                    luaL_addchar(&b, quote);
                } else if (isprint(*src)) {
                    luaL_addchar(&b, *src);
                } else {
                    char repr_char[5];
                    /* forget to cast unsigned leads to segmentation fault */
                    sprintf(repr_char, "\\%03u", (unsigned char)(*src));
                    luaL_addlstring(&b, repr_char, 4);
                }
                break;
            }
        }
    } else {
        /* for utf-8 string we use iswprint() */
        for (size_t i = 0; i < retsize; i++) {
            switch (wstr[i]) {
            case L'\\':
                luaL_addlstring(&b, "\\\\", 2);
                break;
            case L'\r':
                luaL_addlstring(&b, "\\r", 2);
                break;
            case L'\n':
                luaL_addlstring(&b, "\\n", 2);
                break;
            default:
                if (wstr[i] == (wchar_t)quote) {
                    luaL_addchar(&b, '\\');
                    luaL_addchar(&b, quote);
                } else {
                    char utf8str[MB_CUR_MAX];
                    int wssize = wctomb(utf8str, wstr[i]);
                    /* most utf-8 character should be printable */
                    if (iswprint(wstr[i])) {
                        luaL_addlstring(&b, utf8str, wssize);
                    } else {
                        char repr_char[wssize*4+1];
                        for (int j=0; j<wssize; j++) {
                            /* forget to cast unsigned leads to segmentation fault */
                            sprintf(repr_char, "\\%03u", (unsigned char)utf8str[j]);
                            luaL_addlstring(&b, repr_char, 4);
                        }
                    }
                }
                break;
            }
        }
        size_t zs = strlen(src);
        if (zs != size) {
            for (; zs<size; zs++) {
                switch (src[zs]) {
                case '\\':
                    luaL_addlstring(&b, "\\\\", 2);
                    break;
                case '\r':
                    luaL_addlstring(&b, "\\r", 2);
                    break;
                case '\n':
                    luaL_addlstring(&b, "\\n", 2);
                    break;
                default:
                    if (src[zs] == quote) {
                        luaL_addchar(&b, '\\');
                        luaL_addchar(&b, quote);
                    } else if (isprint(src[zs])) {
                        luaL_addchar(&b, src[zs]);
                    } else {
                        char repr_char[5];
                        /* forget to cast unsigned leads to segmentation fault */
                        sprintf(repr_char, "\\%03u", (unsigned char)(src[zs]));
                        luaL_addlstring(&b, repr_char, 4);
                    }
                    break;
                }
            }
        }
    }
    luaL_addchar(&b, quote);
    luaL_pushresult(&b);
    /* end of luaL_Buffer */

    return 1;
}