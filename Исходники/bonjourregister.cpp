bool BonjourRegister::Register(uint16_t port, const QByteArray &type,
                              const QByteArray &name, const QByteArray &txt)
{
    if (m_dnssref)
    {
        LOG(VB_GENERAL, LOG_WARNING, LOC + "Service already registered.");
        return true;
    }

    m_lock = new QMutexLocker(&g_lock);
    m_data = txt;

    uint16_t qport = qToBigEndian(port);
    DNSServiceErrorType res =
        DNSServiceRegister(&m_dnssref, 0, 0, name.data(), type.data(),
                           nullptr, nullptr, qport, txt.size(), (void*)txt.data(),
                           BonjourCallback, this);

    if (kDNSServiceErr_NoError != res)
    {
        LOG(VB_GENERAL, LOG_ERR, LOC + QString("Error: %1").arg(res));
    }
    else
    {
        int fd = DNSServiceRefSockFD(m_dnssref);
        if (fd != -1)
        {
            m_socket = new QSocketNotifier(fd, QSocketNotifier::Read, this);
            m_socket->setEnabled(true);
            connect(m_socket, SIGNAL(activated(int)),
                    this, SLOT(socketReadyRead()));
            delete m_lock; // would already have been deleted, but just in case
            m_lock = nullptr;
            return true;
        }
    }