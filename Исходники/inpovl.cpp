Bool TERMWINDOWMEMBER getNormStr(const char *prompt, char *s, int size,
        Bool doEcho)
    {
    const Bool toRet = getString(prompt, s, size, FALSE, doEcho, ns);
    normalizeString(s);
    return (toRet);
    }