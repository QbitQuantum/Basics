int ipapwd_get_cur_kvno(Slapi_Entry *target)
{
    Slapi_Attr *krbPrincipalKey = NULL;
    Slapi_ValueSet *svs;
    Slapi_Value *sv;
    BerElement *be = NULL;
    const struct berval *cbval;
    ber_tag_t tag, tmp;
    ber_int_t tkvno;
    int hint;
    int kvno;
    int ret;

    /* retrieve current kvno and and keys */
    ret = slapi_entry_attr_find(target, "krbPrincipalKey", &krbPrincipalKey);
    if (ret != 0) {
        return 0;
    }

    kvno = 0;

    slapi_attr_get_valueset(krbPrincipalKey, &svs);
    hint = slapi_valueset_first_value(svs, &sv);
    while (hint != -1) {
        cbval = slapi_value_get_berval(sv);
        if (!cbval) {
            LOG_TRACE("Error retrieving berval from Slapi_Value\n");
            goto next;
        }
        be = ber_init(discard_const(cbval));
        if (!be) {
            LOG_TRACE("ber_init() failed!\n");
            goto next;
        }

        tag = ber_scanf(be, "{xxt[i]", &tmp, &tkvno);
        if (tag == LBER_ERROR) {
            LOG_TRACE("Bad OLD key encoding ?!\n");
            ber_free(be, 1);
            goto next;
        }

        if (tkvno > kvno) {
            kvno = tkvno;
        }

        ber_free(be, 1);
next:
        hint = slapi_valueset_next_value(svs, hint, &sv);
    }

    return kvno;
}