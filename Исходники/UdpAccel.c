// Create a new UDP acceleration function
UDP_ACCEL *NewUdpAccel(CEDAR *cedar, IP *ip, bool client_mode, bool random_port, bool no_nat_t)
{
	UDP_ACCEL *a;
	SOCK *s;
	UINT max_udp_size;
	bool is_in_cedar_port_list = false;

	if (IsZeroIP(ip))
	{
		ip = NULL;
	}

	if (client_mode || random_port)
	{
		// Use a appropriate vacant port number in the case of using random port or client mode
		s = NewUDPEx3(0, ip);
	}
	else
	{
		// Specify in the range in the case of server mode
		UINT i;
		s = NULL;

		LockList(cedar->UdpPortList);
		{
			for (i = UDP_SERVER_PORT_LOWER;i <= UDP_SERVER_PORT_HIGHER;i++)
			{
				if (IsIntInList(cedar->UdpPortList, i) == false)
				{
					s = NewUDPEx3(i, ip);

					if (s != NULL)
					{
						is_in_cedar_port_list = true;
						break;
					}
				}
			}

			if (s == NULL)
			{
				// Leave the port selection to the OS because the available port is not found within the range
				s = NewUDPEx3(0, ip);
			}

			if (s != NULL && is_in_cedar_port_list)
			{
				AddIntDistinct(cedar->UdpPortList, i);
			}
		}
		UnlockList(cedar->UdpPortList);
	}

	if (s == NULL)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(UDP_ACCEL));

	a->Cedar = cedar;
	AddRef(a->Cedar->ref);

	a->NoNatT = no_nat_t;


	a->NatT_TranId = Rand64();

	a->CreatedTick = Tick64();

	a->IsInCedarPortList = is_in_cedar_port_list;

	a->ClientMode = client_mode;

	a->Now = Tick64();
	a->UdpSock = s;
	Rand(a->MyKey, sizeof(a->MyKey));
	Rand(a->YourKey, sizeof(a->YourKey));

	Copy(&a->MyIp, ip, sizeof(IP));
	a->MyPort = s->LocalPort;

	a->IsIPv6 = IsIP6(ip);

	a->RecvBlockQueue = NewQueue();

	Rand(a->NextIv, sizeof(a->NextIv));

	do
	{
		a->MyCookie = Rand32();
	}
	while (a->MyCookie == 0);

	do
	{
		a->YourCookie = Rand32();
	}
	while (a->MyCookie == 0 || a->MyCookie == a->YourCookie);

	// Calculate the maximum transmittable UDP packet size
	max_udp_size = MTU_FOR_PPPOE;

	if (a->IsIPv6 == false)
	{
		// IPv4
		max_udp_size -= 20;
	}
	else
	{
		// IPv6
		max_udp_size -= 40;
	}

	// UDP
	max_udp_size -= 8;

	a->MaxUdpPacketSize = max_udp_size;

	Debug("Udp Accel My Port = %u\n", a->MyPort);

	// Initialize the NAT-T server IP address acquisition thread
	a->NatT_Lock = NewLock();
	a->NatT_HaltEvent = NewEvent();

	if (a->NoNatT == false)
	{
		a->NatT_GetIpThread = NewThread(NatT_GetIpThread, a);
	}

	return a;
}