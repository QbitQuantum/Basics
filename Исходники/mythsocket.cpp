void MythSocket::WriteStringListReal(const QStringList *list, bool *ret)
{
    if (list->empty())
    {
        LOG(VB_GENERAL, LOG_ERR, LOC +
            "WriteStringList: Error, invalid string list.");
        *ret = false;
        return;
    }

    if (m_tcpSocket->state() != QAbstractSocket::ConnectedState)
    {
        LOG(VB_GENERAL, LOG_ERR, LOC +
            "WriteStringList: Error, called with unconnected socket.");
        *ret = false;
        return;
    }

    QString str = list->join("[]:[]");
    if (str.isEmpty())
    {
        LOG(VB_GENERAL, LOG_ERR, LOC +
            "WriteStringList: Error, joined null string.");
        *ret = false;
        return;
    }

    QByteArray utf8 = str.toUtf8();
    int size = utf8.length();
    int written = 0;
    int written_since_timer_restart = 0;

    QByteArray payload;
    payload = payload.setNum(size);
    payload += "        ";
    payload.truncate(8);
    payload += utf8;
    size = payload.length();

    if (VERBOSE_LEVEL_CHECK(VB_NETWORK, LOG_INFO))
    {
        QString msg = QString("write -> %1 %2")
            .arg(m_tcpSocket->socketDescriptor(), 2).arg(payload.data());

        if (logLevel < LOG_DEBUG && msg.length() > 88)
        {
            msg.truncate(85);
            msg += "...";
        }
        LOG(VB_NETWORK, LOG_INFO, LOC + msg);
    }

    MythTimer timer; timer.start();
    unsigned int errorcount = 0;
    while (size > 0)
    {
        if (m_tcpSocket->state() != QAbstractSocket::ConnectedState)
        {
            LOG(VB_GENERAL, LOG_ERR, LOC +
                "WriteStringList: Error, socket went unconnected." +
                QString("\n\t\t\tWe wrote %1 of %2 bytes with %3 errors")
                    .arg(written).arg(written+size).arg(errorcount) +
                    QString("\n\t\t\tstarts with: %1").arg(to_sample(payload)));
            *ret = false;
            return;
        }

        int temp = m_tcpSocket->write(payload.data() + written, size);
        if (temp > 0)
        {
            written += temp;
            written_since_timer_restart += temp;
            size -= temp;
            if ((timer.elapsed() > 500) && written_since_timer_restart != 0)
            {
                timer.restart();
                written_since_timer_restart = 0;
            }
        }
        else if (temp <= 0)
        {
            errorcount++;
            if (timer.elapsed() > 1000)
            {
                LOG(VB_GENERAL, LOG_ERR, LOC + "WriteStringList: Error, " +
                    QString("No data written on write (%1 errors)")
                        .arg(errorcount) +
                    QString("\n\t\t\tstarts with: %1")
                    .arg(to_sample(payload)));
                *ret = false;
                return;
            }
            usleep(1000);
        }
    }

    m_tcpSocket->flush();

    *ret = true;
    return;
}