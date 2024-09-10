void pline
VA_DECL(const char *, line)
#endif /* USE_STDARG | USE_VARARG */
{       /* start of vpline() or of nested block in USE_OLDARG's pline() */
    char pbuf[3 * BUFSZ];
    int ln;
    xchar msgtyp;
    /* Do NOT use VA_START and VA_END in here... see above */

    if (!line || !*line)
        return;
#ifdef HANGUPHANDLING
    if (program_state.done_hup)
        return;
#endif
    if (program_state.wizkit_wishing)
        return;

    if (index(line, '%')) {
        Vsprintf(pbuf, line, VA_ARGS);
        line = pbuf;
    }
    if ((ln = (int) strlen(line)) > BUFSZ - 1) {
        if (line != pbuf)                          /* no '%' was present */
            (void) strncpy(pbuf, line, BUFSZ - 1); /* caveat: unterminated */
        /* truncate, preserving the final 3 characters:
           "___ extremely long text" -> "___ extremely l...ext"
           (this may be suboptimal if overflow is less than 3) */
        (void) strncpy(pbuf + BUFSZ - 1 - 6, "...", 3);
        /* avoid strncpy; buffers could overlap if excess is small */
        pbuf[BUFSZ - 1 - 3] = line[ln - 3];
        pbuf[BUFSZ - 1 - 2] = line[ln - 2];
        pbuf[BUFSZ - 1 - 1] = line[ln - 1];
        pbuf[BUFSZ - 1] = '\0';
        line = pbuf;
    }
    if (!iflags.window_inited) {
        raw_print(line);
        iflags.last_msg = PLNMSG_UNKNOWN;
        return;
    }
#ifndef MAC
    if (no_repeat && !strcmp(line, toplines))
        return;
#endif /* MAC */
    if (vision_full_recalc)
        vision_recalc(0);
    if (u.ux)
        flush_screen(1); /* %% */
    msgtyp = msgtype_type(line);
    if (msgtyp == MSGTYP_NOSHOW) return;
    if (msgtyp == MSGTYP_NOREP && !strcmp(line, prevmsg)) return;
    putstr(WIN_MESSAGE, 0, line);
    /* this gets cleared after every pline message */
    iflags.last_msg = PLNMSG_UNKNOWN;
    strncpy(prevmsg, line, BUFSZ);
    if (msgtyp == MSGTYP_STOP) display_nhwindow(WIN_MESSAGE, TRUE); /* --more-- */

#if !(defined(USE_STDARG) || defined(USE_VARARGS))
    /* provide closing brace for the nested block
       which immediately follows USE_OLDARGS's VA_DECL() */
    VA_END();
#endif
}