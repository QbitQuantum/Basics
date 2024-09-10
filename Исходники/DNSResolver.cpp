   bool
   DNSResolver::Resolve_(const String &sSearchFor, std::vector<String> &vecFoundNames, WORD wType, int iRecursion)
   {
      if (iRecursion > 10)
      {
         String sMessage = Formatter::Format("Too many recursions during query. Query: {0}, Type: {1}", sSearchFor, wType);
         ErrorManager::Instance()->ReportError(ErrorManager::Low, 4401, "DNSResolver::Resolve_", sMessage);

         return false;
      }

      PDNS_RECORD pDnsRecord = NULL;
      PIP4_ARRAY pSrvList = NULL;

      DWORD fOptions = DNS_QUERY_STANDARD;
      
      DNS_STATUS nDnsStatus = DnsQuery(sSearchFor, wType, fOptions, NULL, &pDnsRecord, NULL);

      PDNS_RECORD pDnsRecordsToDelete = pDnsRecord;

      if (nDnsStatus != 0)
      {
         if (pDnsRecordsToDelete)
            _FreeDNSRecord(pDnsRecordsToDelete);

         bool bDNSError = IsDNSError_(nDnsStatus);

         if (bDNSError)
         {
            String sMessage;
            sMessage.Format(_T("DNS - Query failure. Query: %s, Type: %d, DnsQuery return value: %d."), sSearchFor.c_str(), wType, nDnsStatus);
            LOG_TCPIP(sMessage);
            return false;
         }

         return true;
      }

      std::vector<DnsRecordWithPreference> foundDnsRecordsWithPreference;

      do
      {
         switch (pDnsRecord->wType)
         {
            case DNS_TYPE_A:
            {
               SOCKADDR_IN addr;
               memset(&addr, 0, sizeof addr);

               addr.sin_family = AF_INET;
               addr.sin_addr = *((in_addr*)&(pDnsRecord->Data.AAAA.Ip6Address));

               char buf[128];
               DWORD bufSize = sizeof(buf);

               if (WSAAddressToStringA((sockaddr*)&addr, sizeof addr, NULL, buf, &bufSize) == 0)
               {
                  DnsRecordWithPreference rec(0, buf);
                  foundDnsRecordsWithPreference.push_back(rec);
               }
               
               break;
            }
            case DNS_TYPE_AAAA:
            {
               SOCKADDR_IN6 addr;
               memset(&addr, 0, sizeof addr);

               addr.sin6_family = AF_INET6;
               addr.sin6_addr = *((in_addr6*)&(pDnsRecord->Data.AAAA.Ip6Address));

               char buf[128];
               DWORD bufSize = sizeof(buf);

               if (WSAAddressToStringA((sockaddr*)&addr, sizeof addr, NULL, buf, &bufSize) == 0)
               {
                  DnsRecordWithPreference rec(0, buf);
                  foundDnsRecordsWithPreference.push_back(rec);
               }
               
               break;
            }
            case DNS_TYPE_CNAME:
            {
               String sDomainName = pDnsRecord->Data.CNAME.pNameHost;
               if (!Resolve_(sDomainName, vecFoundNames, wType, iRecursion+1))
                  return false;

               break;
            }
            case DNS_TYPE_MX: 
            {
               String sName = pDnsRecord->pName;
               bool bNameMatches = (sName.CompareNoCase(sSearchFor) == 0);

               if (pDnsRecord->Flags.S.Section == DNSREC_ANSWER && bNameMatches)
               {
                  DnsRecordWithPreference rec(pDnsRecord->Data.MX.wPreference, pDnsRecord->Data.MX.pNameExchange);
                  foundDnsRecordsWithPreference.push_back(rec);
               }

               break;
            }
         case DNS_TYPE_TEXT: 
            {
               AnsiString retVal;

               for (u_int i = 0; i < pDnsRecord->Data.TXT.dwStringCount; i++)
                  retVal += pDnsRecord->Data.TXT.pStringArray[i];
               
               DnsRecordWithPreference rec (0, retVal);
               foundDnsRecordsWithPreference.push_back(rec);

               break;
            }
         case DNS_TYPE_PTR: 
            {
               AnsiString retVal;
               retVal = pDnsRecord->Data.PTR.pNameHost;

               DnsRecordWithPreference rec(0, retVal);
               foundDnsRecordsWithPreference.push_back(rec);
               break;
            }
            default:
            {
               ErrorManager::Instance()->ReportError(ErrorManager::Medium, 5036, "DNSResolver::Resolve_", Formatter::Format("Queried for {0} but received type {1}", wType, pDnsRecord->wType));
               break;
            }
         }

         pDnsRecord = pDnsRecord->pNext;
      }
      while (pDnsRecord != nullptr);

      std::sort(foundDnsRecordsWithPreference.begin(), foundDnsRecordsWithPreference.end(), SortDnsRecordWithPreference);

      for (DnsRecordWithPreference item : foundDnsRecordsWithPreference)
      {
         vecFoundNames.push_back(item.Value);
      }

      _FreeDNSRecord(pDnsRecordsToDelete);
      pDnsRecordsToDelete = 0;

      return true;
   }