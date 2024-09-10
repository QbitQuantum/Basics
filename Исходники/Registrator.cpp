STDMETHODIMP CRegistrator::Fiscalization(BSTR FirmID, LONG OldPassword, LONG NewPassword, ULONGLONG MachineRegNum, ULONGLONG TaxpayerIndNum, LONG* ErrorCode)
{
	*ErrorCode = E_SUCCESS;
	CRegistratorInfo* regInfo = m_RegistratorList.GetInfo(FirmID);
	if(!regInfo)
	{
		*ErrorCode = E_NOT_FOUND;
		return S_OK;
	}

	BYTE nSentMessage[MESSAGE_SIZE], nReceivedMessage[MESSAGE_SIZE];
	DWORD dwMessageLen = 0;
	CHAR lpStr[13];

	// формируем текст команды
	memset(nSentMessage, 0, MESSAGE_SIZE);

	// текущий пароль
	memset(lpStr, 0, 13);
	_itoa(OldPassword, lpStr, 10);
	memcpy(nSentMessage + dwMessageLen, lpStr, strlen(lpStr));
	dwMessageLen += (DWORD)strlen(lpStr);
	nSentMessage[dwMessageLen++] = FS;

	// регистрационный номер ККМ
	memset(lpStr, 0, 13);
	_ui64toa(MachineRegNum, lpStr, 10);
	memcpy(nSentMessage + dwMessageLen, lpStr, strlen(lpStr));
	dwMessageLen += (DWORD)strlen(lpStr);
	nSentMessage[dwMessageLen++] = FS;

	// ИНН
	memset(lpStr, 0, 13);
	_ui64toa(TaxpayerIndNum, lpStr, 10);
	memcpy(nSentMessage + dwMessageLen, lpStr, strlen(lpStr));
	dwMessageLen += (DWORD)strlen(lpStr);
	nSentMessage[dwMessageLen++] = FS;

	// новый пароль
	memset(lpStr, 0, 13);
	_itoa(NewPassword, lpStr, 10);
	memcpy(nSentMessage + dwMessageLen, lpStr, strlen(lpStr));
	dwMessageLen += (DWORD)strlen(lpStr);

	PassCommand(regInfo->hCommPort, (LPBYTE) "08", nSentMessage, dwMessageLen, nReceivedMessage, ErrorCode);

	return CheckPaperStatus(regInfo, ErrorCode);
}