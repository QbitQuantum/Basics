void ControlServer(void *pvParameters) {

	char ServerBuffer[CONFIG_SERVER_BUFFER];
	char MsgBuffer[100];
	char *pMsgBuffer;

	SlSockAddrIn_t sAddr;
	SlSockAddrIn_t sLocalAddr;
	int32_t i32SockID;
	int32_t i32NewSockID;
	int32_t i32DataSize;
	int32_t i32NonBlocking = 1;
	SlSocklen_t i32AddrSize;
	int32_t retval;

	pMsgBuffer = &MsgBuffer[0];

	InitVariables();
	retval = ResetSimpleLink();
	if (retval < 0)
		while (1)
			;

	WlanConnect();

	sprintf(MsgBuffer, "Connectado a rede: %s\n\r"
			"IP: %d.%d.%d.%d\n\r"
			"Gateway: %d.%d.%d.%d\n\r", SL_IPV4_BYTE(g_sSLCon.DeviceIP, 3),
			SL_IPV4_BYTE(g_sSLCon.DeviceIP, 2),
			SL_IPV4_BYTE(g_sSLCon.DeviceIP, 1),
			SL_IPV4_BYTE(g_sSLCon.DeviceIP, 0),
			SL_IPV4_BYTE(g_sSLCon.GatewayIP, 3),
			SL_IPV4_BYTE(g_sSLCon.GatewayIP, 2),
			SL_IPV4_BYTE(g_sSLCon.GatewayIP, 1),
			SL_IPV4_BYTE(g_sSLCon.GatewayIP, 0));

	osi_MsgQWrite(&g_sUartQuee, &pMsgBuffer, OSI_NO_WAIT);

	sLocalAddr.sin_family = SL_AF_INET;
	sLocalAddr.sin_port = sl_Htons((unsigned short) g_sSLCon.PortNumber);
	sLocalAddr.sin_addr.s_addr = 0;

	i32SockID = sl_Socket(SL_AF_INET, SL_SOCK_STREAM, 0);
	sl_Bind(i32SockID, (SlSockAddr_t *) &sLocalAddr, sizeof(SlSockAddrIn_t));
	sl_Listen(i32SockID, 0);
	sl_SetSockOpt(i32SockID, SL_SOL_SOCKET, SL_SO_NONBLOCKING, &i32NonBlocking,
			sizeof(i32NonBlocking));

	while (1) {
		i32NewSockID = SL_EAGAIN;

		while (i32NewSockID < 0) {
			i32NewSockID = sl_Accept(i32SockID, (struct SlSockAddr_t *) &sAddr,
					(SlSocklen_t*) &i32AddrSize);
			if (i32NewSockID == SL_EAGAIN) {
				osi_Sleep(100);
			} else if (i32NewSockID < 0) {
				while (1) {
				}
			}
		}

		i32DataSize = sl_Recv(i32NewSockID, ServerBuffer, CONFIG_SERVER_BUFFER,
				0);

		if (strcmp(ServerBuffer, "Led On") == 0) {
			Led_Green(LED_ON);
			strcpy(ServerBuffer, "OK");
			i32DataSize = 3;
		} else if (strcmp(ServerBuffer, "Led Off") == 0) {
			Led_Green(LED_OFF);
			strcpy(ServerBuffer, "OK");
			i32DataSize = 3;
		} else if (strcmp(ServerBuffer, "Lamp On") == 0) {
			MAP_GPIOPinWrite(GPIOA0_BASE, GPIO_PIN_6, GPIO_PIN_6);
			strcpy(ServerBuffer, "OK");
			i32DataSize = 3;
		} else if (strcmp(ServerBuffer, "Lamp Off") == 0) {
			MAP_GPIOPinWrite(GPIOA0_BASE, GPIO_PIN_6, 0);
			strcpy(ServerBuffer, "OK");
			i32DataSize = 3;
		}

		sl_Send(i32NewSockID, ServerBuffer, i32DataSize, 0);
		sl_Close(i32NewSockID);
	}

}