static int
sysctl_vscanf(const char *name, const char *fmt, va_list ap)
{
    char *path = NULL;
    FILE *s = NULL;
    int rv;

    path = mprintf("/proc/sys/%s", name);
    if (!path) {
        rv = -errno;
        goto fail;
    }

    s = fopen(path, "r");
    if (!s) {
        rv = -errno;
        goto fail;
    }

    rv = vfscanf(s, fmt, ap);
fail:
    if (s)
        fclose(s);

    if (path)
        free(path);

    return rv;
}