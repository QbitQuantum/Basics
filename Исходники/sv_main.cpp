/*
================
cInfo

Responds with short info for broadcast scans
The second parameter should be the current protocol version number.
================
*/
static void cInfo(int argc, char **argv)
{
	if (sv_maxclients->integer == 1 || sv.state == ss_demo || sv.attractloop)
		return;					// ignore in single player or demoplay

	int version = atoi(argv[1]);

	if (!version)
	{
		// we should reject this packet -- this is our "info" answer to local client (loopback packet)
		Com_DPrintf("rejected \"info\" answer\n");
		return;
	}

	TString<64> Str;
	if (version != PROTOCOL_VERSION)
		Str.sprintf("%s: wrong version %d\n", hostname->string, version);
	else
	{
		int count = 0;
		for (int i = 0; i < sv_maxclients->integer; i++)
			if (svs.clients[i].state >= cs_connected)
				count++;

		Str.sprintf("%16s %8s %2d/%2d\n", hostname->string, sv.name, count, sv_maxclients->integer);
	}
	Netchan_OutOfBandPrint(NS_SERVER, net_from, "info\n%s", *Str);
}