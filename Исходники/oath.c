Token *oath_token_from_entry(Token *token, Slapi_Entry *e) {

    if (e != NULL && token != NULL) {

        Slapi_Attr *seed;

        token->serial = slapi_entry_attr_get_charptr(e, "tokenSerial");
        token->pin = slapi_entry_attr_get_charptr(e, "tokenPIN");
        token->counter = slapi_entry_attr_get_long(e, "tokenCounter");

        slapi_entry_attr_find(e, "tokenSeed", &seed);

        if (seed != NULL) {
            struct berval *bval;
            Slapi_Value *sval;
            slapi_attr_first_value(seed, &sval);
            bval = slapi_value_get_berval(sval);
            token->seed = ber_bvdup(bval);
        }

    }

    return token;

}