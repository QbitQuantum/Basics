static int is_821_dot_string(char *local_part, char *end, int flags)
{
    char   *cp;
    int     ch;

    /*
     * Detect any deviations from the definition of dot-string. We could use
     * lookup tables to speed up some of the work, but hey, how large can a
     * local-part be anyway?
     */
    if (local_part == end || local_part[0] == 0 || local_part[0] == '.')
        return (NO);
    for (cp = local_part; cp < end && (ch = *(unsigned char *) cp) != 0; cp++) {
        if (ch == '.' && cp[1] == '.')
            return (NO);
        if (ch > 127 && !(flags & QUOTE_FLAG_8BITCLEAN))
            return (NO);
        if (ch == ' ')
            return (NO);
        if (ISCNTRL(ch))
            return (NO);
        if (ch == '<' || ch == '>'
                || ch == '(' || ch == ')'
                || ch == '[' || ch == ']'
                || ch == '\\' || ch == ','
                || ch == ';' || ch == ':'
                || (ch == '@' && !(flags & QUOTE_FLAG_EXPOSE_AT)) || ch == '"')
            return (NO);
    }
    if (cp[-1] == '.')
        return (NO);
    return (YES);
}