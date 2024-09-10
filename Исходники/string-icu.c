//ret_icu_str must be freed after usage
int
icu_str_from_utf8(const char *utf_str,
    UChar **ret_icu_str,
    UErrorCode *ret_icu_err)
{
    int32_t icu_sz;

    SOL_NULL_CHECK(ret_icu_str, -EINVAL);
    SOL_NULL_CHECK(ret_icu_err, -EINVAL);

    icu_sz = 0;
    *ret_icu_str = NULL;
    *ret_icu_err = U_ZERO_ERROR;
    u_strFromUTF8(NULL, 0, &icu_sz, utf_str, -1, ret_icu_err);
    if (U_FAILURE(*ret_icu_err) && *ret_icu_err != U_BUFFER_OVERFLOW_ERROR)
        return -EINVAL;

    *ret_icu_str = calloc(icu_sz + 1, sizeof(UChar));
    SOL_NULL_CHECK(*ret_icu_str, -ENOMEM);

    *ret_icu_err = U_ZERO_ERROR;
    u_strFromUTF8(*ret_icu_str, icu_sz + 1, NULL, utf_str, -1,
        ret_icu_err);
    if (U_FAILURE(*ret_icu_err)) {
        free(*ret_icu_str);
        *ret_icu_str = NULL;
        return -EINVAL;
    }

    return 0;
}