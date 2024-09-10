struct berval *create_key_control(struct keys_container *keys,
                                  const char *principalName)
{
    struct krb_key_salt *ksdata;
    struct berval *bval;
    BerElement *be;
    int ret, i;

    be = ber_alloc_t(LBER_USE_DER);
    if (!be) {
        return NULL;
    }

    ret = ber_printf(be, "{s{", principalName);
    if (ret == -1) {
        ber_free(be, 1);
        return NULL;
    }

    ksdata = keys->ksdata;
    for (i = 0; i < keys->nkeys; i++) {

        /* we set only the EncryptionKey and salt, no s2kparams */

        ret = ber_printf(be, "{t[{t[i]t[o]}]",
                 (ber_tag_t)(LBER_CONSTRUCTED | LBER_CLASS_CONTEXT | 0),
                 (ber_tag_t)(LBER_CONSTRUCTED | LBER_CLASS_CONTEXT | 0),
                 (ber_int_t)ksdata[i].enctype,
                 (ber_tag_t)(LBER_CONSTRUCTED | LBER_CLASS_CONTEXT | 1),
                 (char *)ksdata[i].key.contents, (ber_len_t)ksdata[i].key.length);

        if (ret == -1) {
            ber_free(be, 1);
            return NULL;
        }

        if (ksdata[i].salttype == NO_SALT) {
            ret = ber_printf(be, "}");
            continue;
        }

        /* we have to pass a salt structure */
        ret = ber_printf(be, "t[{t[i]t[o]}]}",
                 (ber_tag_t)(LBER_CONSTRUCTED | LBER_CLASS_CONTEXT | 1),
                 (ber_tag_t)(LBER_CONSTRUCTED | LBER_CLASS_CONTEXT | 0),
                 (ber_int_t)ksdata[i].salttype,
                 (ber_tag_t)(LBER_CONSTRUCTED | LBER_CLASS_CONTEXT | 1),
                 (char *)ksdata[i].salt.data, (ber_len_t)ksdata[i].salt.length);

        if (ret == -1) {
            ber_free(be, 1);
            return NULL;
        }
    }

    ret = ber_printf(be, "}}");
    if (ret == -1) {
        ber_free(be, 1);
        return NULL;
    }

    ret = ber_flatten(be, &bval);
    if (ret == -1) {
        ber_free(be, 1);
        return NULL;
    }

    ber_free(be, 1);
    return bval;
}