static int send_chunk(CONCRETE_IO_HANDLE tls_io, const void* buffer, size_t size, ON_SEND_COMPLETE on_send_complete, void* callback_context)
{
    int result;

    if ((tls_io == NULL) ||
        (buffer == NULL) ||
        (size == 0))
    {
        LogError("invalid argument detected: CONCRETE_IO_HANDLE tls_io = %p, const void* buffer = %p, size_t size = %d", tls_io, buffer, size);
        result = __FAILURE__;
    }
    else
    {
        TLS_IO_INSTANCE* tls_io_instance = (TLS_IO_INSTANCE*)tls_io;
        if (tls_io_instance->tlsio_state != TLS_SERVER_IO_STATE_OPEN)
        {
            LogError("invalid tls_io_instance->tlsio_state: %s", ENUM_TO_STRING(TLS_SERVER_IO_STATE, tls_io_instance->tlsio_state));
            result = __FAILURE__;
        }
        else
        {
            SecPkgContext_StreamSizes  sizes;
            SECURITY_STATUS status = QueryContextAttributes(&tls_io_instance->security_context, SECPKG_ATTR_STREAM_SIZES, &sizes);
            if (status != SEC_E_OK)
            {
                LogError("QueryContextAttributes failed: %x", status);
                result = __FAILURE__;
            }
            else
            {
                SecBuffer security_buffers[4];
                SecBufferDesc security_buffers_desc;
                size_t needed_buffer = sizes.cbHeader + size + sizes.cbTrailer;
                unsigned char* out_buffer = (unsigned char*)malloc(needed_buffer);
                if (out_buffer == NULL)
                {
                    LogError("malloc failed");
                    result = __FAILURE__;
                }
                else
                {
                    (void)memcpy(out_buffer + sizes.cbHeader, buffer, size);

                    security_buffers[0].BufferType = SECBUFFER_STREAM_HEADER;
                    security_buffers[0].cbBuffer = sizes.cbHeader;
                    security_buffers[0].pvBuffer = out_buffer;
                    security_buffers[1].BufferType = SECBUFFER_DATA;
                    security_buffers[1].cbBuffer = (unsigned long)size;
                    security_buffers[1].pvBuffer = out_buffer + sizes.cbHeader;
                    security_buffers[2].BufferType = SECBUFFER_STREAM_TRAILER;
                    security_buffers[2].cbBuffer = sizes.cbTrailer;
                    security_buffers[2].pvBuffer = out_buffer + sizes.cbHeader + size;
                    security_buffers[3].cbBuffer = 0;
                    security_buffers[3].BufferType = SECBUFFER_EMPTY;
                    security_buffers[3].pvBuffer = 0;

                    security_buffers_desc.cBuffers = sizeof(security_buffers) / sizeof(security_buffers[0]);
                    security_buffers_desc.pBuffers = security_buffers;
                    security_buffers_desc.ulVersion = SECBUFFER_VERSION;

                    status = EncryptMessage(&tls_io_instance->security_context, 0, &security_buffers_desc, 0);
                    if (FAILED(status))
                    {
                        LogError("EncryptMessage failed: %x", status);
                        result = __FAILURE__;
                    }
                    else
                    {
                        if (xio_send(tls_io_instance->socket_io, out_buffer, security_buffers[0].cbBuffer + security_buffers[1].cbBuffer + security_buffers[2].cbBuffer, on_send_complete, callback_context) != 0)
                        {
                            LogError("xio_send failed");
                            result = __FAILURE__;
                        }
                        else
                        {
                            result = 0;
                        }
                    }

                    free(out_buffer);
                }
            }
        }
    }

    return result;
}