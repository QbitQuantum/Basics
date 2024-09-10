int CIPMessage::RecMessagePort(HWND hw, int id)
{

	char acRetData[4096];
	int iStat = 0;

	iStat = recv(conn, acRetData, 4096, 0);
	if (iStat == -1)
		return 1;
	//in = acRetData;
	// cout이 아니라 텍스박스 보낼 메세지
	//cout << "-->" << acRetData << "\n";
	Puts(hw, id, acRetData);
	return 0;

}