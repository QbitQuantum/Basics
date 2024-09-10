int main(int argc, char **argv)
{
    BN_GENCB *cb;
    DSA *dsa = NULL;
    int counter, ret = 0, i, j;
    unsigned char buf[256];
    unsigned long h;
    unsigned char sig[256];
    unsigned int siglen;

    if (bio_err == NULL)
        bio_err = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);

    CRYPTO_set_mem_debug(1);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

    RAND_seed(rnd_seed, sizeof rnd_seed);

    BIO_printf(bio_err, "test generation of DSA parameters\n");

    cb = BN_GENCB_new();
    if (!cb)
        goto end;

    BN_GENCB_set(cb, dsa_cb, bio_err);
    if (((dsa = DSA_new()) == NULL) || !DSA_generate_parameters_ex(dsa, 512,
                                                                   seed, 20,
                                                                   &counter,
                                                                   &h, cb))
        goto end;

    BIO_printf(bio_err, "seed\n");
    for (i = 0; i < 20; i += 4) {
        BIO_printf(bio_err, "%02X%02X%02X%02X ",
                   seed[i], seed[i + 1], seed[i + 2], seed[i + 3]);
    }
    BIO_printf(bio_err, "\ncounter=%d h=%ld\n", counter, h);

    DSA_print(bio_err, dsa, 0);
    if (counter != 105) {
        BIO_printf(bio_err, "counter should be 105\n");
        goto end;
    }
    if (h != 2) {
        BIO_printf(bio_err, "h should be 2\n");
        goto end;
    }

    i = BN_bn2bin(dsa->q, buf);
    j = sizeof(out_q);
    if ((i != j) || (memcmp(buf, out_q, i) != 0)) {
        BIO_printf(bio_err, "q value is wrong\n");
        goto end;
    }

    i = BN_bn2bin(dsa->p, buf);
    j = sizeof(out_p);
    if ((i != j) || (memcmp(buf, out_p, i) != 0)) {
        BIO_printf(bio_err, "p value is wrong\n");
        goto end;
    }

    i = BN_bn2bin(dsa->g, buf);
    j = sizeof(out_g);
    if ((i != j) || (memcmp(buf, out_g, i) != 0)) {
        BIO_printf(bio_err, "g value is wrong\n");
        goto end;
    }

    dsa->flags |= DSA_FLAG_NO_EXP_CONSTTIME;
    DSA_generate_key(dsa);
    DSA_sign(0, str1, 20, sig, &siglen, dsa);
    if (DSA_verify(0, str1, 20, sig, siglen, dsa) == 1)
        ret = 1;

    dsa->flags &= ~DSA_FLAG_NO_EXP_CONSTTIME;
    DSA_generate_key(dsa);
    DSA_sign(0, str1, 20, sig, &siglen, dsa);
    if (DSA_verify(0, str1, 20, sig, siglen, dsa) == 1)
        ret = 1;

 end:
    if (!ret)
        ERR_print_errors(bio_err);
    DSA_free(dsa);
    BN_GENCB_free(cb);

#ifndef OPENSSL_NO_CRYPTO_MDEBUG
    if (CRYPTO_mem_leaks(bio_err) <= 0)
        ret = 0;
#endif
    BIO_free(bio_err);
    bio_err = NULL;
    EXIT(!ret);
}