int main(int argc, char *argv[])
{
# ifndef OPENSSL_NO_MD5
    int i;
    char *p;
# endif
    int err = 0;
    HMAC_CTX ctx, ctx2;
    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

# ifdef OPENSSL_NO_MD5
    printf("test skipped: MD5 disabled\n");
# else

#  ifdef CHARSET_EBCDIC
    ebcdic2ascii(test[0].data, test[0].data, test[0].data_len);
    ebcdic2ascii(test[1].data, test[1].data, test[1].data_len);
    ebcdic2ascii(test[2].key, test[2].key, test[2].key_len);
    ebcdic2ascii(test[2].data, test[2].data, test[2].data_len);
#  endif

    for (i = 0; i < 4; i++) {
        p = pt(HMAC(EVP_md5(),
                    test[i].key, test[i].key_len,
                    test[i].data, test[i].data_len, NULL, NULL),
                    MD5_DIGEST_LENGTH);

        if (strcmp(p, (const char *)test[i].digest) != 0) {
            printf("Error calculating HMAC on %d entry'\n", i);
            printf("got %s instead of %s\n", p, test[i].digest);
            err++;
        } else
            printf("test %d ok\n", i);
    }
# endif                         /* OPENSSL_NO_MD5 */

/* test4 */
    HMAC_CTX_init(&ctx);
    if (HMAC_Init_ex(&ctx, NULL, 0, NULL, NULL)) {
        printf("Should fail to initialise HMAC with empty MD and key (test 4)\n");
        err++;
        goto test5;
    }
    if (HMAC_Update(&ctx, test[4].data, test[4].data_len)) {
        printf("Should fail HMAC_Update with ctx not set up (test 4)\n");
        err++;
        goto test5;
    }
    if (HMAC_Init_ex(&ctx, NULL, 0, EVP_sha1(), NULL)) {
        printf("Should fail to initialise HMAC with empty key (test 4)\n");
        err++;
        goto test5;
    }
    if (HMAC_Update(&ctx, test[4].data, test[4].data_len)) {
        printf("Should fail HMAC_Update with ctx not set up (test 4)\n");
        err++;
        goto test5;
    }
    printf("test 4 ok\n");
test5:
    HMAC_CTX_cleanup(&ctx);
    HMAC_CTX_init(&ctx);
    if (HMAC_Init_ex(&ctx, test[4].key, test[4].key_len, NULL, NULL)) {
        printf("Should fail to initialise HMAC with empty MD (test 5)\n");
        err++;
        goto test6;
    }
    if (HMAC_Update(&ctx, test[4].data, test[4].data_len)) {
        printf("Should fail HMAC_Update with ctx not set up (test 5)\n");
        err++;
        goto test6;
    }
    if (HMAC_Init_ex(&ctx, test[4].key, -1, EVP_sha1(), NULL)) {
        printf("Should fail to initialise HMAC with invalid key len(test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Init_ex(&ctx, test[4].key, test[4].key_len, EVP_sha1(), NULL)) {
        printf("Failed to initialise HMAC (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Update(&ctx, test[4].data, test[4].data_len)) {
        printf("Error updating HMAC with data (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Final(&ctx, buf, &len)) {
        printf("Error finalising data (test 5)\n");
        err++;
        goto test6;
    }
    p = pt(buf, len);
    if (strcmp(p, (const char *)test[4].digest) != 0) {
        printf("Error calculating interim HMAC on test 5\n");
        printf("got %s instead of %s\n", p, test[4].digest);
        err++;
        goto test6;
    }
    if (HMAC_Init_ex(&ctx, NULL, 0, EVP_sha256(), NULL)) {
        printf("Should disallow changing MD without a new key (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Init_ex(&ctx, test[4].key, test[4].key_len, EVP_sha256(), NULL)) {
        printf("Failed to reinitialise HMAC (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Update(&ctx, test[5].data, test[5].data_len)) {
        printf("Error updating HMAC with data (sha256) (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Final(&ctx, buf, &len)) {
        printf("Error finalising data (sha256) (test 5)\n");
        err++;
        goto test6;
    }
    p = pt(buf, len);
    if (strcmp(p, (const char *)test[5].digest) != 0) {
        printf("Error calculating 2nd interim HMAC on test 5\n");
        printf("got %s instead of %s\n", p, test[5].digest);
        err++;
        goto test6;
    }
    if (!HMAC_Init_ex(&ctx, test[6].key, test[6].key_len, NULL, NULL)) {
        printf("Failed to reinitialise HMAC with key (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Update(&ctx, test[6].data, test[6].data_len)) {
        printf("Error updating HMAC with data (new key) (test 5)\n");
        err++;
        goto test6;
    }
    if (!HMAC_Final(&ctx, buf, &len)) {
        printf("Error finalising data (new key) (test 5)\n");
        err++;
        goto test6;
    }
    p = pt(buf, len);
    if (strcmp(p, (const char *)test[6].digest) != 0) {
        printf("error calculating HMAC on test 5\n");
        printf("got %s instead of %s\n", p, test[6].digest);
        err++;
    } else {
        printf("test 5 ok\n");
    }
test6:
    HMAC_CTX_cleanup(&ctx);
    HMAC_CTX_init(&ctx);
    if (!HMAC_Init_ex(&ctx, test[7].key, test[7].key_len, EVP_sha1(), NULL)) {
        printf("Failed to initialise HMAC (test 6)\n");
        err++;
        goto end;
    }
    if (!HMAC_Update(&ctx, test[7].data, test[7].data_len)) {
        printf("Error updating HMAC with data (test 6)\n");
        err++;
        goto end;
    }
    if (!HMAC_CTX_copy(&ctx2, &ctx)) {
        printf("Failed to copy HMAC_CTX (test 6)\n");
        err++;
        goto end;
    }
    if (!HMAC_Final(&ctx2, buf, &len)) {
        printf("Error finalising data (test 6)\n");
        err++;
        goto end;
    }
    p = pt(buf, len);
    if (strcmp(p, (const char *)test[7].digest) != 0) {
        printf("Error calculating HMAC on test 6\n");
        printf("got %s instead of %s\n", p, test[7].digest);
        err++;
    } else {
        printf("test 6 ok\n");
    }
end:
    HMAC_CTX_cleanup(&ctx);
    EXIT(err);
    return (0);
}