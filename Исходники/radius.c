// Attempts Radius authentication (with specifying retry interval and multiple server)
bool RadiusLogin(CONNECTION *c, char *server, UINT port, UCHAR *secret, UINT secret_size, wchar_t *username, char *password, UINT interval, UCHAR *mschap_v2_server_response_20)
{
	UCHAR random[MD5_SIZE];
	UCHAR id;
	BUF *encrypted_password = NULL;
	BUF *user_name = NULL;
	//IP ip;
	bool ret = false;
	TOKEN_LIST *token;
	UINT i;
	LIST *ip_list;
	IPC_MSCHAP_V2_AUTHINFO mschap;
	bool is_mschap;
	char client_ip_str[MAX_SIZE];
	static UINT packet_id = 0;
	// Validate arguments
	if (server == NULL || port == 0 || (secret_size != 0 && secret == NULL) || username == NULL || password == NULL)
	{
		return false;
	}

	Zero(client_ip_str, sizeof(client_ip_str));
	if (c != NULL && c->FirstSock != NULL)
	{
		IPToStr(client_ip_str, sizeof(client_ip_str), &c->FirstSock->RemoteIP);
	}

	// Parse the MS-CHAP v2 authentication data
	Zero(&mschap, sizeof(mschap));
	is_mschap = ParseAndExtractMsChapV2InfoFromPassword(&mschap, password);

	// Split the server into tokens
	token = ParseToken(server, " ,;\t");

	// Get the IP address of the server
	ip_list = NewListFast(NULL);
	for(i = 0; i < token->NumTokens; i++)
	{
		IP *tmp_ip = Malloc(sizeof(IP));
		if (GetIP(tmp_ip, token->Token[i]))
		{
			Add(ip_list, tmp_ip);
		}
		else if (GetIPEx(tmp_ip, token->Token[i], true))
		{
			Add(ip_list, tmp_ip);
		}
		else
		{
			Free(tmp_ip);
		}
	}

	FreeToken(token);

	if(LIST_NUM(ip_list) == 0)
	{
		ReleaseList(ip_list);
		return false;
	}

	// Random number generation
	Rand(random, sizeof(random));

	// ID generation
	id = (UCHAR)(packet_id % 254 + 1);
	packet_id++;

	if (is_mschap == false)
	{
		// Encrypt the password
		encrypted_password = RadiusEncryptPassword(password, random, secret, secret_size);
		if (encrypted_password == NULL)
		{
			// Encryption failure
			ReleaseList(ip_list);
			return false;
		}
	}

	// Generate the user name packet
	user_name = RadiusCreateUserName(username);

	if (user_name != NULL)
	{
		// Generate a password packet
		BUF *user_password = (is_mschap ? NULL : RadiusCreateUserPassword(encrypted_password->Buf, encrypted_password->Size));
		BUF *nas_id = RadiusCreateNasId(CEDAR_SERVER_STR);

		if (is_mschap || user_password != NULL)
		{
			UINT64 start;
			UINT64 next_send_time;
			UCHAR tmp[MAX_SIZE];
			UINT recv_buf_size = 32768;
			UCHAR *recv_buf = MallocEx(recv_buf_size, true);
			// Generate an UDP packet
			BUF *p = NewBuf();
			UCHAR type = 1;
			SOCK *sock;
			USHORT sz = 0;
			UINT pos = 0;
			BOOL *finish = ZeroMallocEx(sizeof(BOOL) * LIST_NUM(ip_list), true);

			Zero(tmp, sizeof(tmp));

			WriteBuf(p, &type, 1);
			WriteBuf(p, &id, 1);
			WriteBuf(p, &sz, 2);
			WriteBuf(p, random, 16);
			WriteBuf(p, user_name->Buf, user_name->Size);

			if (is_mschap == false)
			{
				UINT ui;
				// PAP
				WriteBuf(p, user_password->Buf, user_password->Size);
				WriteBuf(p, nas_id->Buf, nas_id->Size);

				// Service-Type
				ui = Endian32(2);
				RadiusAddValue(p, 6, 0, 0, &ui, sizeof(ui));

				// NAS-Port-Type
				ui = Endian32(5);
				RadiusAddValue(p, 61, 0, 0, &ui, sizeof(ui));

				// Tunnel-Type
				ui = Endian32(1);
				RadiusAddValue(p, 64, 0, 0, &ui, sizeof(ui));

				// Tunnel-Medium-Type
				ui = Endian32(1);
				RadiusAddValue(p, 65, 0, 0, &ui, sizeof(ui));

				// Calling-Station-Id
				RadiusAddValue(p, 31, 0, 0, client_ip_str, StrLen(client_ip_str));

				// Tunnel-Client-Endpoint
				RadiusAddValue(p, 66, 0, 0, client_ip_str, StrLen(client_ip_str));
			}
			else
			{
				// MS-CHAP v2
				static UINT session_id = 0;
				USHORT us;
				UINT ui;
				char *ms_ras_version = "MSRASV5.20";
				UCHAR ms_chapv2_response[50];

				// Acct-Session-Id
				us = Endian16(session_id % 254 + 1);
				session_id++;
				RadiusAddValue(p, 44, 0, 0, &us, sizeof(us));

				// NAS-IP-Address
				if (c != NULL && c->FirstSock != NULL && c->FirstSock->IPv6 == false)
				{
					ui = IPToUINT(&c->FirstSock->LocalIP);
					RadiusAddValue(p, 4, 0, 0, &ui, sizeof(ui));
				}

				// Service-Type
				ui = Endian32(2);
				RadiusAddValue(p, 6, 0, 0, &ui, sizeof(ui));

				// MS-RAS-Vendor
				ui = Endian32(311);
				RadiusAddValue(p, 26, 311, 9, &ui, sizeof(ui));

				// MS-RAS-Version
				RadiusAddValue(p, 26, 311, 18, ms_ras_version, StrLen(ms_ras_version));

				// NAS-Port-Type
				ui = Endian32(5);
				RadiusAddValue(p, 61, 0, 0, &ui, sizeof(ui));

				// Tunnel-Type
				ui = Endian32(1);
				RadiusAddValue(p, 64, 0, 0, &ui, sizeof(ui));

				// Tunnel-Medium-Type
				ui = Endian32(1);
				RadiusAddValue(p, 65, 0, 0, &ui, sizeof(ui));

				// Calling-Station-Id
				RadiusAddValue(p, 31, 0, 0, client_ip_str, StrLen(client_ip_str));

				// Tunnel-Client-Endpoint
				RadiusAddValue(p, 66, 0, 0, client_ip_str, StrLen(client_ip_str));

				// MS-RAS-Client-Version
				RadiusAddValue(p, 26, 311, 35, ms_ras_version, StrLen(ms_ras_version));

				// MS-RAS-Client-Name
				RadiusAddValue(p, 26, 311, 34, client_ip_str, StrLen(client_ip_str));

				// MS-CHAP-Challenge
				RadiusAddValue(p, 26, 311, 11, mschap.MsChapV2_ServerChallenge, sizeof(mschap.MsChapV2_ServerChallenge));

				// MS-CHAP2-Response
				Zero(ms_chapv2_response, sizeof(ms_chapv2_response));
				Copy(ms_chapv2_response + 2, mschap.MsChapV2_ClientChallenge, 16);
				Copy(ms_chapv2_response + 2 + 16 + 8, mschap.MsChapV2_ClientResponse, 24);
				RadiusAddValue(p, 26, 311, 25, ms_chapv2_response, sizeof(ms_chapv2_response));

				// NAS-ID
				WriteBuf(p, nas_id->Buf, nas_id->Size);
			}

			SeekBuf(p, 0, 0);

			WRITE_USHORT(((UCHAR *)p->Buf) + 2, (USHORT)p->Size);

			// Create a socket
			sock = NewUDPEx(0, IsIP6(LIST_DATA(ip_list, pos)));

			// Transmission process start
			start = Tick64();
			if(interval < RADIUS_RETRY_INTERVAL)
			{
				interval = RADIUS_RETRY_INTERVAL;
			}
			else if(interval > RADIUS_RETRY_TIMEOUT)
			{
				interval = RADIUS_RETRY_TIMEOUT;
			}
			next_send_time = start + (UINT64)interval;

			while (true)
			{
				UINT server_port;
				UINT recv_size;
				//IP server_ip;
				SOCKSET set;
				UINT64 now;

SEND_RETRY:
				//SendTo(sock, &ip, port, p->Buf, p->Size);
				SendTo(sock, LIST_DATA(ip_list, pos), port, p->Buf, p->Size);

				Debug("send to host:%u\n", pos);

				next_send_time = Tick64() + (UINT64)interval;

RECV_RETRY:
				now = Tick64();
				if (next_send_time <= now)
				{
					// Switch the host to refer
					pos++;
					pos = pos % LIST_NUM(ip_list);

					goto SEND_RETRY;
				}

				if ((start + RADIUS_RETRY_TIMEOUT) < now)
				{
					// Time-out
					break;
				}

				InitSockSet(&set);
				AddSockSet(&set, sock);
				Select(&set, (UINT)(next_send_time - now), NULL, NULL);

				recv_size = RecvFrom(sock, LIST_DATA(ip_list, pos), &server_port, recv_buf, recv_buf_size);

				if (recv_size == 0)
				{
					Debug("Radius recv_size 0\n");
					finish[pos] = TRUE;
					for(i = 0; i < LIST_NUM(ip_list); i++)
					{
						if(finish[i] == FALSE)
						{
							// Switch the host to refer
							pos++;
							pos = pos % LIST_NUM(ip_list);
							goto SEND_RETRY;
						}
					}
					// Failure
					break;
				}
				else if (recv_size == SOCK_LATER)
				{
					// Waiting
					goto RECV_RETRY;
				}
				else
				{
					// Check such as the IP address
					if (/*Cmp(&server_ip, &ip, sizeof(IP)) != 0 || */server_port != port)
					{
						goto RECV_RETRY;
					}
					// Success
					if (recv_buf[0] == 2)
					{
						ret = true;

						if (is_mschap && mschap_v2_server_response_20 != NULL)
						{
							// Cutting corners Zurukko
							UCHAR signature[] = {0x1A, 0x33, 0x00, 0x00, 0x01, 0x37, 0x1A, 0x2D, 0x00, 0x53, 0x3D, };
							UINT i = SearchBin(recv_buf, 0, recv_buf_size, signature, sizeof(signature));

							if (i == INFINITE || ((i + sizeof(signature) + 40) > recv_buf_size))
							{
								ret = false;
							}
							else
							{
								char tmp[MAX_SIZE];
								BUF *b;

								Zero(tmp, sizeof(tmp));
								Copy(tmp, recv_buf + i + sizeof(signature), 40);

								b = StrToBin(tmp);

								if (b != NULL && b->Size == 20)
								{
									WHERE;
									Copy(mschap_v2_server_response_20, b->Buf, 20);
								}
								else
								{
									WHERE;
									ret = false;
								}

								FreeBuf(b);
							}
						}
					}
					break;
				}
			}

			Free(finish);

			// Release the socket
			ReleaseSock(sock);

			FreeBuf(p);
			FreeBuf(user_password);

			Free(recv_buf);
		}

		FreeBuf(nas_id);
		FreeBuf(user_name);
	}

	// Release the ip_list
	for(i = 0; i < LIST_NUM(ip_list); i++)
	{
		IP *tmp_ip = LIST_DATA(ip_list, i);
		Free(tmp_ip);
	}
	ReleaseList(ip_list);

	// Release the memory
	FreeBuf(encrypted_password);

	return ret;
}