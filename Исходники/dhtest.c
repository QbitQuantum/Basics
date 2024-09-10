int main(int argc, char *argv[])
{
    BN_GENCB _cb;
    DH *a;
    DH *b = NULL;
    char buf[12];
    unsigned char *abuf = NULL, *bbuf = NULL;
    int i, alen, blen, aout, bout, ret = 1;
    BIO *out;

    CRYPTO_malloc_debug_init();
    CRYPTO_dbg_set_options(V_CRYPTO_MDEBUG_ALL);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

# ifdef OPENSSL_SYS_WIN32
    CRYPTO_malloc_init();
# endif

    RAND_seed(rnd_seed, sizeof rnd_seed);

    out = BIO_new(BIO_s_file());
    if (out == NULL)
        EXIT(1);
    BIO_set_fp(out, stdout, BIO_NOCLOSE);

    BN_GENCB_set(&_cb, &cb, out);
    if (((a = DH_new()) == NULL) || !DH_generate_parameters_ex(a, 64,
                                                               DH_GENERATOR_5,
                                                               &_cb))
        goto err;

    if (!DH_check(a, &i))
        goto err;
    if (i & DH_CHECK_P_NOT_PRIME)
        BIO_puts(out, "p value is not prime\n");
    if (i & DH_CHECK_P_NOT_SAFE_PRIME)
        BIO_puts(out, "p value is not a safe prime\n");
    if (i & DH_UNABLE_TO_CHECK_GENERATOR)
        BIO_puts(out, "unable to check the generator value\n");
    if (i & DH_NOT_SUITABLE_GENERATOR)
        BIO_puts(out, "the g value is not a generator\n");

    BIO_puts(out, "\np    =");
    BN_print(out, a->p);
    BIO_puts(out, "\ng    =");
    BN_print(out, a->g);
    BIO_puts(out, "\n");

    b = DH_new();
    if (b == NULL)
        goto err;

    b->p = BN_dup(a->p);
    b->g = BN_dup(a->g);
    if ((b->p == NULL) || (b->g == NULL))
        goto err;

    /* Set a to run with normal modexp and b to use constant time */
    a->flags &= ~DH_FLAG_NO_EXP_CONSTTIME;
    b->flags |= DH_FLAG_NO_EXP_CONSTTIME;

    if (!DH_generate_key(a))
        goto err;
    BIO_puts(out, "pri 1=");
    BN_print(out, a->priv_key);
    BIO_puts(out, "\npub 1=");
    BN_print(out, a->pub_key);
    BIO_puts(out, "\n");

    if (!DH_generate_key(b))
        goto err;
    BIO_puts(out, "pri 2=");
    BN_print(out, b->priv_key);
    BIO_puts(out, "\npub 2=");
    BN_print(out, b->pub_key);
    BIO_puts(out, "\n");

    alen = DH_size(a);
    abuf = (unsigned char *)OPENSSL_malloc(alen);
    aout = DH_compute_key(abuf, b->pub_key, a);

    BIO_puts(out, "key1 =");
    for (i = 0; i < aout; i++) {
        sprintf(buf, "%02X", abuf[i]);
        BIO_puts(out, buf);
    }
    BIO_puts(out, "\n");

    blen = DH_size(b);
    bbuf = (unsigned char *)OPENSSL_malloc(blen);
    bout = DH_compute_key(bbuf, a->pub_key, b);

    BIO_puts(out, "key2 =");
    for (i = 0; i < bout; i++) {
        sprintf(buf, "%02X", bbuf[i]);
        BIO_puts(out, buf);
    }
    BIO_puts(out, "\n");
    if ((aout < 4) || (bout != aout) || (memcmp(abuf, bbuf, aout) != 0)) {
        fprintf(stderr, "Error in DH routines\n");
        ret = 1;
    } else
        ret = 0;
    if (!run_rfc5114_tests())
        ret = 1;
 err:
    ERR_print_errors_fp(stderr);

    if (abuf != NULL)
        OPENSSL_free(abuf);
    if (bbuf != NULL)
        OPENSSL_free(bbuf);
    if (b != NULL)
        DH_free(b);
    if (a != NULL)
        DH_free(a);
    BIO_free(out);
# ifdef OPENSSL_SYS_NETWARE
    if (ret)
        printf("ERROR: %d\n", ret);
# endif
    EXIT(ret);
    return (ret);
}