void SslServer::newConnectionPrivate(qintptr descriptor)
{
    QSslSocket *socket = new QSslSocket(this);
    socket->setSocketDescriptor(descriptor);

    if (m_max_connections == 0)
    {
        socket->abort();
        return;
    }

    socket->setProtocol(QSsl::TlsV1_2OrLater);

    socket->addCaCertificate(m_cert);
    socket->setLocalCertificate(m_cert);
    socket->setPrivateKey(m_key);

    //New connection done, set one less available connection
    m_max_connections--;

    QByteArray m_buffer;
    qint32 size = 0;

    m_socket_list.append(socket);
    m_descriptor_hash.insert(socket, descriptor);
    m_socket_hash.insert(descriptor, socket);
    m_buffer_hash.insert(socket, m_buffer);
    m_size_hash.insert(socket, size);

    connect(socket, &QSslSocket::encrypted, this, &SslServer::encrypted);
    connect(socket, &QSslSocket::disconnected, this, &SslServer::disconnectedPrivate);
    connect(socket, static_cast<void(QSslSocket::*)(const QList<QSslError>&)>(&QSslSocket::sslErrors), this, &SslServer::sslErrors);

    m_alive_hash[socket].start();

    socket->startServerEncryption();
}