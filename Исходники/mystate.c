static int sendIdentityPacket()
{
	int nameLen = strlen(userName);
	if (startMode%3 == 2)	/* 赛尔 */
	{
		if (sendCount == 0)
		{
			printf(_(">> 发送用户名...\n"));
			*(u_int16_t *)(sendPacket+0x0E) = htons(0x0100);
			*(u_int16_t *)(sendPacket+0x10) = *(u_int16_t *)(sendPacket+0x14) = htons(nameLen+30);
			sendPacket[0x12] = 0x02;
			sendPacket[0x16] = 0x01;
			sendPacket[0x17] = 0x01;
			fillCernetAddr(sendPacket);
			memcpy(sendPacket+0x28, "03.02.05", 8);
			memcpy(sendPacket+0x30, userName, nameLen);
			setTimer(timeout);
		}
		sendPacket[0x13] = capBuf[0x13];
		return pcap_sendpacket(hPcap, sendPacket, nameLen+48);
	}
	if (sendCount == 0)
	{
		printf(_(">> 发送用户名...\n"));
		fillEtherAddr(0x888E0100);
		nameLen = strlen(userName);
		*(u_int16_t *)(sendPacket+0x14) = *(u_int16_t *)(sendPacket+0x10) = htons(nameLen+5);
		sendPacket[0x12] = 0x02;
		sendPacket[0x13] = capBuf[0x13];
		sendPacket[0x16] = 0x01;
		memcpy(sendPacket+0x17, userName, nameLen);
		memcpy(sendPacket+0x17+nameLen, pkt2, sizeof(pkt2));
                memcpy(sendPacket + 0xe7 + nameLen, computeV4(pad, 16), 0x80);
		setTimer(timeout);
	}
	return pcap_sendpacket(hPcap, sendPacket, 545);
}