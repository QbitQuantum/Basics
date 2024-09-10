int send_file(HTHREAD_PTR descr, char *filename)
{
	WSADATA				wsa_data;
	SOCKET				data_socket					= INVALID_SOCKET;
	struct sockaddr_in	send_data_addr;
	HPACKET				packet;
	HPARTITION			partition;
	FILE				*fp;
	int					return_code;
	unsigned long		at_location,
						read_amount,
						tries;					
	unsigned char		packet_count;
	char				control_message[MAX_INPUT_LENGTH];

	if(fopen_s(&fp, filename, "rb") > 0)
	{
		memset(control_message, 0, sizeof(MAX_INPUT_LENGTH));
		control_message[0] = CONTROL_MESSAGE_NO_SUCH_FILE;
		return_code = send(descr->socket, control_message, (int)strlen(control_message), 0);		
		return 1;
	}

	for(tries = 0; tries < CONTROL_MESSAGE_RECV_RETRIES; tries++)
	{
		memset(control_message, 0, sizeof(MAX_INPUT_LENGTH));
		return_code = recv(descr->socket, control_message, MAX_INPUT_LENGTH-1, 0);
		if(return_code < 1)
		{
			printf("failed to recv command: %d\n", WSAGetLastError());
			closesocket(data_socket);
			return 0;
		}

		if(control_message[0] == CONTROL_MESSAGE_OK_START_SENDING)
			break;
	}

	if(tries >= CONTROL_MESSAGE_RECV_RETRIES)
	{
		printf("No CONTROL_MESSAGE_OK_START_SENDING from %s\n", inet_ntoa(descr->address.sin_addr));
		closesocket(data_socket);
		return 0;
	}

	WSAStartup(MAKEWORD(2,2), &wsa_data);
	data_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	send_data_addr.sin_family = AF_INET;
	send_data_addr.sin_port = htons(CONNECT_PORT_N);//descr->address.sin_port;
	send_data_addr.sin_addr = descr->address.sin_addr;//inet_addr("123.456.789.1");

	packet.partition_id = 0;
	packet.reserved = 0;
	while(!feof(fp))
	{
		memset(partition.packet_stats, 0, MAX_PARTITION_DIVISIONS+1);
		partition.actual_size = (unsigned long)fread(partition.data, 1, PARTITION_LENGTH_TOTAL, fp);
		packet_count = (unsigned char)ceil(partition.actual_size / PACKET_LENGTH_DATA);

		memset(control_message, 0, sizeof(MAX_INPUT_LENGTH));
		sprintf_s(control_message, MAX_INPUT_LENGTH, "  %u", partition.actual_size);
		control_message[0] = CONTROL_MESSAGE_SENDING_DATA;
		return_code = send(descr->socket, control_message, (int)strlen(control_message)+1, 0);
		if(return_code == SOCKET_ERROR)
		{
			printf("failed to send command: %d\n", WSAGetLastError());
			closesocket(data_socket);
			return 0;
		}		

		while(1)
		{	
			for(packet.packet_id = 0; packet.packet_id < packet_count; packet.packet_id++)
			{
				if(partition.packet_stats[packet.packet_id] != 1)
					break;
			}

			if(packet.packet_id == packet_count)
				break;

			for(packet.packet_id = 0; packet.packet_id < packet_count; packet.packet_id++)
			{
				if(partition.packet_stats[packet.packet_id] != 1)
				{					
					memset(packet.data, 0, sizeof(PARTITION_LENGTH_TOTAL));
					at_location = packet.packet_id * PACKET_LENGTH_DATA;
					read_amount = at_location + PACKET_LENGTH_DATA < partition.actual_size ? PACKET_LENGTH_DATA : partition.actual_size - at_location;
					memcpy(packet.data, &partition.data[at_location], read_amount);
					packet.crc = compute_crc((const unsigned char *)packet.data, PACKET_LENGTH_DATA);

					return_code = sendto(data_socket, (char *)&packet, sizeof(packet), 0, (SOCKADDR *)&send_data_addr, sizeof(send_data_addr));
					if(return_code == SOCKET_ERROR)
					{
						printf("failed to send command: %d\n", WSAGetLastError());
						closesocket(data_socket);
						return 0;
					}
					Sleep(5);
				}
			}

			memset(control_message, 0, sizeof(MAX_INPUT_LENGTH));
			control_message[0] = CONTROL_MESSAGE_PARTITION_SENT;
			return_code = send(descr->socket, control_message, (int)strlen(control_message)+1, 0);
			if(return_code == SOCKET_ERROR)
			{
				printf("failed to send command: %d\n", WSAGetLastError());
				closesocket(data_socket);
				return 0;
			}

			for(tries = 0; tries < CONTROL_MESSAGE_RECV_RETRIES; tries++)
			{
				memset(control_message, 0, sizeof(MAX_INPUT_LENGTH));
				return_code = recv(descr->socket, control_message, MAX_INPUT_LENGTH-1, 0);
				if(return_code < 1)
				{
					printf("failed to recv command: %d\n", WSAGetLastError());
					closesocket(data_socket);
					return 0;
				}

				if(control_message[0] == CONTROL_MESSAGE_PARTITION_STATUS)
				{
					memset(partition.packet_stats, 0, MAX_PARTITION_DIVISIONS+1);
					memcpy(partition.packet_stats, &control_message[2], MAX_PARTITION_DIVISIONS);
					break;
				}
			}

			if(tries >= CONTROL_MESSAGE_RECV_RETRIES)
			{
				printf("No CONTROL_MESSAGE_PARTITION_STATUS from %s\n", inet_ntoa(descr->address.sin_addr));
				closesocket(data_socket);
				return 0;
			}
		}

		packet.partition_id++;
	}
	fclose(fp);

	memset(control_message, 0, sizeof(MAX_INPUT_LENGTH));
	control_message[0] = CONTROL_MESSAGE_ALL_DATA_SENT;
	return_code = send(descr->socket, control_message, (int)strlen(control_message)+1, 0);
	if(return_code == SOCKET_ERROR)
	{
		printf("failed to send command: %d\n", WSAGetLastError());
		closesocket(data_socket);
		return 1;
	}			

	closesocket(data_socket);
	return 1;
}