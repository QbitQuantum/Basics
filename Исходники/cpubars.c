void
ui_init(bool force_ascii)
{
        // Cell character 0 is always a space
        strcpy(ui_chars[0], " ");

#ifdef __STDC_ISO_10646__
        if (force_ascii) {
                ui_ascii = true;
                return;
        }

        // Encode Unicode cell characters using system locale
        char *origLocale = setlocale(LC_CTYPE, NULL);
        setlocale(LC_CTYPE, "");

        int ch;
        mbstate_t mbs;
        memset(&mbs, 0, sizeof mbs);
        for (ch = 1; ch < NCHARS; ch++) {
                int len = wcrtomb(ui_chars[ch], 0x2580 + ch, &mbs);
                if (len == -1 || !mbsinit(&mbs)) {
                        ui_ascii = true;
                        break;
                }
                ui_chars[ch][len] = 0;
        }

        // Restore the original locale
        setlocale(LC_CTYPE, origLocale);
#else
        ui_ascii = true;
#endif
}