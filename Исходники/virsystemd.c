/**
 * virSystemdEscapeName:
 *
 * This function escapes various characters in @name and appends that
 * escaped string to @buf, in order to comply with the requirements
 * from systemd/machined.  Parameter @full_escape decides whether to
 * also escape dot as a first character and '-'.
 */
static void virSystemdEscapeName(virBufferPtr buf,
                                 const char *name,
                                 bool full_escape)
{
    static const char hextable[16] = "0123456789abcdef";

#define ESCAPE(c)                                                       \
    do {                                                                \
        virBufferAddChar(buf, '\\');                                    \
        virBufferAddChar(buf, 'x');                                     \
        virBufferAddChar(buf, hextable[(c >> 4) & 15]);                 \
        virBufferAddChar(buf, hextable[c & 15]);                        \
    } while (0)

#define VALID_CHARS                             \
        "0123456789"                            \
        "abcdefghijklmnopqrstuvwxyz"            \
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"            \
        ":-_.\\"

    if (full_escape && *name == '.') {
        ESCAPE(*name);
        name++;
    }

    while (*name) {
        if (*name == '/')
            virBufferAddChar(buf, '-');
        else if ((full_escape && *name == '-') ||
                 *name == '\\' ||
                 !strchr(VALID_CHARS, *name))
            ESCAPE(*name);
        else
            virBufferAddChar(buf, *name);
        name++;
    }

#undef ESCAPE
#undef VALID_CHARS
}