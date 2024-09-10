/* stdio functions - versions that translate to/from utf-8 */
static int GSDLLCALL
gsdll_stdin_utf8(void *instance, char *buf, int len)
{
    static WCHAR thiswchar = 0; /* wide character to convert to multiple bytes */
    static int nmore = 0;       /* number of additional encoding bytes to generate */
    UINT consolecp = 0;
    int nret = 0;               /* number of bytes returned to caller */
    int i;

    while (len) {
        while (len && nmore) {
            nmore--;
            *buf++ = 0x80 | ((thiswchar >> (6 * nmore)) & 0x3F), nret++;
            len--;
        }
        while (len) {
            if (0 >= _read(fileno(stdin), buf, 1))
                return nret;
            nret++, buf++, len--;
            if (buf[-1] == '\n')
                /* return at end of line (note: no traslation needed) */
                return nret;
            else if ((unsigned char)buf[-1] <= 0x7F)
                /* no translation needed for 7-bit ASCII codes */
                continue;
            else {
                /* extended character, may be double */
                BYTE dbcsstr[2];

                dbcsstr[0] = buf[-1];
                if (!consolecp)
                    consolecp = GetConsoleCP();
                thiswchar = L'?'; /* initialize in case the conversion below fails */
                if (IsDBCSLeadByteEx(consolecp, dbcsstr[0])) {
                    /* double-byte character code, fetch the trail byte */
                    _read(fileno(stdin), &dbcsstr[1], 1);
                    MultiByteToWideChar(consolecp, 0, dbcsstr, 2, &thiswchar, 1);
                }
                else {
                    MultiByteToWideChar(consolecp, 0, dbcsstr, 1, &thiswchar, 1);
                }
                /* convert thiswchar to utf-8 */
                if (thiswchar <= 0x007F) {          /* encoded as single byte */
                    buf[-1] = (char)thiswchar;
                } else if (thiswchar <= 0x07FF) {   /* encoded as 2 bytes */
                    buf[-1] = 0xC0 | ((thiswchar >> 6) & 0x1F);
                    nmore = 1;
                    break;
                } else if (thiswchar <= 0xFFFF) {   /* encoded as 3 bytes */
                    buf[-1] = 0xE0 | ((thiswchar >> 12) & 0xF);
                    nmore = 2;
                    break;
                } else