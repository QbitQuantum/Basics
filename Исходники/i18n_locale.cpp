ERL_NIF_TERM locale_language_tag(ErlNifEnv* env, int argc, 
    const ERL_NIF_TERM argv[])
{
    UErrorCode status = U_ZERO_ERROR;

    int32_t /*value_len,*/     key_len; 
    char    value[LOCALE_LEN], key[LOCALE_LEN];

    if (argc != 1)
        return enif_make_badarg(env);

    key_len = enif_get_atom(env, argv[0], (char*) key, 
                    LOCALE_LEN, ERL_NIF_LATIN1);

    if (!key_len) {
        return enif_make_badarg(env);
    }

    
    /*value_len =*/ uloc_toLanguageTag((const char*) key, /* Locale Id */
        (char *)  value, /* Name */
        (int32_t) LOCALE_LEN,
        FALSE,
        &status);
    CHECK(env, status);

    return enif_make_atom(env, value);
}