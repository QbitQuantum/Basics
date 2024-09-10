void
SipRegistrar::addValidDomain(const UtlString& host, int port)
{
   UtlString* valid = new UtlString(host);
   valid->toLower();

   char explicitPort[20];
   sprintf(explicitPort,":%d", PORT_NONE==port ? SIP_PORT : port );
   valid->append(explicitPort);

   Os::Logger::instance().log(FAC_AUTH, PRI_DEBUG, "SipRegistrar::addValidDomain(%s)",valid->data()) ;

   mValidDomains.insert(valid);
}