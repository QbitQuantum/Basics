static ZZJSON *parse_object(ZZJSON_CONFIG *config) {
    ZZJSON *retval = NULL;
    int c;
    ZZJSON **next = &retval;

    SKIPWS();
    c = GETC();
    if (c != '{') {
        ERROR("object: expected '{'");
        return NULL;
    }

    SKIPWS();
    c = GETC();
    while (c > 0 && c != '}') {
        ZZJSON *zzjson = NULL, *val = NULL;
        char *str;

        UNGETC(c);

        str = parse_string(config);
        if (!str) {
            ERROR("object: expected string");
errout_with_str:
            config->free(str);
            goto errout;
        }

        SKIPWS();
        c = GETC();
        if (c != ':') {
            ERROR("object: expected ':'");
            goto errout_with_str;
        }

        SKIPWS();
        val = parse_value(config);
        if (!val) {
            ERROR("object: value expected");
            goto errout_with_str;
        }

        SKIPWS();
        c = GETC();
        if (c != ',' && c != '}') {
            ERROR("object: expected ',' or '}'");
errout_with_str_and_val:
            zzjson_free(config, val);
            goto errout_with_str;
        }
        if (c == ',') {
            SKIPWS();
            c = GETC();
            if (c == '}' && !ALLOW_EXTRA_COMMA) {
                ERROR("object: expected pair after ','");
                goto errout_with_str_and_val;
            }
        }
        UNGETC(c);

        zzjson = config->calloc(1, sizeof(ZZJSON));
        if (!zzjson) {
            MEMERROR();
            goto errout_with_str_and_val;
        }
        zzjson->type                = ZZJSON_OBJECT;
        zzjson->value.object.label  = str;
        zzjson->value.object.val    = val;
        *next = zzjson;
        next = &zzjson->next;

        c = GETC();
    }

    if (c != '}') {
        ERROR("object: expected '}'");
        goto errout;
    }

    if (!retval) {  /* empty object, { } */
        retval = config->calloc(1, sizeof(ZZJSON));
        if (!retval) {
            MEMERROR();
            return NULL;
        }
        retval->type = ZZJSON_OBJECT;
    }
            
    return retval;

errout:
    zzjson_free(config, retval);
    return NULL;
}