static LONG SCR_SCardPIN(long lAction, LPCTSTR szPinPadDll, const SCR_Card * pCard, BYTE pinID,
			 const SCR_PinUsage * pUsage, const SCR_Application * pApp,
			 BYTE * pCardStatus)
{
	LONG rv;
	unsigned char sendbuf[256];
	unsigned char recvbuf[2];
	char szTemp[32];
	DWORD dwRecvLength;
	struct tTLV tlv;

	memset(szTemp, 0, sizeof(szTemp));
	memset(recvbuf, 0, sizeof(recvbuf));
	dwRecvLength = sizeof(recvbuf);

	/* Make TLV buffer */
	TLVInit(&tlv, sendbuf, sizeof(sendbuf));
	TLVNext(&tlv, 0x01);	/* Function ID */
	sprintf(szTemp, "%ld", lAction);
	TLVAddBuffer(&tlv, (u8 *) szTemp, strlen(szTemp));
	TLVNext(&tlv, 0x02);	/* PinPad Dll */
	TLVAddBuffer(&tlv, (u8 *) szPinPadDll, strlen(szPinPadDll));
	TLVNext(&tlv, 0x03);	/* SCR_Card Handle */
	sprintf(szTemp, "%ld", pCard->hCard);
	TLVAddBuffer(&tlv, (u8 *) szTemp, strlen(szTemp));
	if (pCard->language != NULL) {
		TLVNext(&tlv, 0x04);	/* SCR_Card language */
		TLVAddBuffer(&tlv, (u8 *) pCard->language, strlen(pCard->language));
	}
	if (pCard->id.data != NULL) {
		TLVNext(&tlv, 0x05);	/* SCR_Card id */
		TLVAddBuffer(&tlv, pCard->id.data, pCard->id.length);
	}
	TLVNext(&tlv, 0x06);	/* PinID */
	TLVAdd(&tlv, pinID);
	if (pUsage != NULL) {
		TLVNext(&tlv, 0x07);	/* SCR_PinUsage code */
		sprintf(szTemp, "%ld", pUsage->code);
		TLVAddBuffer(&tlv, (u8 *) szTemp, strlen(szTemp));
		if (pUsage->shortString != NULL) {
			TLVNext(&tlv, 0x08);	/* SCR_PinUsage shortstring */
			TLVAddBuffer(&tlv, (u8 *) pUsage->shortString, strlen(pUsage->shortString));
		}
		if (pUsage->longString != NULL) {
			TLVNext(&tlv, 0x09);	/* SCR_PinUsage longstring */
			TLVAddBuffer(&tlv, (u8 *) pUsage->longString, strlen(pUsage->longString));
		}
	}
	if (pApp->id.data != NULL) {
		TLVNext(&tlv, 0x0A);	/* SCR_Application id */
		TLVAddBuffer(&tlv, (u8 *) pApp->id.data, pApp->id.length);
	}
	if (pApp->shortString != NULL) {
		TLVNext(&tlv, 0x0B);	/* SCR_Application shortstring */
		TLVAddBuffer(&tlv, (u8 *) pApp->shortString, strlen(pApp->shortString));
	}
	if (pApp->longString != NULL) {
		TLVNext(&tlv, 0x0C);	/* SCR_Application longstring */
		TLVAddBuffer(&tlv, (u8 *) pApp->longString, strlen(pApp->longString));
	}
#ifdef HAVE_PCSC_OLD
	rv = SCardControl(SCR_CARD_HANDLE, sendbuf, TLVLen(&tlv), recvbuf, &dwRecvLength);
#else
	rv = SCardControl(SCR_CARD_HANDLE, 0, sendbuf, TLVLen(&tlv),
			  recvbuf, dwRecvLength, &dwRecvLength);
#endif
	if (dwRecvLength < 2) {
		rv = SC_ERROR_UNKNOWN_DATA_RECEIVED;
	} else {
		memcpy(pCardStatus, recvbuf, 2);
	}

	return rv;
}