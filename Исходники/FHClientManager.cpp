void FHClientManager::InitMachineInfo()
{
	if (NULL != m_pcConnectSocket) {
		FHMessage cMsg;
		cMsg.SetCommandID(FH_COMM_MACHINEINFO);
		cMsg.SetMachineInfo(FH_MSG_MachineInfo(GetHostName()));
		m_pcConnectSocket->SendMessage(cMsg);
	}
}