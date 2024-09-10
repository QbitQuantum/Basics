void
ManagementTool::addRrSet(const Name& zoneName,
                         const Name& label,
                         const name::Component& type,
                         NdnsType ndnsType,
                         const uint64_t version,
                         const std::vector<std::string>& contents,
                         const Name& inputDskCertName,
                         const time::seconds& ttl)
{
  // check pre-condition
  Zone zone(zoneName);
  if (!m_dbMgr.find(zone)) {
    throw Error(zoneName.toUri() + " is not presented in the NDNS db");
  }

  if (ndnsType == NDNS_UNKNOWN) {
    throw Error("The ndns type is unknown");
  }

  if (type == label::CERT_RR_TYPE) {
    throw Error("It cannot handle ID-CERT rrset type");
  }

  // check strange rr type and ndns type combination
  if (type == label::NS_RR_TYPE && ndnsType == NDNS_RAW) {
    throw Error("NS cannot be of the type NDNS_RAW");
  }

  if (type == label::TXT_RR_TYPE && ndnsType != NDNS_RESP) {
    throw Error("TXT cannot be of the type NDNS_RAW or NDNS_AUTH");
  }

  if (ndnsType == NDNS_RAW && contents.size() != 1) {
    throw Error("NDNS_RAW must contain a single content element");
  }

  Name dskName;
  Name dskCertName = inputDskCertName;
  if (dskCertName == DEFAULT_CERT) {
    dskName = m_keyChain.getDefaultKeyNameForIdentity(zoneName);
    dskCertName = m_keyChain.getDefaultCertificateNameForKey(dskName);
  }
  else {
    if (!matchCertificate(dskCertName, zoneName)) {
      throw Error("Cannot verify certificate");
    }
  }

  time::seconds actualTtl = ttl;
  if (ttl == DEFAULT_RR_TTL)
    actualTtl = zone.getTtl();

  // set rrset
  Rrset rrset(&zone);
  rrset.setLabel(label);
  rrset.setType(type);
  rrset.setTtl(actualTtl);

  // set response
  Response re;
  re.setZone(zoneName);
  re.setQueryType(label::NDNS_ITERATIVE_QUERY);
  re.setRrLabel(label);
  re.setRrType(type);
  re.setNdnsType(ndnsType);
  re.setFreshnessPeriod(actualTtl);

  //set content according to ndns type
  if (ndnsType == NDNS_RAW) {
    Block tmp = ndn::dataBlock(ndn::tlv::Content, contents[0].c_str(), contents[0].length());
    re.setAppContent(tmp);
  }
  else if (ndnsType != NDNS_AUTH) {
    if (contents.empty()) {
      re.addRr("");
    }
    else {
      for (const auto& item : contents) {
        re.addRr(item);
      }
    }
  }

  if (version != VERSION_USE_UNIX_TIMESTAMP) {
    name::Component tmp = name::Component::fromVersion(version);
    re.setVersion(tmp);
  }
  shared_ptr<Data> data = re.toData();
  m_keyChain.sign(*data, dskCertName);

  rrset.setVersion(re.getVersion());
  rrset.setData(data->wireEncode());

  checkRrsetVersion(rrset);
  NDNS_LOG_INFO("Added " << rrset);
  m_dbMgr.insert(rrset);
}