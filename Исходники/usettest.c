/**
 * Make sure that when non-invariant chars are passed to uset_openPattern
 * they do not cause an ugly failure mode (e.g. assertion failure).
 * JB#3795.
 */
static void
TestNonInvariantPattern() {
    UErrorCode ec = U_ZERO_ERROR;
    /* The critical part of this test is that the following pattern
       must contain a non-invariant character. */
    static const char *pattern = "[:ccc!=0:]";
    UChar buf[256];
    int32_t len = u_unescape(pattern, buf, 256);
    /* This test 'fails' by having an assertion failure within the
       following call.  It passes by running to completion with no
       assertion failure. */
    USet *set = uset_openPattern(buf, len, &ec);
    uset_close(set);
}