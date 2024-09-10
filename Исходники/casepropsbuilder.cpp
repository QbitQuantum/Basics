static int32_t U_CALLCONV
compareUnfold(const void *context, const void *left, const void *right) {
    return u_memcmp((const UChar *)left, (const UChar *)right, UGENCASE_UNFOLD_WIDTH);
}