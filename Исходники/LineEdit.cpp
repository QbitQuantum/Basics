char *lineedit_get_text(void)
{
    size_t wide_len, multibyte_max_len;
    mbstate_t state;
    wchar_t **p_wide_string = &(l.buf);
    char *padded_multibyte_string = NULL;
    char *multibyte_string = NULL;

    memset(&state, '\0', sizeof (state));

    wide_len = wcslen(l.buf);
    multibyte_max_len = wide_len * 4 + 1;
    padded_multibyte_string = (char *) calloc(multibyte_max_len, sizeof(char));
    wcsrtombs (padded_multibyte_string, (const wchar_t **) p_wide_string, multibyte_max_len, &state);
    multibyte_string = strdup(padded_multibyte_string);
    free(padded_multibyte_string);
    return multibyte_string;
}