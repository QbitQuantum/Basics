/****************************************************************************
 *
 * NAME: vHandleSerialInput
 *
 * DESCRIPTION:
 *
 * PARAMETERS:      Name            RW  Usage
 *
 * RETURNS:
 *
 * NOTES:
 ****************************************************************************/
PRIVATE void vHandleSerialInput() {
	// handle UART command
	while (!SERIAL_bRxQueueEmpty(sSerPort.u8SerialPort)) {
		int16 i16Char;

		i16Char = SERIAL_i16RxChar(sSerPort.u8SerialPort);

		// process
		if (i16Char >=0 && i16Char <= 0xFF) {
			uint8 u8res = u8ParseSerCmd(&sSerCmd, (uint8)i16Char);
			if (u8res == E_SERCMD_VERBOSE) {
				vfPrintf(&sSerStream, "\n\rVERBOSE MODE = %s", bSerCmd_VerboseMode ? "ON" : "OFF");
				continue;
			}
			if (!bSerCmd_VerboseMode) continue;

			switch (i16Char) {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				sAppData.sFlash.sData.u8Layer = i16Char - '0';
				if (bFlash_Write(&sAppData.sFlash, FLASH_SECTOR_NUMBER - 1, 0)) {
					V_PRINTF( LB "Flash Saved (Router Layer #%d)... RESETTING", sAppData.sFlash.sData.u8Layer);
					vWait(100000);
					vAHI_SwReset();
				} else {
					V_PRINTF( LB "Failed to save flash...");
				}
				break;

			case 'i': // info
				_C {
					tsToCoNet_NwkLyTr_Context *pc = (tsToCoNet_NwkLyTr_Context *)(sAppData.pContextNwk);

					V_PRINTF( LB "Info: la=%d ty=%d ro=%02x st=%02x",
							pc->sInfo.u8Layer, pc->sInfo.u8NwkTypeId, pc->sInfo.u8Role, pc->sInfo.u8State);
					V_PRINTF( LB "Parent: %08x", pc->u32AddrHigherLayer);
					V_PRINTF( LB "LostParent: %d", pc->u8Ct_LostParent);
					V_PRINTF( LB "SecRescan: %d, SecRelocate: %d", pc->u8Ct_Second_To_Rescan, pc->u8Ct_Second_To_Relocate);
				}
				break;

			case '>':
				sToCoNet_AppContext.u8Channel++;
				if (sToCoNet_AppContext.u8Channel > 25)
					sToCoNet_AppContext.u8Channel = 0;
				ToCoNet_vRfConfig();
				V_PRINTF( LB"channel set to %d.", sToCoNet_AppContext.u8Channel);
				break;

			case '<':
				sToCoNet_AppContext.u8Channel--;
				if (sToCoNet_AppContext.u8Channel < 11)
					sToCoNet_AppContext.u8Channel = 25;
				ToCoNet_vRfConfig();
				V_PRINTF( LB"channel set to %d.", sToCoNet_AppContext.u8Channel);
				break;

			case 't':
				SPRINTF_vRewind();
				vfPrintf(SPRINTF_Stream, "TEST FROM ROUTER(#%08X)", ToCoNet_u32GetSerial());
				bTransmitToParent(sAppData.pContextNwk, SPRINTF_pu8GetBuff(), SPRINTF_u16Length());
				break;

			case 'd': case 'D':
				_C {
					static uint8 u8DgbLvl;

					u8DgbLvl++;
					if(u8DgbLvl > 10) u8DgbLvl = 0;
					ToCoNet_vDebugLevel(u8DgbLvl);

					V_PRINTF( LB"set NwkCode debug level to %d.", u8DgbLvl);
				}
				break;

			default:
				break;
			}
		}
	}