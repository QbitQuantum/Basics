boolean CDNSClient::Resolve (const char *pHostname, CIPAddress *pIPAddress)
{
	assert (pHostname != 0);

	if ('1' <= *pHostname && *pHostname <= '9')
	{
		return FALSE;
	}

	assert (m_pNetSubSystem != 0);
	CIPAddress DNSServer (m_pNetSubSystem->GetConfig ()->GetDNSServer ()->Get ());
	
	CSocket Socket (m_pNetSubSystem, IPPROTO_UDP);
	if (Socket.Connect (DNSServer, 53) != 0)
	{
		return FALSE;
	}

	u8 Buffer[DNS_MAX_MESSAGE_SIZE];
	memset (Buffer, 0, sizeof Buffer);
	TDNSHeader *pDNSHeader = (TDNSHeader *) Buffer;

	u16 nXID = s_nXID++;

	pDNSHeader->nID      = le2be16 (nXID);
	pDNSHeader->nFlags   = BE (DNS_FLAGS_OPCODE_QUERY | DNS_FLAGS_RD);
	pDNSHeader->nQDCount = BE (1);

	u8 *pQuery = Buffer + sizeof (TDNSHeader);

	char Hostname[MAX_HOSTNAME_SIZE];
	strncpy (Hostname, pHostname, MAX_HOSTNAME_SIZE-1);
	Hostname[MAX_HOSTNAME_SIZE-1] = '\0';

	char *pSavePtr;
	size_t nLength;
	char *pLabel = strtok_r (Hostname, ".", &pSavePtr);
	while (pLabel != 0)
	{
		nLength = strlen (pLabel);
		if (   nLength > 255
		    || (int) (nLength+1+1) >= DNS_MAX_MESSAGE_SIZE-(pQuery-Buffer))
		{
			return FALSE;
		}

		*pQuery++ = (u8) nLength;

		strcpy ((char *) pQuery, pLabel);
		pQuery += nLength;

		pLabel = strtok_r (0, ".", &pSavePtr);
	}

	*pQuery++ = '\0';

	TDNSQueryTrailer QueryTrailer;
	QueryTrailer.nQType  = BE (DNS_QTYPE_A);
	QueryTrailer.nQClass = BE (DNS_QCLASS_IN);

	if ((int) (sizeof QueryTrailer) > DNS_MAX_MESSAGE_SIZE-(pQuery-Buffer))
	{
		return FALSE;
	}
	memcpy (pQuery, &QueryTrailer, sizeof QueryTrailer);
	pQuery += sizeof QueryTrailer;
	
	int nSize = pQuery - Buffer;
	assert (nSize <= DNS_MAX_MESSAGE_SIZE);

	unsigned char RecvBuffer[DNS_MAX_MESSAGE_SIZE];
	int nRecvSize;

	unsigned nTry = 1;
	do
	{
		if (   nTry++ > 3
		    || Socket.Send (Buffer, nSize, 0) != nSize)
		{
			return FALSE;
		}

		CScheduler::Get ()->MsSleep (1000);

		nRecvSize = Socket.Receive (RecvBuffer, DNS_MAX_MESSAGE_SIZE, MSG_DONTWAIT);
		assert (nRecvSize < DNS_MAX_MESSAGE_SIZE);
	}
	while (nRecvSize < (int) (sizeof (TDNSHeader)+sizeof (TDNSResourceRecordTrailerAIN)));

	pDNSHeader = (TDNSHeader *) RecvBuffer;
	if (   pDNSHeader->nID != le2be16 (nXID)
	    ||    (pDNSHeader->nFlags & BE (  DNS_FLAGS_QR
	                                    | DNS_FLAGS_OPCODE
	                                    | DNS_FLAGS_TC
	                                    | DNS_FLAGS_RCODE))
	       != BE (DNS_FLAGS_QR | DNS_FLAGS_OPCODE_QUERY | DNS_RCODE_SUCCESS)
	    || pDNSHeader->nQDCount != BE (1)
	    || pDNSHeader->nANCount == BE (0))
	{
		return FALSE;
	}

	u8 *pResponse = RecvBuffer + sizeof (TDNSHeader);

	// parse the query section
	while ((nLength = *pResponse++) > 0)
	{
		pResponse += nLength;
		if (pResponse-RecvBuffer >= nRecvSize)
		{
			return FALSE;
		}
	}

	pResponse += sizeof (TDNSQueryTrailer);
	if (pResponse-RecvBuffer >= nRecvSize)
	{
		return FALSE;
	}

	TDNSResourceRecordTrailerAIN RRTrailer;

	// parse the answer section
	while (1)
	{
		nLength = *pResponse++;
		if ((nLength & 0xC0) == 0xC0)		// check for compression
		{
			pResponse++;
		}
		else
		{
			if (pResponse-RecvBuffer >= nRecvSize)
			{
				return FALSE;
			}

			while ((nLength = *pResponse++) > 0)
			{
				pResponse += nLength;
				if (pResponse-RecvBuffer >= nRecvSize)
				{
					return FALSE;
				}
			}
		}

		if (pResponse-RecvBuffer > (int) (nRecvSize-sizeof RRTrailer))
		{
			return FALSE;
		}

		memcpy (&RRTrailer, pResponse, sizeof RRTrailer);

		if (   RRTrailer.nType     == BE (DNS_QTYPE_A)
		    && RRTrailer.nClass    == BE (DNS_QCLASS_IN)
		    && RRTrailer.nRDLength == BE (DNS_RDLENGTH_AIN))
		{
			break;
		}

		pResponse += DNS_RR_TRAILER_HEADER_LENGTH + BE (RRTrailer.nRDLength);
		if (pResponse-RecvBuffer >= nRecvSize)
		{
			return FALSE;
		}
	}

	assert (pIPAddress != 0);
	pIPAddress->Set (RRTrailer.RData);

	return TRUE;
}