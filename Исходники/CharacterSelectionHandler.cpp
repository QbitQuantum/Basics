void CUser::RecvDeleteChar(Packet & pkt)
{
	Packet result;
	std::string strCharID;
	int16 sKnights;
	uint8 bResult, bCharIndex;
	pkt >> bResult >> bCharIndex >> sKnights >> strCharID;

	if (bResult == 1 && sKnights != 0)
	{
		// TO-DO: Synchronise this system better. Much better. This is dumb.
		g_pMain->m_KnightsManager.RemoveKnightsUser(sKnights, (char *)strCharID.c_str());
		result.SetOpcode(UDP_KNIGHTS_PROCESS);
		result << uint8(KNIGHTS_WITHDRAW) << sKnights << strCharID;
		g_pMain->Send_UDP_All(&result, g_pMain->m_nServerGroup == 0 ? 0 : 1);
	}


	result.Initialize(WIZ_DEL_CHAR);
	result << bResult << bCharIndex;
	Send(&result);
}