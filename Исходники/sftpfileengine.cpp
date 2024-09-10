bool SFtpFileEngine::sftpConnect()
{
    SFtpConnectionCache* cache = SFtpConnectionCache::getInstance();

    const SFtpConnectionCache::SFtpConnection *conn =
            cache->findConnection(_url);

    if (conn)
    {
        _sock = conn->sock;
        _session = conn->session;
        _sftp_session = conn->sftp_session;

        return true;
    }

    struct hostent *host;

    host = gethostbyname(_url.host().toLocal8Bit().constData());
    if (!host)
        return false;

    _sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(_port);
    sin.sin_addr.s_addr = *reinterpret_cast<u_long *>(host->h_addr);
    if (::connect(_sock, reinterpret_cast<struct sockaddr *>(&sin),
                  sizeof(struct sockaddr_in)) != 0)
    {
        closesocket(_sock);

        return false;
    }

    _session = libssh2_session_init();
    if(!_session)
    {
        closesocket(_sock);

        return false;
    }

    libssh2_session_set_blocking(_session, 1);

    if (libssh2_session_handshake(_session, _sock))
    {
        libssh2_session_free(_session);
        closesocket(_sock);

        return false;
    }

    if (libssh2_userauth_password(_session,
                                  _textCodec->fromUnicode(_userName).data(),
                                  _textCodec->fromUnicode(_password).data()))
    {
        libssh2_session_disconnect(_session, "Abnormal Shutdown");
        libssh2_session_free(_session);
        closesocket(_sock);

        return false;
    }

    _sftp_session = libssh2_sftp_init(_session);
    if (!_sftp_session)
    {
        libssh2_session_disconnect(_session, "Abnormal Shutdown");
        libssh2_session_free(_session);
        closesocket(_sock);


        return false;
    }

    libssh2_session_set_blocking(_session, 1);
    libssh2_session_set_timeout(_session, 30 * 1000);

    cache->addConnection(_url, _sock, _session, _sftp_session);

    return true;
}