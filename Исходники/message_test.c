/*
 * Test trunc_string().
 */
    static void
test_trunc_string(void)
{
    char_u  *buf; /*allocated every time to find uninit errors */
    char_u  *s;

    /* in place */
    buf = alloc(40);
    STRCPY(buf, "text");
    trunc_string(buf, buf, 20, 40);
    assert(STRCMP(buf, "text") == 0);
    vim_free(buf);

    buf = alloc(40);
    STRCPY(buf, "a short text");
    trunc_string(buf, buf, 20, 40);
    assert(STRCMP(buf, "a short text") == 0);
    vim_free(buf);

    buf = alloc(40);
    STRCPY(buf, "a text tha just fits");
    trunc_string(buf, buf, 20, 40);
    assert(STRCMP(buf, "a text tha just fits") == 0);
    vim_free(buf);

    buf = alloc(40);
    STRCPY(buf, "a text that nott fits");
    trunc_string(buf, buf, 20, 40);
    assert(STRCMP(buf, "a text t...nott fits") == 0);
    vim_free(buf);

    /* copy from string to buf */
    buf = alloc(40);
    s = vim_strsave((char_u *)"text");
    trunc_string(s, buf, 20, 40);
    assert(STRCMP(buf, "text") == 0);
    vim_free(buf);
    vim_free(s);

    buf = alloc(40);
    s = vim_strsave((char_u *)"a text that fits");
    trunc_string(s, buf, 34, 40);
    assert(STRCMP(buf, "a text that fits") == 0);
    vim_free(buf);
    vim_free(s);

    buf = alloc(40);
    s = vim_strsave((char_u *)"a short text");
    trunc_string(s, buf, 20, 40);
    assert(STRCMP(buf, "a short text") == 0);
    vim_free(buf);
    vim_free(s);

    buf = alloc(40);
    s = vim_strsave((char_u *)"a text tha just fits");
    trunc_string(s, buf, 20, 40);
    assert(STRCMP(buf, "a text tha just fits") == 0);
    vim_free(buf);
    vim_free(s);

    buf = alloc(40);
    s = vim_strsave((char_u *)"a text that nott fits");
    trunc_string(s, buf, 20, 40);
    assert(STRCMP(buf, "a text t...nott fits") == 0);
    vim_free(buf);
    vim_free(s);
}