static int has_invalid_null_termination(const ErlNifBinary *path) {
    const WCHAR *null_pos, *end_pos;

    null_pos = wmemchr((const WCHAR*)path->data, L'\0', path->size);
    end_pos = (const WCHAR*)&path->data[path->size] - 1;

    if(null_pos == NULL) {
        return 1;
    }

    /* prim_file:internal_name2native sometimes feeds us data that is "doubly"
     * NUL-terminated, so we'll accept any number of trailing NULs so long as
     * they aren't interrupted by anything else. */
    while(null_pos < end_pos && (*null_pos) == L'\0') {
        null_pos++;
    }

    return null_pos != end_pos;
}