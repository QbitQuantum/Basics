/*
 * This is stupid. But it's just a bit of fun.
 *
 * The file descriptor of the sender is prepended to the
 * message sent to clients, so you can distinguish
 * each other with a degree of sanity. This gives a
 * similar effect to an IRC session. But stupider.
 */
static char *chat_filter(char *buf, size_t size, int fd, int *nwritten)
{
    char *result = NULL;
    size_t n = 0;
    const char *p;
    int i;

    n = 32;
    result = (char *) safe_malloc(n);
    i = Snprintf(result, n, "<user%d> ", fd);

    /* Escape control characters. */
    for (p = buf; p - buf < size; p++) {
        char repl[32];
        int repl_len;

        if (isprint((int) (unsigned char) *p) || *p == '\r' || *p == '\n' || *p == '\t') {
            repl[0] = *p;
            repl_len = 1;
        } else {
            repl_len = Snprintf(repl, sizeof(repl), "\\%03o", (unsigned char) *p);
        }

        if (i + repl_len > n) {
            n = (i + repl_len) * 2;
            result = (char *) safe_realloc(result, n + 1);
        }
        memcpy(result + i, repl, repl_len);
        i += repl_len;
    }
    /* Trim to length. (Also does initial allocation when str is empty.) */
    result = (char *) safe_realloc(result, i + 1);
    result[i] = '\0';

    *nwritten = i;

    return result;
}