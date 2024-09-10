int mem_callback(CPUState *env, target_ulong pc, target_ulong addr,
                       target_ulong size, void *buf, bool is_write) {

    string_pos &sp = is_write ? write_text_tracker[pc] : read_text_tracker[pc];
    ustring_pos &usp = is_write ? write_utext_tracker[pc] : read_utext_tracker[pc];

    // ASCII
    for (unsigned int i = 0; i < size; i++) {
        uint8_t val = ((uint8_t *)buf)[i];
        if (isprint(val)) {
            sp.ch[sp.nch++] = val;
            // If we max out the string, chop it
            if (sp.nch == MAX_STRLEN - 1) {
                gzprintf(mem_report, "%.*s\n", sp.nch, sp.ch);
                sp.nch = 0;
            }
        }
        else {
            // Don't bother with strings shorter than min
            if (sp.nch >= min_strlen) {
                gzprintf(mem_report, "%.*s\n", sp.nch, sp.ch);
            }
            sp.nch = 0;
        }
    }

    // Don't consider one-byte reads/writes for UTF-16
    if (size < 2) {
        return 1;
    }

    // UTF-16-LE
    for (unsigned int i = 0; i < size; i+=2) {
        uint8_t vall = ((uint8_t *)buf)[i];
        uint8_t valh = ((uint8_t *)buf)[i+1];
        uint16_t val = (valh << 8) | vall;
        if (iswprint(val)) {
            usp.ch[usp.nch++] = val;
            // If we max out the string, chop it
            if (usp.nch == MAX_STRLEN - 1) {
                gsize bytes_written = 0;
                gchar *out_str = g_convert((gchar *)usp.ch, usp.nch*2,
                    "UTF-8", "UTF-16LE", NULL, &bytes_written, NULL);
                gzprintf(mem_report, "%s\n", out_str);
                g_free(out_str);
                usp.nch = 0;
            }
        }
        else {
            // Don't bother with strings shorter than min
            if (usp.nch >= min_strlen) {
                gsize bytes_written = 0;
                gchar *out_str = g_convert((gchar *)usp.ch, usp.nch*2,
                    "UTF-8", "UTF-16LE", NULL, &bytes_written, NULL);
                gzprintf(mem_report, "%s\n", out_str);
                g_free(out_str);
            }
            usp.nch = 0;
        }
    }

    return 1;
}