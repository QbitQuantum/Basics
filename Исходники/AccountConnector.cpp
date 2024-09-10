bool CAccountConnector::__AuthState_RecvChinaMatrixCard()
{
	TPacketGCChinaMatrixCard kMatrixCardPacket;
	if (!Recv(sizeof(TPacketGCChinaMatrixCard), &kMatrixCardPacket))
		return false;

	if (m_poHandler)
	{
		PyObject * pyValue = Py_BuildValue("(iiiiiiii)",	ROW(kMatrixCardPacket.dwRows, 0),
															ROW(kMatrixCardPacket.dwRows, 1),
															ROW(kMatrixCardPacket.dwRows, 2),
															ROW(kMatrixCardPacket.dwRows, 3),
															COL(kMatrixCardPacket.dwCols, 0),
															COL(kMatrixCardPacket.dwCols, 1),
															COL(kMatrixCardPacket.dwCols, 2),
															COL(kMatrixCardPacket.dwCols, 3));
		PyCallClassMemberFunc(m_poHandler, "OnMatrixCard", pyValue);
	}

	return true;
}