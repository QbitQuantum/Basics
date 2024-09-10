static int
testCorrupt(const void *opaque)
{
    const struct testCorruptData *data = opaque;
    struct daemonConfig *conf = daemonConfigNew(false);
    int ret = 0;
    int type = VIR_CONF_NONE;
    char *newdata = munge_param(data->filedata,
                                data->params,
                                data->paramnum,
                                &type);
    virErrorPtr err = NULL;

    if (!newdata)
        return -1;

    //VIR_DEBUG("New config [%s]", newdata);

    if (daemonConfigLoadData(conf, data->filename, newdata) != -1) {
        VIR_DEBUG("Did not see a failure");
        ret = -1;
        goto cleanup;
    }

    err = virGetLastError();
    if (!err || !err->message) {
        VIR_DEBUG("No error or message %p", err);
        ret = -1;
        goto cleanup;
    }

#if !WITH_SASL
    if (strstr(err->message, "unsupported auth sasl")) {
        VIR_DEBUG("sasl unsupported, skipping this config");
        goto cleanup;
    }
#endif

    switch (type) {
    case VIR_CONF_LONG:
        if (!strstr(err->message, "invalid type: got string; expected long")) {
            VIR_DEBUG("Wrong error for long: '%s'",
                      err->message);
            ret = -1;
        }
        break;
    case VIR_CONF_STRING:
        if (!strstr(err->message, "invalid type: got long; expected string")) {
            VIR_DEBUG("Wrong error for string: '%s'",
                      err->message);
            ret = -1;
        }
        break;
    case VIR_CONF_LIST:
        if (!strstr(err->message, "must be a string or list of strings")) {
            VIR_DEBUG("Wrong error for list: '%s'",
                      err->message);
            ret = -1;
        }
        break;
    }

cleanup:
    VIR_FREE(newdata);
    daemonConfigFree(conf);
    return ret;
}