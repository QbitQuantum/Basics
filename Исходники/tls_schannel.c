static int tls_write(URLContext *h, const uint8_t *buf, int len)
{
    TLSContext *c = h->priv_data;
    TLSShared *s = &c->tls_shared;
    SECURITY_STATUS sspi_ret;
    int ret = 0, data_size;
    uint8_t *data = NULL;
    SecBuffer outbuf[4];
    SecBufferDesc outbuf_desc;

    if (c->sizes.cbMaximumMessage == 0) {
        sspi_ret = QueryContextAttributes(&c->ctxt_handle, SECPKG_ATTR_STREAM_SIZES, &c->sizes);
        if (sspi_ret != SEC_E_OK)
            return AVERROR_UNKNOWN;
    }

    /* limit how much data we can consume */
    len = FFMIN(len, c->sizes.cbMaximumMessage);

    data_size = c->sizes.cbHeader + len + c->sizes.cbTrailer;
    data = av_malloc(data_size);
    if (data == NULL)
        return AVERROR(ENOMEM);

    init_sec_buffer(&outbuf[0], SECBUFFER_STREAM_HEADER,
                  data, c->sizes.cbHeader);
    init_sec_buffer(&outbuf[1], SECBUFFER_DATA,
                  data + c->sizes.cbHeader, len);
    init_sec_buffer(&outbuf[2], SECBUFFER_STREAM_TRAILER,
                  data + c->sizes.cbHeader + len,
                  c->sizes.cbTrailer);
    init_sec_buffer(&outbuf[3], SECBUFFER_EMPTY, NULL, 0);
    init_sec_buffer_desc(&outbuf_desc, outbuf, 4);

    memcpy(outbuf[1].pvBuffer, buf, len);

    sspi_ret = EncryptMessage(&c->ctxt_handle, 0, &outbuf_desc, 0);
    if (sspi_ret == SEC_E_OK)  {
        len = outbuf[0].cbBuffer + outbuf[1].cbBuffer + outbuf[2].cbBuffer;
        ret = ffurl_write(s->tcp, data, len);
        if (ret < 0 || ret != len) {
            ret = AVERROR(EIO);
            av_log(h, AV_LOG_ERROR, "Writing encrypted data to socket failed\n");
            goto done;
        }
    } else {
        av_log(h, AV_LOG_ERROR, "Encrypting data failed\n");
        if (sspi_ret == SEC_E_INSUFFICIENT_MEMORY)
            ret = AVERROR(ENOMEM);
        else
            ret = AVERROR(EIO);
        goto done;
    }

done:
    av_freep(&data);
    return ret < 0 ? ret : outbuf[1].cbBuffer;
}