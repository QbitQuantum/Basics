static int _MatchSet (
    const ZChar* pattern, 
    const ZChar* string, 
    int *skip)
{
    int bFnd;
    const ZChar* pos;
    int notinset;
    int matched;
    ZChar lastchar;

    /*this tells whether ']' is found or not */
    bFnd = MI_FALSE;

    /* Skip the opening '['. */
    pos = pattern+1;

    /* See if we are matching a [^] set. */
    notinset = (*pos == '^');
    if (notinset) 
        pos++;

    /* See if the target character matches any character in the set. */
    matched = MI_FALSE;
    lastchar = '\0';

    while (*pos && *pos != ']' && !matched)
    {
        /* A range of characters is indicated by a '-' unless it's the first */
        /* character in the set (in which case it's just a character to be */
        /* matched. */
        if (*pos == '-' && lastchar != '\0')
        {
            pos++;
            if (*pos && *pos != ']')
            {
                matched = (_Toupper(*string) >= lastchar && 
                    _Toupper(*string) <= _Toupper(*pos));
                lastchar = _Toupper(*pos);
                pos++;
            }
        }
        else
        {
            /* Match a normal character in the set. */
            lastchar = _Toupper(*pos);
            matched = (_Toupper(*pos) == _Toupper(*string));
            if (!matched) 
                pos++;
        }
    }

    /* Find the trailing ']'.  If the set did not contain a closing ']' */
    /* we return a failed match. */
    while (*pos && *pos != ']') pos++;
    if (*pos == ']')
    {
        pos++;
        bFnd = MI_TRUE;
    }
    /*If ']' is not found and we reach end of string match is false */
    /*since this is invalid pattern */
    if (!*pos && !bFnd) 
        matched = MI_FALSE;

    /* Done. */
    *skip = (int)(pos-pattern);
    return matched == !notinset;
}