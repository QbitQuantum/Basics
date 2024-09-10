/*!
 * \brief
 * This function pings an IPv6-Address with a specified Time-To-Live-value.
 * 
 * \param ai
 * The AddrInfo-representation of the TargetIP
 * 
 * \param ttl
 * The Time-To-Live-value to perform the ping with
 * 
 * \param out
 * The Buffer into which the result of the ping-command will be written
 * 
 * \param outSize
 * The maximum number of characters that can be written into "out"
 * 
 * \returns
 * True if the execution succeded and false otherwise. The following will be written in "out": "TARGET "+TargetIP if the target was reached, "HOP "+HopIP if an intermediate Host was reached or "NO_REPLY" if an execution error occurred. If an internal error occured, a message describing that error will be written.
 *
 * \remarks
 * ai will be Freed
 */
bool ping6(struct addrinfoW *ai, int ttl, WCHAR * out, int  outSize){
	// Create a handle to a hIcmpFile (required by Icmp6SendEcho2)
		HANDLE hIcmpFile = Icmp6CreateFile();
		if (hIcmpFile == INVALID_HANDLE_VALUE) {
			outPutWstring(std::wstring(L"Icmp6Createfile returned error: ")+getFormatedLastError(),out,outSize);

			// Free all allocated resources
			FreeAddrInfoW(ai);
			return false;
		}

		// A ICMP-request using IPv6 requires a source address: Get the system's IPv6 addresses
		ADDRINFOW hints;
		memset(&hints,0,sizeof(ADDRINFOW));
		hints.ai_family = AF_INET6;
		struct addrinfoW *lai;
		if(! (0==GetAddrInfoW(L"",NULL,&hints,&lai))){
			outPutWstring(std::wstring(L"Invalid Socket (Localhost) : ")+getFormatedLastError(),out,outSize);

			// Free all allocated resources
			FreeAddrInfoW(ai);
			IcmpCloseHandle(hIcmpFile);
			return false;
		}

		// Out of all of the system's IPv6-addresses: get a global IPv6 IP-Address for localhost
		struct addrinfoW *sourceGlobal = lai;
		while(sourceGlobal != NULL){
			sockaddr_in6 * a = (sockaddr_in6 *)sourceGlobal->ai_addr;
			if(IN6_IS_ADDR_GLOBAL(&a->sin6_addr)) break;
			sourceGlobal = sourceGlobal->ai_next;
		}

		// If there is none then there is no way to perform an ICMP-request on a IPv6-address -> abbort!
		if(sourceGlobal == NULL){
			outPutWstring(std::wstring(L"No global IPv6 interface found on localhost: ")+getFormatedLastError(),out,outSize);

			// Free all allocated resources
			FreeAddrInfoW(ai);
			FreeAddrInfoW(lai);
			IcmpCloseHandle(hIcmpFile);
			return false;
		}


		// Build the payload of the ICMP-request (mustn't be empty)
		char SendData[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ012345";

		// Allocate space for a single reply
		DWORD ReplySize = sizeof (ICMPV6_ECHO_REPLY) + sizeof (SendData) + 8 + sizeof(IO_STATUS_BLOCK);
		LPVOID ReplyBuffer = (VOID *) malloc(ReplySize);

		// Create a IP_OPTION_INFORMATION and set its TTL-field so Icmp6SendEcho2 will perform a ping with the correct TTL
		IP_OPTION_INFORMATION ipopts;
		memset(&ipopts,0,sizeof(ipopts));
		ipopts.Ttl = (unsigned char)ttl;

		//Try to perform the actual ping
		DWORD dwRetVal = Icmp6SendEcho2(hIcmpFile, NULL, NULL, NULL,(sockaddr_in6 *)sourceGlobal->ai_addr,  (sockaddr_in6 *)ai->ai_addr, SendData, sizeof (SendData), &ipopts, ReplyBuffer, ReplySize, 1000);
		if (dwRetVal == 0) {

			// In case it failed: Did it fail because of a timeout or because of a serious problem?
			bool success = false;
			DWORD lastError = GetLastError();
			if(IP_REQ_TIMED_OUT == lastError || IP_DEST_NET_UNREACHABLE ==  lastError ){
				// If it failed because of a Timeout return "NO_REPLY"
				outPutWstring(std::wstring(L"NO_REPLY"),out,outSize);
				success = true;
			}
			else{
				// If it failed because of a serious problem return a detailed description about the failure
				outPutWstring(std::wstring(L"Call to Icmp6SendEcho2 failed: ")+getFormatedLastError(),out,outSize);
			}

			// Free all allocated resources
			FreeAddrInfoW(ai);
			FreeAddrInfoW(lai);
			free(ReplyBuffer);
			IcmpCloseHandle(hIcmpFile);
			return success;
		}

		// Parse the reply on the ICMP-request
		PICMPV6_ECHO_REPLY pEchoReply = (PICMPV6_ECHO_REPLY) ReplyBuffer;

		/*
		 * Extract the address of the replying host
		 */
		// First: copy the reply data into a sockaddr_in6-struckture
		PIPV6_ADDRESS_EX pIP6Addr = &pEchoReply->Address;;
		sockaddr_in6 sock6;
		sock6.sin6_family = AF_INET6;
		sock6.sin6_flowinfo = pIP6Addr->sin6_flowinfo;
		sock6.sin6_port = pIP6Addr->sin6_port;
		sock6.sin6_scope_id = pIP6Addr->sin6_scope_id;
		memcpy(&sock6.sin6_addr, pIP6Addr->sin6_addr,sizeof(IN6_ADDR));

		// Second: convert it into human readable version
		WCHAR  ip6AddressString[256];
		DWORD bufferLenght = 256;
		if(0 != WSAAddressToStringW((LPSOCKADDR)&sock6,sizeof(sockaddr_in6),NULL,ip6AddressString,&bufferLenght)){
			outPutWstring(std::wstring(L"Call to WSAAddressToStringW failed: ")+getFormatedLastError(),out,outSize);

			// Free all allocated resources
			FreeAddrInfoW(ai);
			FreeAddrInfoW(lai);
			free(ReplyBuffer);
			IcmpCloseHandle(hIcmpFile);
			return false;
		}

		// Third: convert it into a wstring
		std::wstring hopName = std::wstring(ip6AddressString);

		/*
		 * Switch according to status of reply
		 */
		ULONG status = pEchoReply->Status;

		if(status == IP_SUCCESS){ 
			// Ping reached the target
			outPutWstring(std::wstring(L"TARGET ")+ hopName,out,outSize);
		}
		else if(status == IP_TTL_EXPIRED_TRANSIT || status == IP_TTL_EXPIRED_REASSEM){ 
			// Ping got a reply from a hop on the way to target
			outPutWstring(std::wstring(L"HOP ")+ hopName,out,outSize);
		}
		else{ 
			// Something didn't work
			outPutWstring(std::wstring(L"NO_REPLY"),out,outSize);
		}

		// Free all allocated resources
		free(ReplyBuffer);
		FreeAddrInfoW(ai);
		FreeAddrInfoW(lai);
		IcmpCloseHandle(hIcmpFile);
		return true;
}