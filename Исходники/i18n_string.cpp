ERL_NIF_TERM to_title(ErlNifEnv* env, int argc, 
    const ERL_NIF_TERM argv[])
{
    ErlNifBinary in, out;
    int32_t ulen; 
    char locale[LOCALE_LEN];
    const char* locptr;
    cloner* ptr; 
    UBreakIterator* iter; 
    UErrorCode status = U_ZERO_ERROR;

    if (argc != 2)
        return enif_make_badarg(env);

    /* Second argument must be a binary */
    if(!enif_inspect_binary(env, argv[1], &in)) {
        return enif_make_badarg(env);
    }

    if (enif_get_atom(env, argv[0], locale, LOCALE_LEN, ERL_NIF_LATIN1)) {
        /* First element is an atom. */
        locptr = (const char*) locale;
        iter = NULL;

    } else if (enif_get_resource(env, argv[0], iterator_type, (void**) &ptr)) {
        /* First element is an iterator. */
        iter = (UBreakIterator*) cloner_get(ptr);
        CHECK_RES(env, iter);
            

        /* Iterator contains a locale name. Extract it. */
        locptr = ubrk_getLocaleByType((const UBreakIterator*) iter,
            ULOC_ACTUAL_LOCALE, /* locale type */
            &status);

        CHECK(env, status);
    } else {
        return enif_make_badarg(env);
    }  

    ulen = TO_ULEN(in.size);
    do_to_title(in, out, ulen, iter, locptr, status);
    if (status == U_BUFFER_OVERFLOW_ERROR) {
        do_to_title(in, out, ulen, iter, locptr, status);
    }
    CHECK(env, status);
    return enif_make_binary(env, &out);

}