void CGnuLocal::Init()
{
	if(!Create(UDP_PORT, SOCK_DGRAM))
	{
		return;
	}

	if(!SetSockOpt(SO_BROADCAST, &m_Broadcasted, sizeof(int)))
	{
		return;
	}
}