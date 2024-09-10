/*********************************************************************//**
 * @brief		c_entry: Main CAN program body
 * @param[in]	none
 * @return 		int
 **********************************************************************/
int c_entry(void) { /* Main Program */
	uint32_t i;
	uint32_t cnt;
	CAN_ERROR error;
	PINSEL_CFG_Type PinCfg;

	/* Initialize debug via UART0
	 * – 115200bps
	 * – 8 data bit
	 * – No parity
	 * – 1 stop bit
	 * – No flow control
	 */
	debug_frmwrk_init();
	print_menu();

	/* Pin configuration
	 * CAN1: select P0.0 as RD1. P0.1 as TD1
	 * CAN2: select P2.7 as RD2, P2.8 as RD2
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 0;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);

	PinCfg.Pinnum = 7;
	PinCfg.Portnum = 2;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);

	//Initialize CAN1 & CAN2
	CAN_Init(LPC_CAN1, 125000);
	CAN_Init(LPC_CAN2, 125000);

	//Enable Receive Interrupt
	CAN_IRQCmd(LPC_CAN2, CANINT_FCE, ENABLE);
	CAN_IRQCmd(LPC_CAN2, CANINT_RIE, ENABLE);

	//Enable CAN Interrupt
	NVIC_EnableIRQ(CAN_IRQn);

	/* First, we send 10 messages:
	 * - message 0,2,4,6,8 have id in AFLUT >>> will be received
	 * - message 1,3,5,7,9 don't have id in AFLUT >>> will be ignored
	 * Then, we change AFLUT by load/remove entries in AFLUT and re-send messages
	 * - message 1,3,5,7,9 have id in AFLUT >>> will be received
	 * - message 0,2,4,6,8 don't have id in AFLUT >>> will be ignored
	 * Note that: FullCAN Object must be read from FullCAN Object Section next to AFLUT
	 */
	/*-------------------------Init Message & AF Look-up Table------------------------*/

	_DBG_("Test Acceptance Filter function...");
	_DBG_("Press '1' to initialize message and AF Loop-up Table...");_DBG_("");
	while(_DG !='1');
	CAN_InitAFMessage(); /* initialize Transmit Message */
	_DBG_("Init message finished!!!");
	CAN_SetupAFTable(); /* initialize AF Look-up Table sections*/
	error = CAN_SetupAFLUT(LPC_CANAF,&AFTable); /* install AF Look-up Table */
	if (error != CAN_OK) {
		_DBG_("Setup AF: ERROR...");
		while (1); // AF Table has error
	}
	else _DBG_("Setup AF: SUCCESSFUL!!!");_DBG_("");


	/*-------------------------Send messages------------------------*/
	_DBG_("Press '2' to start CAN transferring operation...");_DBG_("");
	while(_DG !='2');
	for (i = 0; i < CAN_TX_MSG_CNT; i++) {
		CAN_SendMsg(LPC_CAN1, &AFTxMsg[i]);
		PrintMessage(&AFTxMsg[i]);_DBG_("");
		for(cnt=0;cnt<10000;cnt++); //transmit delay
		CANTxCount++;
	}
	_DBG_("Sending finished !!!");

	/*-------------------------Display Received messages------------------------*/
	_DBG_("Press '3' to display received messages...");_DBG_("");
	while(_DG !='3');
	for (i = 0; i < CAN_RX_MSG_CNT; i++) {
		PrintMessage(&AFRxMsg[i]);_DBG_("");
	}

	/*-------------------------Change AFLUT Table --------------------*/
	_DBG_("Press '4' to change AF look-up table...");_DBG_("");
	while(_DG !='4');
	CAN_ChangeAFTable();
	_DBG_("Change AFLUT: FINISHED!!!");
	CAN_SetAFMode(LPC_CANAF, CAN_eFCAN);
	CAN_InitAFMessage();
	CANRxCount = CANTxCount = 0;

	/*-------------------------Re-Send messages------------------------*/
	_DBG_("Press '5' to re-send messages...");_DBG_("");
	while(_DG !='5');
	for (i = 0; i < CAN_TX_MSG_CNT; i++) {
		CAN_SendMsg(LPC_CAN1, &AFTxMsg[i]);
		PrintMessage(&AFTxMsg[i]);_DBG_("");
		for(cnt=0;cnt<10000;cnt++); //transmit delay
		CANTxCount++;
	}

	/*-------------------------Display received messages------------------------*/
	_DBG_("Re-Sending finished !!!");

	_DBG_("Press '6' to display received messages...");_DBG_("");
	while(_DG !='6');
	for (i = 0; i < CAN_RX_MSG_CNT; i++) {
		PrintMessage(&AFRxMsg[i]);_DBG_("");
	}
	_DBG_("Demo terminal !!!");

	CAN_DeInit(LPC_CAN1);
	CAN_DeInit(LPC_CAN2);
	while (1);
	return 0;
}