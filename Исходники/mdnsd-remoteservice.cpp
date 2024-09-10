void RemoteService::resolveAsync()
{
	K_D;
	if (d->isRunning()) return;
	d->m_resolved = false;
	kDebug() << this << ":Starting resolve of : " << d->m_serviceName << " " << d->m_type << " " << d->m_domain << "\n";
	DNSServiceRef ref;
	if (DNSServiceResolve(&ref,0,0,d->m_serviceName.toUtf8(), d->m_type.toAscii().constData(), 
 		domainToDNS(d->m_domain),(DNSServiceResolveReply)resolve_callback,reinterpret_cast<void*>(d))
		== kDNSServiceErr_NoError) d->setRef(ref);
	if (!d->isRunning()) emit resolved(false);
}