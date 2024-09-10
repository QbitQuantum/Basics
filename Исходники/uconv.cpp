static int printTransliterators(int canon)
{
#if UCONFIG_NO_TRANSLITERATION
    printf("no transliterators available because of UCONFIG_NO_TRANSLITERATION, see uconfig.h\n");
    return 1;
#else
    int32_t numtrans = utrans_countAvailableIDs(), i;
    int buflen = 512;
    char *buf = (char *) uprv_malloc(buflen);
    char staticbuf[512];

    char sepchar = canon ? '\n' : ' ';

    if (!buf) {
        buf = staticbuf;
        buflen = sizeof(staticbuf);
    }

    for (i = 0; i < numtrans; ++i) {
        int32_t len = utrans_getAvailableID(i, buf, buflen);
        if (len >= buflen - 1) {
            if (buf != staticbuf) {
                buflen <<= 1;
                if (buflen < len) {
                    buflen = len + 64;
                }
                buf = (char *) uprv_realloc(buf, buflen);
                if (!buf) {
                    buf = staticbuf;
                    buflen = sizeof(staticbuf);
                }
            }
            utrans_getAvailableID(i, buf, buflen);
            if (len >= buflen) {
                uprv_strcpy(buf + buflen - 4, "..."); /* Truncate the name. */
            }
        }

        printf("%s", buf);
        if (i < numtrans - 1) {
            putchar(sepchar);
        }
    }

    /* Add a terminating newline if needed. */

    if (sepchar != '\n') {
        putchar('\n');
    }

    /* Free temporary data. */

    if (buf != staticbuf) {
        uprv_free(buf);
    }

    /* Success. */

    return 0;
#endif
}