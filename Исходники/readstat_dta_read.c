static readstat_error_t dta_handle_rows(dta_ctx_t *ctx) {
    readstat_io_t *io = ctx->io;
    char *buf = NULL;
    char  str_buf[2048];
    int i;
    readstat_error_t retval = READSTAT_OK;

    if ((buf = malloc(ctx->record_len)) == NULL) {
        retval = READSTAT_ERROR_MALLOC;
        goto cleanup;
    }

    for (i=0; i<ctx->row_limit; i++) {
        if (io->read(buf, ctx->record_len, io->io_ctx) != ctx->record_len) {
            retval = READSTAT_ERROR_READ;
            goto cleanup;
        }
        int j;
        off_t offset = 0;
        for (j=0; j<ctx->nvar; j++) {
            size_t max_len;
            readstat_value_t value;
            memset(&value, 0, sizeof(readstat_value_t));

            value.type = dta_type_info(ctx->typlist[j], &max_len, ctx);

            if (value.type == READSTAT_TYPE_STRING) {
                readstat_convert(str_buf, sizeof(str_buf), &buf[offset], max_len, ctx->converter);
                value.v.string_value = str_buf;
            } else if (value.type == READSTAT_TYPE_STRING_REF) {
                dta_strl_t key;
                dta_interpret_strl_vo_bytes(ctx, (unsigned char *)&buf[offset], &key);

                dta_strl_t **found = bsearch(&key, ctx->strls, ctx->strls_count, sizeof(dta_strl_t *), &dta_compare_strls);

                if (found) {
                    value.v.string_value = (*found)->data;
                }
                value.type = READSTAT_TYPE_STRING;
            } else if (value.type == READSTAT_TYPE_INT8) {
                int8_t byte = buf[offset];
                if (ctx->machine_is_twos_complement) {
                    byte = ones_to_twos_complement1(byte);
                }
                if (byte > ctx->max_int8) {
                    if (ctx->supports_tagged_missing && byte > DTA_113_MISSING_INT8) {
                        value.tag = 'a' + (byte - DTA_113_MISSING_INT8_A);
                        value.is_tagged_missing = 1;
                    } else {
                        value.is_system_missing = 1;
                    }
                }
                value.v.i8_value = byte;
            } else if (value.type == READSTAT_TYPE_INT16) {
                int16_t num = *((int16_t *)&buf[offset]);
                if (ctx->machine_needs_byte_swap) {
                    num = byteswap2(num);
                }
                if (ctx->machine_is_twos_complement) {
                    num = ones_to_twos_complement2(num);
                }
                if (num > ctx->max_int16) {
                    if (ctx->supports_tagged_missing && num > DTA_113_MISSING_INT16) {
                        value.tag = 'a' + (num - DTA_113_MISSING_INT16_A);
                        value.is_tagged_missing = 1;
                    } else {
                        value.is_system_missing = 1;
                    }
                }
                value.v.i16_value = num;
            } else if (value.type == READSTAT_TYPE_INT32) {
                int32_t num = *((int32_t *)&buf[offset]);
                if (ctx->machine_needs_byte_swap) {
                    num = byteswap4(num);
                }
                if (ctx->machine_is_twos_complement) {
                    num = ones_to_twos_complement4(num);
                }
                if (num > ctx->max_int32) {
                    if (ctx->supports_tagged_missing && num > DTA_113_MISSING_INT32) {
                        value.tag = 'a' + (num - DTA_113_MISSING_INT32_A);
                        value.is_tagged_missing = 1;
                    } else {
                        value.is_system_missing = 1;
                    }
                }
                value.v.i32_value = num;
            } else if (value.type == READSTAT_TYPE_FLOAT) {
                int32_t num = *((int32_t *)&buf[offset]);
                float f_num = NAN;
                if (ctx->machine_needs_byte_swap) {
                    num = byteswap4(num);
                }
                if (num > ctx->max_float) {
                    if (ctx->supports_tagged_missing && num > DTA_113_MISSING_FLOAT) {
                        value.tag = 'a' + ((num - DTA_113_MISSING_FLOAT_A) >> 11);
                        value.is_tagged_missing = 1;
                    } else {
                        value.is_system_missing = 1;
                    }
                } else {