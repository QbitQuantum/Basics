AUTH_RESULT GSSAPISession::authenticate()
{
#ifdef Q_OS_WIN
    SECURITY_STATUS status;
    _inSecBuf.cbBuffer = static_cast<unsigned long>(inBuffer.length());
    _inSecBuf.BufferType = SECBUFFER_TOKEN;
    _inSecBuf.pvBuffer = inBuffer.data();
    _outSecBuf.cbBuffer = _info->cbMaxToken;

    CtxtHandle* contextPtr = &_context;
    if(_first)
    {
        contextPtr = NULL;
        _first = false;
    }
    status = AcceptSecurityContext (
                    &_serverHandle,
                    contextPtr,
                    &_inSecBufDesc,
                    0,
                    SECURITY_NATIVE_DREP,
                    &_context,
                    &_outSecBufDesc,
                    &_attrs,
                    &_serviceLifetime
                    );


    outBuffer = QByteArray((const char *)_outSecBuf.pvBuffer, _outSecBuf.cbBuffer);
    if(status == SEC_I_CONTINUE_NEEDED || status == SEC_I_COMPLETE_AND_CONTINUE) return AUTH_RESULT::CONTINUE;
    if(status == 0)
    {

        status = QuerySecurityContextToken(&_context, &_secToken);
        status  = QueryContextAttributes(&_context, SECPKG_ATTR_NAMES, &_names);
        return AUTH_RESULT::ACCEPTED;
    }

    return AUTH_RESULT::REJECTED;
#endif
#ifdef Q_OS_LINUX
    throw "not implemented";
    return AUTH_RESULT::REJECTED;
#endif
}