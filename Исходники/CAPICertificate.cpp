static void smartcard_check_status (SCARDCONTEXT hContext,
		const char* pReader,
		SCARDHANDLE hCardHandle, /* Can be 0 on the first call */
		SCARDHANDLE* newCardHandle, /* The handle returned */
		DWORD* pdwState) {
	DWORD shareMode = SCARD_SHARE_SHARED;
	DWORD preferredProtocols = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;
	DWORD dwAP;
	LONG result;

	if (hCardHandle == 0) {
		result = SCardConnect(hContext, pReader, shareMode, preferredProtocols, &hCardHandle, &dwAP);
		DEBUG_SCARD_STATUS("SCardConnect", result);
		if (SCARD_S_SUCCESS != result) {
			hCardHandle = 0;
		}
	}

	char szReader[200];
	DWORD cch = sizeof(szReader);
	BYTE bAttr[32];
	DWORD cByte = 32;
	size_t countStatusAttempts = 0;

	while (hCardHandle && (countStatusAttempts < 2)) {
		*pdwState = SCARD_UNKNOWN;

		result = SCardStatus(hCardHandle, /* Unfortunately we can't use NULL here */ szReader, &cch, pdwState, NULL, (LPBYTE)&bAttr, &cByte);
		DEBUG_SCARD_STATUS("SCardStatus", result);
		countStatusAttempts++;

		if ((SCARD_W_RESET_CARD == result) && (countStatusAttempts < 2)) {
			result = SCardReconnect(hCardHandle, shareMode, preferredProtocols, SCARD_RESET_CARD, &dwAP);
			DEBUG_SCARD_STATUS("SCardReconnect", result);
			if (SCARD_S_SUCCESS != result) {
				break;
			}
		}
		else {
			break;
		}
	}

	if (SCARD_S_SUCCESS != result) {
		if (SCARD_E_NO_SMARTCARD == result || SCARD_W_REMOVED_CARD == result) {
			*pdwState = SCARD_ABSENT;
		}
		else {
			*pdwState = SCARD_UNKNOWN;
		}
	}

	if (newCardHandle == NULL) {
		result = SCardDisconnect(hCardHandle, SCARD_LEAVE_CARD);
		DEBUG_SCARD_STATUS("SCardDisconnect", result);
	}
	else {
		*newCardHandle = hCardHandle;
	}
}