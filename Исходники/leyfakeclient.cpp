int HandleConnectionLessPacket(char*ip, short port, int connection_less, bf_read& recvdata)
{
	recvdata.ReadLong();

	int header = 0;
	int id = 0;
	int total = 0;
	int number = 0;
	short splitsize = 0;

	if (connection_less == 1)
	{
		header = recvdata.ReadByte();
	}
	else {
		id = recvdata.ReadLong();
		total = recvdata.ReadByte();
		number = recvdata.ReadByte();
		splitsize = recvdata.ReadByte();
	}

	switch (header)
	{

	case '9':
	{
		recvdata.ReadLong();

		char error[1024];
		recvdata.ReadString(error, 1024);
		printf("Connection refused! [%s]\n", error);

		NET_Reconnect();

		return 0;
	}
	case 'A': // A2A_GETCHALLENGE
	{
		bconnectstep = 2;
		long magicnumber = recvdata.ReadLong();

		serverchallenge = recvdata.ReadLong();
		ourchallenge = recvdata.ReadLong();
		authprotocol = recvdata.ReadLong();

		steamkey_encryptionsize = recvdata.ReadShort(); // gotta be 0

		recvdata.ReadBytes(steamkey_encryptionkey, steamkey_encryptionsize);
		recvdata.ReadBytes(serversteamid, sizeof(serversteamid));
		vacsecured = recvdata.ReadByte();

		printf("Challenge: %lu__%lu|Auth: %x|SKey: %lu|VAC: %x\n", serverchallenge, ourchallenge, authprotocol, steamkey_encryptionsize, vacsecured);

		char connectpkg[700];
		memset(connectpkg, 0, sizeof(connectpkg));

		bf_write writeconnect(connectpkg, sizeof(connectpkg));
		bf_read readsteamid(connectpkg, sizeof(connectpkg));

		writeconnect.WriteLong(-1);
		writeconnect.WriteByte('k');//C2S_CONNECT

		writeconnect.WriteLong(0x18);//protocol ver

		writeconnect.WriteLong(0x03);//auth protocol 0x03 = PROTOCOL_STEAM, 0x02 = PROTOCOL_HASHEDCDKEY, 0x01=PROTOCOL_AUTHCERTIFICATE
		writeconnect.WriteLong(serverchallenge);
		writeconnect.WriteLong(ourchallenge);

		writeconnect.WriteUBitLong(2729496039, 32);

		writeconnect.WriteString(nickname); //nick
		writeconnect.WriteString(password); // pass
		writeconnect.WriteString("2000"); // game version


		unsigned char steamkey[STEAM_KEYSIZE];
		unsigned int keysize = 0;

		steamuser->GetAuthSessionTicket(steamkey, STEAM_KEYSIZE, &keysize);

		CSteamID localsid = steamuser->GetSteamID();

		writeconnect.WriteShort(242);
		unsigned long long steamid64 = localsid.ConvertToUint64();
		writeconnect.WriteLongLong(steamid64);

		if (keysize)
			writeconnect.WriteBytes(steamkey, keysize);

		net.SendTo(ip, port, connectpkg, writeconnect.GetNumBytesWritten());


		return 0;

	}
	case 'B': // S2C_CONNECTION
	{

		if (bconnectstep == 2)
		{

			bconnectstep = 3;
			printf("Connected successfully\n");

			netchan->Initialize();



			senddata.WriteUBitLong(6, 6);
			senddata.WriteByte(2);
			senddata.WriteLong(-1);

			senddata.WriteUBitLong(4, 6);
			senddata.WriteString("VModEnable 1");
			senddata.WriteUBitLong(4, 6);
			senddata.WriteString("vban 0 0 0 0");

			/*
			senddata.WriteByte(31);
			for (int i = 0; i < 31; i++)
			{
			senddata.WriteString("gm_snapangles");
			senddata.WriteString("45");
			}s
			*/
			NET_SendDatagram();

			Sleep(3000);

		}


		return 0;
	}

	case 'I':
	{
		return 0;
	}
	default:
	{
		printf("Unknown message received from: %s, header: %i ( %c )\n", ip, header, header);
		break;
	}


	}
	return 0;
}