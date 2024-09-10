void PublicService::publishAsync()
{
    if(d->isRunning())
        stop();
#ifdef HAVE_DNSSD
    if(ServiceBrowser::isAvailable() == ServiceBrowser::Working)
    {
        TXTRecordRef txt;
        TXTRecordCreate(&txt, 0, 0);
        QMap< QString, QString >::ConstIterator itEnd = m_textData.end();
        for(QMap< QString, QString >::ConstIterator it = m_textData.begin(); it != itEnd; ++it)
        {
            QCString value = it.data().utf8();
            if(TXTRecordSetValue(&txt, it.key().utf8(), value.length(), value) != kDNSServiceErr_NoError)
            {
                TXTRecordDeallocate(&txt);
                emit published(false);
                return;
            }
        }
        DNSServiceRef ref;
        if(DNSServiceRegister(&ref, 0, 0, m_serviceName.utf8(), m_type.ascii(), domainToDNS(m_domain), NULL, htons(m_port), TXTRecordGetLength(&txt),
                              TXTRecordGetBytesPtr(&txt), publish_callback, reinterpret_cast< void * >(this))
           == kDNSServiceErr_NoError)
            d->setRef(ref);
        TXTRecordDeallocate(&txt);
    }
#endif
    if(!d->isRunning())
        emit published(false);
}