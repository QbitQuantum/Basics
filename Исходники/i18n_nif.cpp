static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info)
{
    static int is_loaded = 0;
    int code;

    if (is_loaded)
        return 0;

    uloc_getDefault();

    code = i18n_atom_load(env, priv_data, load_info);
    if (code) return code;

#if I18N_STRING
    code = i18n_string_load(env, priv_data, load_info);
    if (code) return code;
#endif


#if I18N_COLLATION
    code = i18n_collation_load(env, priv_data, load_info);
    if (code) return code;
#endif


#if I18N_COLLATION
    code = i18n_search_load(env, priv_data, load_info);
    if (code) return code;
#endif


#if I18N_MESSAGE
    code = i18n_message_load(env, priv_data, load_info);
    if (code) return code;
#endif


#if I18N_REGEX
    code = i18n_regex_load(env, priv_data, load_info);
    if (code) return code;
#endif


#if I18N_DATE
    code = i18n_date_load(env, priv_data, load_info);
    if (code) return code;
#endif


#if I18N_TRANS
    code = i18n_trans_load(env, priv_data, load_info);
    if (code) return code;
#endif
     
    is_loaded = 1;
     
    return 0;
}