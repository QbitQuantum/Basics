bool WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	SimpleCommand msg;
	msg.cmd = Cmds::endServer;
	sf::Packet endPacket;
	endPacket << msg.cmd << msg.winner;
	localPlayer->send(endPacket);
	return dwCtrlType == CTRL_CLOSE_EVENT;
}