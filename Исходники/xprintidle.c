// Print a string in multibyte format
static void mbprint(const char* msg) {
    size_t len = mbsrtowcs(NULL, &msg, 0, NULL);
    if(len == (size_t)-1) {
        error(EXIT_FAILURE, errno, _("conversion to multibyte string failed"));
    }
    wchar_t* mb_msg = xmalloc((len + 1) * sizeof(wchar_t));
    mbsrtowcs(mb_msg, &msg, len + 1, NULL);
    wprintf(L"%ls\n", mb_msg);
    free(mb_msg);
}