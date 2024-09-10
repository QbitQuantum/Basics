//methods to implement for concrete implementations
bool CZeroconfWIN::doPublishService(const std::string& fcr_identifier,
                      const std::string& fcr_type,
                      const std::string& fcr_name,
                      unsigned int f_port,
                      std::map<std::string, std::string> txt)
{
  DNSServiceRef netService = NULL;
  TXTRecordRef txtRecord;
  TXTRecordCreate(&txtRecord, 0, NULL);

  CLog::Log(LOGDEBUG, __FUNCTION__ " identifier: %s type: %s name:%s port:%i", fcr_identifier.c_str(), fcr_type.c_str(), fcr_name.c_str(), f_port);

  //add txt records
  if(!txt.empty())
  {
    for(std::map<std::string, std::string>::const_iterator it = txt.begin(); it != txt.end(); ++it)
    {
      CLog::Log(LOGDEBUG, "ZeroconfWIN: key:%s, value:%s",it->first.c_str(),it->second.c_str());
      uint8_t txtLen = (uint8_t)strlen(it->second.c_str());
      TXTRecordSetValue(&txtRecord, it->first.c_str(), txtLen, it->second.c_str());
    }
  }

  DNSServiceErrorType err = DNSServiceRegister(&netService, 0, 0, fcr_name.c_str(), fcr_type.c_str(), NULL, NULL, htons(f_port), TXTRecordGetLength(&txtRecord), TXTRecordGetBytesPtr(&txtRecord), registerCallback, NULL);
  
  if (err != kDNSServiceErr_NoError)
  {
    // Something went wrong so lets clean up.
    if (netService)
      DNSServiceRefDeallocate(netService);

    CLog::Log(LOGERROR, __FUNCTION__ " DNSServiceRegister returned (error = %ld)", (int) err);
  } 
  else
  {
    err = DNSServiceProcessResult(netService);

    if (err != kDNSServiceErr_NoError)
      CLog::Log(LOGERROR, __FUNCTION__ " DNSServiceProcessResult returned (error = %ld)", (int) err);

    CSingleLock lock(m_data_guard);
    m_services.insert(make_pair(fcr_identifier, netService));
  }

  TXTRecordDeallocate(&txtRecord);

  return err == kDNSServiceErr_NoError;
}