/*
 * @brief A connection request that did not come from the master.
 */
static void Sv_Connect_f(void) {
	char user_info[MAX_USER_INFO_STRING];
	sv_client_t *cl, *client;
	int32_t i;

	Com_Debug("Svc_Connect()\n");

	net_addr_t *addr = &net_from;

	const int32_t version = strtol(Cmd_Argv(1), NULL, 0);

	// resolve protocol
	if (version != PROTOCOL_MAJOR) {
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nServer is version %d.\n",
		PROTOCOL_MAJOR);
		return;
	}

	const uint8_t qport = strtoul(Cmd_Argv(2), NULL, 0);

	const uint32_t challenge = strtoul(Cmd_Argv(3), NULL, 0);

	// copy user_info, leave room for ip stuffing
	g_strlcpy(user_info, Cmd_Argv(4), sizeof(user_info) - 25);

	if (*user_info == '\0') { // catch empty user_info
		Com_Print("Empty user_info from %s\n", Net_NetaddrToString(addr));
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nConnection refused\n");
		return;
	}

	if (strchr(user_info, '\xFF')) { // catch end of message in string exploit
		Com_Print("Illegal user_info contained xFF from %s\n", Net_NetaddrToString(addr));
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nConnection refused\n");
		return;
	}

	if (strlen(GetUserInfo(user_info, "ip"))) { // catch spoofed ips
		Com_Print("Illegal user_info contained ip from %s\n", Net_NetaddrToString(addr));
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nConnection refused\n");
		return;
	}

	if (!ValidateUserInfo(user_info)) { // catch otherwise invalid user_info
		Com_Print("Invalid user_info from %s\n", Net_NetaddrToString(addr));
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nConnection refused\n");
		return;
	}

	// force the ip so the game can filter on it
	SetUserInfo(user_info, "ip", Net_NetaddrToString(addr));

	// enforce a valid challenge to avoid denial of service attack
	for (i = 0; i < MAX_CHALLENGES; i++) {
		if (Net_CompareClientNetaddr(addr, &svs.challenges[i].addr)) {
			if (challenge == svs.challenges[i].challenge) {
				svs.challenges[i].challenge = 0;
				break; // good
			}
			Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nBad challenge\n");
			return;
		}
	}
	if (i == MAX_CHALLENGES) {
		Com_Print("Connection without challenge from %s\n", Net_NetaddrToString(addr));
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nNo challenge for address\n");
		return;
	}

	// resolve the client slot
	client = NULL;

	// first check for an ungraceful reconnect (client crashed, perhaps)
	for (i = 0, cl = svs.clients; i < sv_max_clients->integer; i++, cl++) {

		const net_chan_t *ch = &cl->net_chan;

		if (cl->state == SV_CLIENT_FREE) // not in use, not interested
			continue;

		// the base address and either the qport or real port must match
		if (Net_CompareClientNetaddr(addr, &ch->remote_address)) {

			if (addr->port == ch->remote_address.port || qport == ch->qport) {
				client = cl;
				break;
			}
		}
	}

	// otherwise, treat as a fresh connect to a new slot
	if (!client) {
		for (i = 0, cl = svs.clients; i < sv_max_clients->integer; i++, cl++) {
			if (cl->state == SV_CLIENT_FREE && !cl->entity->ai) { // we have a free one
				client = cl;
				break;
			}
		}
	}

	// no soup for you, next!!
	if (!client) {
		Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nServer is full\n");
		Com_Debug("Rejected a connection\n");
		return;
	}

	// give the game a chance to reject this connection or modify the user_info
	if (!(svs.game->ClientConnect(client->entity, user_info))) {
		const char *rejmsg = GetUserInfo(user_info, "rejmsg");

		if (strlen(rejmsg)) {
			Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\n%s\nConnection refused\n", rejmsg);
		} else {
			Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "print\nConnection refused\n");
		}

		Com_Debug("Game rejected a connection\n");
		return;
	}

	// parse some info from the info strings
	g_strlcpy(client->user_info, user_info, sizeof(client->user_info));
	Sv_UserInfoChanged(client);

	// send the connect packet to the client
	Netchan_OutOfBandPrint(NS_UDP_SERVER, addr, "client_connect %s", sv_download_url->string);

	Netchan_Setup(NS_UDP_SERVER, &client->net_chan, addr, qport);

	Mem_InitBuffer(&client->datagram.buffer, client->datagram.data, sizeof(client->datagram.data));
	client->datagram.buffer.allow_overflow = true;

	client->last_message = quetoo.time;

	client->state = SV_CLIENT_CONNECTED;
}