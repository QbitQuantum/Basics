error_t dnsSendQuery(DnsCacheEntry *entry)
{
   error_t error;
   size_t length;
   size_t offset;
   ChunkedBuffer *buffer;
   DnsHeader *message;
   DnsQuestion *dnsQuestion;
   IpAddr destIpAddr;

#if (IPV4_SUPPORT == ENABLED)
   //An IPv4 address is expected?
   if(entry->type == HOST_TYPE_IPV4)
   {
      //Select the relevant DNS server
      destIpAddr.length = sizeof(Ipv4Addr);
      ipv4GetDnsServer(entry->interface, entry->dnsServerNum, &destIpAddr.ipv4Addr);

      //Make sure the IP address is valid
      if(destIpAddr.ipv4Addr == IPV4_UNSPECIFIED_ADDR)
         return ERROR_NO_DNS_SERVER;
   }
   else
#endif
#if (IPV6_SUPPORT == ENABLED)
   //An IPv6 address is expected?
   if(entry->type == HOST_TYPE_IPV6)
   {
      //Select the relevant DNS server
      destIpAddr.length = sizeof(Ipv6Addr);
      ipv6GetDnsServer(entry->interface, entry->dnsServerNum, &destIpAddr.ipv6Addr);

      //Make sure the IP address is valid
      if(ipv6CompAddr(&destIpAddr.ipv6Addr, &IPV6_UNSPECIFIED_ADDR))
         return ERROR_NO_DNS_SERVER;
   }
   else
#endif
   //Invalid host type?
   {
      //Report an error
      return ERROR_INVALID_PARAMETER;
   }

   //Allocate a memory buffer to hold the DNS query message
   buffer = udpAllocBuffer(DNS_MESSAGE_MAX_SIZE, &offset);
   //Failed to allocate buffer?
   if(!buffer) return ERROR_OUT_OF_MEMORY;

   //Point to the DNS header
   message = chunkedBufferAt(buffer, offset);

   //Format DNS query message
   message->id = htons(entry->id);
   message->qr = 0;
   message->opcode = DNS_OPCODE_QUERY;
   message->aa = 0;
   message->tc = 0;
   message->rd = 1;
   message->ra = 0;
   message->z = 0;
   message->rcode = DNS_RCODE_NO_ERROR;

   //The DNS query contains one question
   message->qdcount = HTONS(1);
   message->ancount = 0;
   message->nscount = 0;
   message->arcount = 0;

   //Length of the DNS query message
   length = sizeof(DnsHeader);

   //Encode the host name using the DNS name notation
   length += dnsEncodeName(entry->name, message->questions);

   //Point to the corresponding question structure
   dnsQuestion = DNS_GET_QUESTION(message, length);

#if (IPV4_SUPPORT == ENABLED)
   //An IPv4 address is expected?
   if(entry->type == HOST_TYPE_IPV4)
   {
      //Fill in question structure
      dnsQuestion->qtype = HTONS(DNS_RR_TYPE_A);
      dnsQuestion->qclass = HTONS(DNS_RR_CLASS_IN);
   }
#endif
#if (IPV6_SUPPORT == ENABLED)
   //An IPv6 address is expected?
   if(entry->type == HOST_TYPE_IPV6)
   {
      //Fill in question structure
      dnsQuestion->qtype = HTONS(DNS_RR_TYPE_AAAA);
      dnsQuestion->qclass = HTONS(DNS_RR_CLASS_IN);
   }
#endif

   //Update the length of the DNS query message
   length += sizeof(DnsQuestion);

   //Adjust the length of the multi-part buffer
   chunkedBufferSetLength(buffer, offset + length);

   //Debug message
   TRACE_INFO("Sending DNS message (%" PRIuSIZE " bytes)...\r\n", length);
   //Dump message
   dnsDumpMessage(message, length);

   //Send DNS query message
   error = udpSendDatagramEx(entry->interface, entry->port,
      &destIpAddr, DNS_PORT, buffer, offset, 0);

   //Free previously allocated memory
   chunkedBufferFree(buffer);
   //Return status code
   return error;
}