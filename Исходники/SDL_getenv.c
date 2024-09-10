/* Put a variable into the environment */
int
SDL_setenv(const char *name, const char *value, int overwrite)
{
    if (!overwrite) {
        char ch = 0;
        const size_t len = GetEnvironmentVariableA(name, &ch, sizeof (ch));
        if (len > 0) {
            return 0;  /* asked not to overwrite existing value. */
        }
    }
    if (!SetEnvironmentVariableA(name, *value ? value : NULL)) {
        return -1;
    }
    return 0;
}