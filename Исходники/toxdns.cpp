QByteArray ToxDNS::fetchLastTextRecord(const QString& record, bool silent)
{
    QByteArray result;

    QDnsLookup dns;
    dns.setType(QDnsLookup::TXT);
    dns.setName(record);
    dns.lookup();

    int timeout;
    for (timeout = 0; timeout<30 && !dns.isFinished(); ++timeout)
    {
        qApp->processEvents();
        QThread::msleep(100);
    }
    if (timeout >= 30)
    {
        dns.abort();
        if (!silent)
            showWarning(tr("The connection timed out","The DNS gives the Tox ID associated to toxme.se addresses"));

        return result;
    }

    if (dns.error() == QDnsLookup::NotFoundError)
    {
        if (!silent)
            showWarning(tr("This address does not exist","The DNS gives the Tox ID associated to toxme.se addresses"));

        return result;
    }
    else if (dns.error() != QDnsLookup::NoError)
    {
        if (!silent)
            showWarning(tr("Error while looking up DNS","The DNS gives the Tox ID associated to toxme.se addresses"));

        return result;
    }

    const QList<QDnsTextRecord> textRecords = dns.textRecords();
    if (textRecords.isEmpty())
    {
        if (!silent)
            showWarning(tr("No text record found", "Error with the DNS"));

        return result;
    }

    const QList<QByteArray> textRecordValues = textRecords.last().values();
    if (textRecordValues.length() != 1)
    {
        if (!silent)
            showWarning(tr("Unexpected number of values in text record", "Error with the DNS"));

        return result;
    }

    result = textRecordValues.first();
    return result;
}