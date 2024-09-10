void PublicService::publishAsync()
{
	K_D;
	if (d->isRunning()) stop();
	TXTRecordRef txt;
	TXTRecordCreate(&txt,0,0);
	QMap<QString,QByteArray>::ConstIterator itEnd = d->m_textData.end();
	for (QMap<QString,QByteArray>::ConstIterator it = d->m_textData.begin(); it!=itEnd ; ++it) {
		if (TXTRecordSetValue(&txt,it.key().toUtf8(),it.value().length(),it.value())!=kDNSServiceErr_NoError) {
			TXTRecordDeallocate(&txt);
			emit published(false);
			return;
		}
	}
	DNSServiceRef ref;
	QString fullType=d->m_type;
	Q_FOREACH(const QString &subtype, d->m_subtypes) fullType+=','+subtype;
	if (DNSServiceRegister(&ref,0,0,d->m_serviceName.toUtf8(),fullType.toAscii().constData(),domainToDNS(d->m_domain),NULL,
	    htons(d->m_port),TXTRecordGetLength(&txt),TXTRecordGetBytesPtr(&txt),publish_callback,
	    reinterpret_cast<void*>(d)) == kDNSServiceErr_NoError) d->setRef(ref);
	TXTRecordDeallocate(&txt);
	if (!d->isRunning()) emit published(false);
}