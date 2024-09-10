/* Process a stream, but just center its lines rather than trying to
 * format them neatly.
 */
static void
center_stream(FILE *stream, const char *name)
{
    wchar_t *line, *p;
    size_t length;
    size_t width;
    int cwidth;

    while ((line = get_line(stream, &length)) != NULL) {
        size_t l = length;

        while (l > 0 && iswspace(*line)) {
            ++line;
            --l;
        }
        length = l;
        for (p = line, width = 0; p < &line[length]; p++)
            width += (cwidth = wcwidth(*p)) > 0 ? cwidth : 1;
        l = width;
        while (l < goal_length) {
            putwchar(' ');
            l += 2;
        }
        wprintf(L"%.*ls\n", (int)length, line);
    }
    if (ferror(stream)) {
        warn("%s", name);
        ++n_errors;
    }
}