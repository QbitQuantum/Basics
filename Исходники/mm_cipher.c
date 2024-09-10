static void mmenc_func(sqlite3_context *db, int argc, sqlite3_value **argv)
{
    mm_cipher_context_t *ctx;
    const UChar *src;
    int32_t src_len;
    char buf[1024];
    char *dst = buf;
    int32_t dst_len;
    UErrorCode status = U_ZERO_ERROR;
    int arg_type;

    // only accept 1 argument.
    if (argc != 1)
        goto error_misuse;

    // encoding BLOB data type is not supported.
    arg_type = sqlite3_value_type(argv[0]);
    if (arg_type == SQLITE_BLOB)
        goto error_misuse;

    // for data types other than TEXT, just return them.
    if (arg_type != SQLITE_TEXT) {
        sqlite3_result_value(db, argv[0]);
        return;
    }

    ctx = (mm_cipher_context_t *) sqlite3_user_data(db);
    src_len = sqlite3_value_bytes16(argv[0]) / 2;
    src = (const UChar *) sqlite3_value_text16(argv[0]);

    // transform input string to BOCU-1 encoding.
    // try stack buffer first, if it doesn't fit, malloc a new buffer.
    dst_len =
        ucnv_fromUChars(ctx->cnv, dst, sizeof(buf), src, src_len, &status);
    if (status == U_BUFFER_OVERFLOW_ERROR) {
        status = U_ZERO_ERROR;
        dst = (char *) sqlite3_malloc(dst_len);
        dst_len =
            ucnv_fromUChars(ctx->cnv, dst, dst_len, src, src_len, &status);
    }
    if (U_FAILURE(status) && status != U_STRING_NOT_TERMINATED_WARNING) {
        sqlite3_mm_set_last_error(
            "Failed transforming text to internal encoding.");
        goto error_error;
    }

    // encrypt transformed BOCU-1 string.
    do_rc4(ctx, dst, dst_len);

    // return
    sqlite3_result_blob(db, dst, dst_len, SQLITE_TRANSIENT);
    if (dst != buf)
        sqlite3_free(dst);
    return;

error_error:
    if (dst != buf)
        sqlite3_free(dst);
    sqlite3_result_error_code(db, SQLITE_ERROR);
    return;

error_misuse:
    if (dst != buf)
        sqlite3_free(dst);
    sqlite3_result_error_code(db, SQLITE_MISUSE);
    return;
}