// Отправка файлов
DWORD CMraProto::MraGame(const CMStringA &szEmail, DWORD dwGameSessionID, DWORD dwGameMsg, DWORD dwGameMsgID, const CMStringA &szData)
{
	if (szEmail.GetLength() <= 4)
		return 0;

	OutBuffer buf;
	buf.SetLPSLowerCase(szEmail);
	buf.SetUL(dwGameSessionID);
	buf.SetUL(dwGameMsg);
	buf.SetUL(dwGameMsgID);
	buf.SetUL(_time32(NULL));
	buf.SetLPS(szData);
	return MraSendCMD(MRIM_CS_GAME, buf.Data(), buf.Len());
}