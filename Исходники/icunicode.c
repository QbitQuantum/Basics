/*
 * call-seq:
 * string.transliterate(transform_string) -> string
 *
 * Transliterates string using transform.
 *
 */
static VALUE unicode_transliterate(int argc, VALUE *argv, VALUE string) {
    UChar str[BUF_SIZE];
    int32_t slen = 0;
    UErrorCode status = U_ZERO_ERROR;
    UTransliterator *trans;
    VALUE transform;

    rb_scan_args(argc, argv, "01", &transform);
    if (NIL_P(transform)) transform = rb_str_new2("Latin; Lower; NFD; [^[:letter:] [:space:] [0-9] [:punctuation:]] Remove; NFC");

    to_utf16(string, str, &slen);

    trans = get_trans(transform);
    utrans_transUChars(trans, str, &slen, BUF_SIZE, 0, &slen, &status);

    to_utf8(str, slen);
}