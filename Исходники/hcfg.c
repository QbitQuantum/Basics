/* Parse the key and value from a memory buffer. */
char *hcfg_parse(char *buf, char **key, char **val)
{
    char *ptr = NULL;

    *key = NULL;
    *val = NULL;

    /* Skip leading key whitespace. */
    while (isspace(*buf) && *buf != '\n')
        ++buf;

    /* Skip empty lines and comments. */
    if (*buf == '\n' || *buf == '#')
        goto endline;

    if (!isalnum(*buf) && *buf != '_')
        return NULL;

    /* Force key strings to be uppercase. */
    *key = buf;
    while (isalnum(*buf) || *buf == '_') {
        *buf = toupper(*buf);
        ++buf;
    }

    /* Check that key string was valid. */
    ptr = buf;
    while (isspace(*buf) && *buf != '\n')
        ++buf;

    if (*(buf++) != '=')
        return NULL;

    while (isspace(*buf) && *buf != '\n')
        ++buf;

    /* Kill whitespace and separator between key and value. */
    while (ptr < buf)
        *(ptr++) = '\0';

    /* Unquote the value string. */
    *val = buf;
    ptr = buf;
    while (*buf && *buf != '\n') {
        if (*buf ==  '#') goto endline;
        if (*buf == '\\') ++buf;
        *(ptr++) = *(buf++);
    }

  endline:
    buf += strcspn(buf, "\n");
    if (*buf == '\n')
        ++buf;

    /* Kill trailing value whitespace. */
    if (ptr) {
        do *(ptr--) = '\0';
        while (isspace(*ptr));
    }
    return buf;
}