ERL_NIF_TERM trans_ids(ErlNifEnv* env, int argc, 
    const ERL_NIF_TERM /*argv*/[])
{
    ERL_NIF_TERM out;
    UEnumeration* en; 
    UErrorCode status = U_ZERO_ERROR;

    if (argc != 0)
        return enif_make_badarg(env);

    en = utrans_openIDs(&status);   
    CHECK(env, status);

    out = enum_to_term(env, en);
    uenum_close(en);

    return out;
}