static int processSolicited(RilClientPrv *prv, Parcel &p) {
    int32_t token, err, len;
    status_t status;
    const void *data = NULL;
    RilOnComplete req_func = NULL;
    int ret = RIL_CLIENT_ERR_SUCCESS;
    uint32_t req_id = 0;

    if (DBG) ALOGD("%s()", __FUNCTION__);

    status = p.readInt32(&token);
    if (status != NO_ERROR) {
        ALOGE("%s: Read token fail. Status %d\n", __FUNCTION__, status);
        return RIL_CLIENT_ERR_IO;
    }

    if (IsValidToken(&(prv->token_pool), token) == 0) {
        ALOGE("%s: Invalid Token", __FUNCTION__);
        return RIL_CLIENT_ERR_INVAL;    // Invalid token.
    }

    status = p.readInt32(&err);
    if (status != NO_ERROR) {
        ALOGE("%s: Read err fail. Status %d\n", __FUNCTION__, status);
        ret = RIL_CLIENT_ERR_IO;
        goto error;
    }

    // Don't go further for error response.
    if (err != RIL_CLIENT_ERR_SUCCESS) {
        ALOGE("%s: Error %d\n", __FUNCTION__, err);
        if (prv->err_cb)
            prv->err_cb(prv->err_cb_data, err);
        ret = RIL_CLIENT_ERR_SUCCESS;
        goto error;
    }

    status = p.readInt32(&len);
    if (status != NO_ERROR) {
        /* no length field */
        len = 0;
    }

    if (len)
        data = p.readInplace(len);

    // Find request handler for the token.
    // First, FindReqHandler() searches request history with the token
    // and finds out a request ID. Then, it search request handler table
    // with the request ID.
    req_func = FindReqHandler(prv, token, &req_id);
    if (req_func)
    {
        if (DBG) ALOGD("[*] Call handler");
        req_func(prv->parent, data, len);

        if(prv->b_del_handler) {
         prv->b_del_handler = 0;
            RegisterRequestCompleteHandler(prv->parent, req_id, NULL);
        }
    } else {
        if (DBG) ALOGD("%s: No handler for token %d\n", __FUNCTION__, token);
    }

error:
    FreeToken(&(prv->token_pool), token);
    ClearReqHistory(prv, token);
    return ret;
}