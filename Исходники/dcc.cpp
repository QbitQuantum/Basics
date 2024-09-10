void CDCCSock::Connected() {
	DEBUG(GetSockName() << " == Connected(" << GetRemoteIP() << ")");
	m_pModule->PutModule(((m_bSend) ? "DCC -> [" : "DCC <- [") + m_sRemoteNick + "][" + m_sFileName + "] - Transfer Started.");

	if (m_bSend) {
		SendPacket();
	}

	SetTimeout(120);
}