// Similar function in sisis_api.c
void sisis_process_message(char * msg, int msg_len, int sock, struct sockaddr * from, socklen_t from_len)
{
	// Get message version
	unsigned short version = 0;
	if (msg_len >= 2)
		version = ntohs(*(unsigned short *)msg);
	printf("Message:\n");
	printf("\tVersion: %u\n", version);
	if (version == 1)
	{
		// Get request id
		unsigned int request_id = 0;
		if (msg_len >= 6)
			request_id = ntohl(*(unsigned int *)(msg+2));
		printf("\tRequest Id: %u\n", request_id);
		
		// Get command
		unsigned short command = -1;
		if (msg_len >= 8)
			command = ntohs(*(unsigned short *)(msg+6));
		printf("\tCommand: %u\n", command);
		switch (command)
		{
			case SISIS_CMD_REGISTER_ADDRESS:
			case SISIS_CMD_UNREGISTER_ADDRESS:
				{
#ifdef USE_IPV6
					if (msg_len >= 12)
					{
						// Set up prefix
						struct prefix p;
						p.family = ntohs(*(unsigned short *)(msg+8));
						p.prefixlen = 128;
						
						// Get address
						short len = ntohs(*(unsigned short *)(msg+10));
						char ip_addr[64];
						memset(ip_addr, 0, 64);
						if (len >= 64 || msg_len > msg-12)
							printf("Invalid IP address length: %hd\n", len);
						else
						{
							memcpy(ip_addr, msg+12, len);
							printf("\tIP Address: %s\n", ip_addr);
							
							// Set expiration
							time_t expires = time(NULL) + SISIS_ADDRESS_TIMEOUT;
							
							// Get loopback ifindex
							int ifindex = if_nametoindex("lo");
							
							// Set up prefix
							if (inet_pton(p.family, ip_addr, &p.u.prefix) != 1)
							{
								// Construct reply
								char * buf;
								int buf_len = sisis_construct_message(&buf, SISIS_MESSAGE_VERSION, request_id, SISIS_NACK, NULL, 0);
								sendto(sock, buf, buf_len, 0, from, from_len);
								free(buf);
								
								zlog_err ("sisis_process_message: Invalid SIS-IS address: %s", ip_addr);
								return;
							}
							
							int zcmd = (command == SISIS_CMD_REGISTER_ADDRESS) ? ZEBRA_INTERFACE_ADDRESS_ADD : ZEBRA_INTERFACE_ADDRESS_DELETE;
							int status = zapi_interface_address(zcmd, zclient, &p, ifindex, &expires);
							
							// Construct reply
							char * buf;
							int buf_len = sisis_construct_message(&buf, SISIS_MESSAGE_VERSION, request_id, (status == 0) ? SISIS_ACK : SISIS_NACK, NULL, 0);
							printf("\tSending %s\n", (status == 0) ? "ACK" : "NACK");
							sendto(sock, buf, buf_len, 0, from, from_len);
							free(buf);
						}
					}
#else /* IPv6 Version */
					char ip_addr[INET_ADDRSTRLEN+1];
					memset(ip_addr, 0, INET_ADDRSTRLEN+1);
					memcpy(ip_addr, msg+8, from_len-8);
					printf("\tIP Address: %s\n", ip_addr);
					
					// Set expiration
					time_t expires = time(NULL) + SISIS_ADDRESS_TIMEOUT;
					
					// Get loopback ifindex
					int ifindex = if_nametoindex("lo");
					
					// Set up prefix
					struct prefix_ipv4 p;
					p.family = AF_INET;
					p.prefixlen = 32;
					if (inet_pton(AF_INET, ip_addr, &p.prefix.s_addr) != 1)
					{
						// Construct reply
						char * buf;
						int buf_len = sisis_construct_message(&buf, SISIS_MESSAGE_VERSION, request_id, SISIS_NACK, NULL, 0);
						sendto(sock, buf, buf_len, 0, from, from_len);
						free(buf);
						
						zlog_err ("sisis_process_message: Invalid SIS-IS address: %s", ip_addr);
						return;
					}
					
					int zcmd = (command == SISIS_CMD_REGISTER_ADDRESS) ? ZEBRA_INTERFACE_ADDRESS_ADD : ZEBRA_INTERFACE_ADDRESS_DELETE;
					int status = zapi_interface_address(zcmd, zclient, &p, ifindex, &expires);
					
					// Construct reply
					char * buf;
					int buf_len = sisis_construct_message(&buf, SISIS_MESSAGE_VERSION, request_id, (status == 0) ? SISIS_ACK : SISIS_NACK, NULL, 0);
					printf("\tSending %s\n", (status == 0) ? "ACK" : "NACK");
					sendto(sock, buf, buf_len, 0, from, from_len);
					free(buf);
#endif /* USE_IPV6 */
				}
				break;
		}
	}
}