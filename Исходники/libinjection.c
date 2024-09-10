static
ib_status_t sqli_normalize_tfn(
    ib_mm_t            mm,
    const ib_field_t  *field_in,
    const ib_field_t **field_out,
    void              *instdata,
    void              *tfn_data
)
{
    assert(field_in  != NULL);
    assert(field_out != NULL);

    const sqli_fingerprint_set_t *ps = (const sqli_fingerprint_set_t *)tfn_data;
    sfilter                   sf;
    ib_bytestr_t             *bs_in;
    ib_bytestr_t             *bs_out;
    const char               *buf_in;
    char                     *buf_in_start;
    size_t                    buf_in_len;
    char                     *buf_out;
    char                     *buf_out_end;
    size_t                    buf_out_len;
    size_t                    lead_len = 0;
    char                      prev_token_type;
    ib_field_t               *field_new;
    ib_status_t               rc;
    size_t                    fingerprint_len;

    /* Currently only bytestring types are supported.
     * Other types will just get passed through. */
    if (field_in->type != IB_FTYPE_BYTESTR) {
        *field_out = field_in;
        return IB_OK;
    }

    /* Extract the underlying incoming value. */
    rc = ib_field_value(field_in, ib_ftype_bytestr_mutable_out(&bs_in));
    if (rc != IB_OK) {
        return rc;
    }
    if (ib_bytestr_length(bs_in) == 0) {
        *field_out = field_in;
        return IB_OK;
    }

    /* Create a buffer big enough (double) to allow for normalization. */
    buf_in = (const char *)ib_bytestr_const_ptr(bs_in);
    buf_out = buf_out_end = (char *)ib_mm_calloc(mm, 2, ib_bytestr_length(bs_in));
    if (buf_out == NULL) {
        return IB_EALLOC;
    }

/* TODO: With the latest libinjection, we will need to do something like the
 * following, but more robust, instead of just calling is_sqli. This seems
 * to be because folding is now called, which removes some tokens.
 */
#if 0
    /* As SQL can be injected into a string, the normalization
     * needs to start after the first quote character if one
     * exists.
     *
     * First try single quote, then double, then none.
     *
     * TODO: Handle returning multiple transformations:
     *       1) Straight normalization
     *       2) Normalization as if with single quotes (starting point
     *          should be based on straight normalization)
     *       3) Normalization as if with double quotes (starting point
     *          should be based on straight normalization)
     */
    buf_in_start = memchr(buf_in, CHAR_SINGLE, ib_bytestr_length(bs_in));
    if (buf_in_start == NULL) {
        buf_in_start = memchr(buf_in, CHAR_DOUBLE, ib_bytestr_length(bs_in));
    }
    if (buf_in_start == NULL) {
        buf_in_start = (char *)buf_in;
        buf_in_len = ib_bytestr_length(bs_in);
    }
    else {
        ++buf_in_start; /* After the quote. */
        buf_in_len = ib_bytestr_length(bs_in) - (buf_in_start - buf_in);
    }

    /* Copy the leading string if one exists. */
    if (buf_in_start != buf_in) {
        lead_len = buf_in_start - buf_in;
        memcpy(buf_out, buf_in, lead_len);
        buf_out_end += lead_len;
    }
#endif
    buf_in_start = (char *)buf_in;
    buf_in_len = ib_bytestr_length(bs_in);

    /* Copy the normalized tokens as a space separated list. Since
     * the tokenizer does not backtrack, and the normalized values
     * are always equal to or less than the original length, the
     * tokens are written back to the beginning of the original
     * buffer.
     */
    libinjection_sqli_init(&sf,buf_in_start, buf_in_len, FLAG_NONE);
    libinjection_sqli_callback(&sf, sqli_lookup_word, (void *)ps);

    /* NOTE: We do not care if it is sqli, but just want the tokens. */
    libinjection_is_sqli(&sf);

    if (strlen(sf.fingerprint) == 0) {
        *field_out = field_in;
        return IB_OK;
    }

    buf_out_len = 0;
    prev_token_type = 0;
    fingerprint_len = strlen(sf.fingerprint);
    for (size_t i = 0; i < fingerprint_len; ++i) {
        stoken_t current = sf.tokenvec[i];
        size_t token_len = strlen(current.val);

        /* Add in the space if required. */
        if ((buf_out_end != buf_out) &&
            (current.type != 'o') &&
            (prev_token_type != 'o') &&
            (current.type != ',') &&
            (*(buf_out_end - 1) != ','))
        {
            *buf_out_end = ' ';
            buf_out_end += 1;
            ++buf_out_len;
        }

        /* Copy the token value. */
        memcpy(buf_out_end, current.val, token_len);
        buf_out_end += token_len;
        buf_out_len += token_len;

        prev_token_type = current.type;
    }


    /* Create the output field wrapping bs_out. */
    buf_out_len += lead_len;
    rc = ib_bytestr_alias_mem(&bs_out, mm, (uint8_t *)buf_out, buf_out_len);
    if (rc != IB_OK) {
        return rc;
    }
    rc = ib_field_create(&field_new, mm,
                         field_in->name, field_in->nlen,
                         IB_FTYPE_BYTESTR,
                         ib_ftype_bytestr_mutable_in(bs_out));
    if (rc == IB_OK) {
        *field_out = field_new;
    }
    return rc;
}