INT
auth_sspi_client_wrap(sspi_client_state* state,
                      SEC_CHAR* data,
                      SEC_CHAR* user) {
    SECURITY_STATUS status;
    SecPkgContext_Sizes sizes;
    SecBuffer wrapBufs[3];
    SecBufferDesc wrapBufDesc;
    SEC_CHAR* decodedData = NULL;
    SEC_CHAR* inbuf;
    SEC_CHAR* outbuf;
    SIZE_T outbufSize;
    SEC_CHAR* plaintextMessage;
    SIZE_T plaintextMessageSize;

    if (state->response != NULL) {
        free(state->response);
        state->response = NULL;
    }

    if (!state->haveCtx) {
        set_uninitialized_context();
        return AUTH_GSS_ERROR;
    }

    status = QueryContextAttributes(&state->ctx, SECPKG_ATTR_SIZES, &sizes);
    if (status != SEC_E_OK) {
        set_krberror(status, "QueryContextAttributes");
        return AUTH_GSS_ERROR;
    }

    if (user) {
        /* Length of user + 4 bytes for security layer (see below). */
        plaintextMessageSize = strlen(user) + 4;
    } else {
        decodedData = base64_decode(data, &plaintextMessageSize);
    }

    inbuf = (SEC_CHAR*)malloc(
        sizes.cbSecurityTrailer + plaintextMessageSize + sizes.cbBlockSize);
    if (inbuf == NULL) {
        free(decodedData);
        PyErr_SetNone(PyExc_MemoryError);
        return AUTH_GSS_ERROR;
    }

    plaintextMessage = inbuf + sizes.cbSecurityTrailer;
    if (user) {
        /* Authenticate the provided user. Unlike pykerberos, we don't
         * need any information from "data" to do that.
         * */
        plaintextMessage[0] = 1; /* No security layer */
        plaintextMessage[1] = 0;
        plaintextMessage[2] = 0;
        plaintextMessage[3] = 0;
        memcpy(plaintextMessage + 4, user, strlen(user));
    } else {
        /* No user provided. Just rewrap data. */
        memcpy(plaintextMessage, decodedData, plaintextMessageSize);
        free(decodedData);
    }

    wrapBufDesc.cBuffers = 3;
    wrapBufDesc.pBuffers = wrapBufs;
    wrapBufDesc.ulVersion = SECBUFFER_VERSION;

    wrapBufs[0].cbBuffer = sizes.cbSecurityTrailer;
    wrapBufs[0].BufferType = SECBUFFER_TOKEN;
    wrapBufs[0].pvBuffer = inbuf;

    wrapBufs[1].cbBuffer = (ULONG)plaintextMessageSize;
    wrapBufs[1].BufferType = SECBUFFER_DATA;
    wrapBufs[1].pvBuffer = inbuf + sizes.cbSecurityTrailer;

    wrapBufs[2].cbBuffer = sizes.cbBlockSize;
    wrapBufs[2].BufferType = SECBUFFER_PADDING;
    wrapBufs[2].pvBuffer =
        inbuf + (sizes.cbSecurityTrailer + plaintextMessageSize);

    status = EncryptMessage(
        &state->ctx, SECQOP_WRAP_NO_ENCRYPT, &wrapBufDesc, 0);
    if (status != SEC_E_OK) {
        free(inbuf);
        set_krberror(status, "EncryptMessage");
        return AUTH_GSS_ERROR;
    }

    outbufSize =
        wrapBufs[0].cbBuffer + wrapBufs[1].cbBuffer + wrapBufs[2].cbBuffer;
    outbuf = (SEC_CHAR*)malloc(outbufSize);
    if (outbuf == NULL) {
        free(inbuf);
        PyErr_SetNone(PyExc_MemoryError);
        return AUTH_GSS_ERROR;
    }
    memcpy(outbuf, wrapBufs[0].pvBuffer,
           wrapBufs[0].cbBuffer);
    memcpy(outbuf + wrapBufs[0].cbBuffer,
           wrapBufs[1].pvBuffer,
           wrapBufs[1].cbBuffer);
    memcpy(outbuf + wrapBufs[0].cbBuffer + wrapBufs[1].cbBuffer,
           wrapBufs[2].pvBuffer,
           wrapBufs[2].cbBuffer);
    state->response = base64_encode(outbuf, outbufSize);
    free(inbuf);
    free(outbuf);
    return AUTH_GSS_COMPLETE;
}