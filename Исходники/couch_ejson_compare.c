int
compare_strings(couch_ejson_ctx_t* ctx, ErlNifBinary a, ErlNifBinary b)
{
    UErrorCode status = U_ZERO_ERROR;
    UCharIterator iterA, iterB;
    int result;

    uiter_setUTF8(&iterA, (const char *) a.data, (uint32_t) a.size);
    uiter_setUTF8(&iterB, (const char *) b.data, (uint32_t) b.size);

    reserve_coll(ctx);
    result = ucol_strcollIter(ctx->coll, &iterA, &iterB, &status);

    if (U_FAILURE(status)) {
        ctx->error = 1;
        return 0;
    }

    /* ucol_strcollIter returns 0, -1 or 1
     * (see type UCollationResult in unicode/ucol.h) */

    return result;
}