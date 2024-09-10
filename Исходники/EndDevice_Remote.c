/****************************************************************************
 *
 * NAME: cbToCoNet_vNwkEvent
 *
 * DESCRIPTION:
 *
 * PARAMETERS:      Name            RW  Usage
 *
 * RETURNS:
 *
 * NOTES:
 ****************************************************************************/
void cbToCoNet_vNwkEvent(teEvent eEvent, uint32 u32arg) {
	switch(eEvent) {
	/*
	 * ネットワークが開始された
	 */
	case E_EVENT_TOCONET_NWK_START:
		V_PRINTF(LB"[E_EVENT_TOCONET_NWK_START:%d,Ch:%d]", u32TickCount_ms & 0xFFFF, sToCoNet_AppContext.u8Channel);
		vDispInfo(&sSerStream, (void*)sAppData.pContextNwk);

		// pass this event to the event machine
		ToCoNet_Event_Process(E_EVENT_TOCONET_NWK_START, u32arg, vProcessEvCore);
		break;

	/*
	 * ネットワークが切断された
	 */
	case E_EVENT_TOCONET_NWK_DISCONNECT:
		V_PRINTF(LB"[E_EVENT_TOCONET_NWK_DISCONNECT]");

		// pass this event to the event machine
		ToCoNet_Event_Process(E_EVENT_TOCONET_NWK_DISCONNECT, u32arg, vProcessEvCore);
		break;

	/*
	 * メッセージプールを受信
	 */
	case E_EVENT_TOCONET_NWK_MESSAGE_POOL:
		if (u32arg) {
			tsToCoNet_MsgPl_Entity *pInfo = (void*)u32arg;
			int i;
			//static uint8 u8seq = 0;

			uint8 u8buff[TOCONET_MOD_MESSAGE_POOL_MAX_MESSAGE+1];
			memcpy(u8buff, pInfo->au8Message, pInfo->u8MessageLen); // u8Message にデータ u8MessageLen にデータ長
			u8buff[pInfo->u8MessageLen] = 0;

			// UART にメッセージ出力
			if (pInfo->bGotData) { // empty なら FALSE になる
				V_PRINTF(LB"---MSGPOOL sl=%d ln=%d msg=",
						pInfo->u8Slot,
						pInfo->u8MessageLen
						);

				SPRINTF_vRewind();
				for (i = 0; i < pInfo->u8MessageLen; i++) {
					vfPrintf(SPRINTF_Stream, "%02X", u8buff[i]);
				}
				V_PRINTF("%s", SPRINTF_pu8GetBuff());

#ifdef USE_LCD
				V_PRINTF_LCD("%02x:%s\r\n", u8seq++, SPRINTF_pu8GetBuff());
				vLcdRefresh();
#endif

				V_PRINTF("---");
			} else {
				V_PRINTF(LB"---MSGPOOL sl=%d EMPTY ---",
						pInfo->u8Slot
						);
#ifdef USE_LCD
				V_PRINTF_LCD("%02x: EMPTY\r\n", u8seq++);
				vLcdRefresh();
#endif
			}

			ToCoNet_Event_Process(E_EVENT_APP_GET_IC_INFO, pInfo->bGotData, vProcessEvCore); // vProcessEvCore にイベント送信
		}
		break;

	default:
		break;
	}
}