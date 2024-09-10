static bool
Send_Message(CLIENT * Client, REQUEST * Req, int ForceType, bool SendErrors)
{
	CLIENT *cl, *from;
	CL2CHAN *cl2chan;
	CHANNEL *chan;
	char *currentTarget = Req->argv[0];
	char *lastCurrentTarget = NULL;
	char *message = NULL;

	assert(Client != NULL);
	assert(Req != NULL);

	if (Req->argc == 0) {
		if (!SendErrors)
			return CONNECTED;
		return IRC_WriteStrClient(Client, ERR_NORECIPIENT_MSG,
					  Client_ID(Client), Req->command);
	}
	if (Req->argc == 1) {
		if (!SendErrors)
			return CONNECTED;
		return IRC_WriteStrClient(Client, ERR_NOTEXTTOSEND_MSG,
					  Client_ID(Client));
	}
	if (Req->argc > 2) {
		if (!SendErrors)
			return CONNECTED;
		return IRC_WriteStrClient(Client, ERR_NEEDMOREPARAMS_MSG,
					  Client_ID(Client), Req->command);
	}

	if (Client_Type(Client) == CLIENT_SERVER)
		from = Client_Search(Req->prefix);
	else
		from = Client;
	if (!from)
		return IRC_WriteStrClient(Client, ERR_NOSUCHNICK_MSG,
					  Client_ID(Client), Req->prefix);

#ifdef ICONV
	if (Client_Conn(Client) > NONE)
		message = Conn_EncodingFrom(Client_Conn(Client), Req->argv[1]);
	else
#endif
		message = Req->argv[1];

	/* handle msgtarget = msgto *("," msgto) */
	currentTarget = strtok_r(currentTarget, ",", &lastCurrentTarget);
	ngt_UpperStr(Req->command);

	while (currentTarget) {
		/* Check for and handle valid <msgto> of form:
		 * RFC 2812 2.3.1:
		 *   msgto =  channel / ( user [ "%" host ] "@" servername )
		 *   msgto =/ ( user "%" host ) / targetmask
		 *   msgto =/ nickname / ( nickname "!" user "@" host )
		 */
		if (strchr(currentTarget, '!') == NULL)
			/* nickname */
			cl = Client_Search(currentTarget);
		else
			cl = NULL;

		if (cl == NULL) {
			/* If currentTarget isn't a nickname check for:
			 * user ["%" host] "@" servername
			 * user "%" host
			 * nickname "!" user "@" host
			 */
			char target[COMMAND_LEN];
			char * nick = NULL;
			char * user = NULL;
			char * host = NULL;
			char * server = NULL;

			strlcpy(target, currentTarget, COMMAND_LEN);
			server = strchr(target, '@');
			if (server) {
				*server = '\0';
				server++;
			}
			host = strchr(target, '%');
			if (host) {
				*host = '\0';
				host++;
			}
			user = strchr(target, '!');
			if (user) {
				/* msgto form: nick!user@host */
				*user = '******';
				user++;
				nick = target;
				host = server; /* not "@server" but "@host" */
			} else {
				user = target;
			}

			for (cl = Client_First(); cl != NULL; cl = Client_Next(cl)) {
				if (Client_Type(cl) != CLIENT_USER &&
				    Client_Type(cl) != CLIENT_SERVICE)
					continue;
				if (nick != NULL && host != NULL) {
					if (strcasecmp(nick, Client_ID(cl)) == 0 &&
					    strcasecmp(user, Client_User(cl)) == 0 &&
					    strcasecmp(host, Client_HostnameCloaked(cl)) == 0)
						break;
					else
						continue;
				}
				if (strcasecmp(user, Client_User(cl)) != 0)
					continue;
				if (host != NULL && strcasecmp(host,
						Client_HostnameCloaked(cl)) != 0)
					continue;
				if (server != NULL && strcasecmp(server,
						Client_ID(Client_Introducer(cl))) != 0)
					continue;
				break;
			}
		}

		if (cl) {
			/* Target is a user, enforce type */
#ifndef STRICT_RFC
			if (Client_Type(cl) != ForceType &&
			    !(ForceType == CLIENT_USER &&
			      (Client_Type(cl) == CLIENT_USER ||
			       Client_Type(cl) == CLIENT_SERVICE))) {
#else
			if (Client_Type(cl) != ForceType) {
#endif
				if (SendErrors && !IRC_WriteStrClient(
				    from, ERR_NOSUCHNICK_MSG,Client_ID(from),
				    currentTarget))
					return DISCONNECTED;
				goto send_next_target;
			}

#ifndef STRICT_RFC
			if (ForceType == CLIENT_SERVICE &&
			    (Conn_Options(Client_Conn(Client_NextHop(cl)))
			     & CONN_RFC1459)) {
				/* SQUERY command but RFC 1459 link: convert
				 * request to PRIVMSG command */
				Req->command = "PRIVMSG";
			}
#endif
			if (Client_HasMode(cl, 'b') &&
			    !Client_HasMode(from, 'R') &&
			    !Client_HasMode(from, 'o') &&
			    !(Client_Type(from) == CLIENT_SERVER) &&
			    !(Client_Type(from) == CLIENT_SERVICE)) {
				if (SendErrors && !IRC_WriteStrClient(from,
						ERR_NONONREG_MSG,
						Client_ID(from), Client_ID(cl)))
					return DISCONNECTED;
				goto send_next_target;
			}

			if (Client_HasMode(cl, 'C')) {
				cl2chan = Channel_FirstChannelOf(cl);
				while (cl2chan) {
					chan = Channel_GetChannel(cl2chan);
					if (Channel_IsMemberOf(chan, from))
						break;
					cl2chan = Channel_NextChannelOf(cl, cl2chan);
				}
				if (!cl2chan) {
					if (SendErrors && !IRC_WriteStrClient(
					    from, ERR_NOTONSAMECHANNEL_MSG,
					    Client_ID(from), Client_ID(cl)))
						return DISCONNECTED;
					goto send_next_target;
				}
			}

			if (SendErrors && (Client_Type(Client) != CLIENT_SERVER)
			    && strchr(Client_Modes(cl), 'a')) {
				/* Target is away */
				if (!IRC_WriteStrClient(from, RPL_AWAY_MSG,
							Client_ID(from),
							Client_ID(cl),
							Client_Away(cl)))
					return DISCONNECTED;
			}
			if (Client_Conn(from) > NONE) {
				Conn_UpdateIdle(Client_Conn(from));
			}
			if (!IRC_WriteStrClientPrefix(cl, from, "%s %s :%s",
						      Req->command, Client_ID(cl),
						      message))
				return DISCONNECTED;
		} else if (ForceType != CLIENT_SERVICE
			   && (chan = Channel_Search(currentTarget))) {
			if (!Channel_Write(chan, from, Client, Req->command,
					   SendErrors, message))
					return DISCONNECTED;
		} else if (ForceType != CLIENT_SERVICE
			/* $#: server/target mask, RFC 2812, sec. 3.3.1 */
			   && strchr("$#", currentTarget[0])
			   && strchr(currentTarget, '.')) {
			/* targetmask */
			if (!Send_Message_Mask(from, Req->command, currentTarget,
					       message, SendErrors))
				return DISCONNECTED;
		} else {
			if (!SendErrors)
				return CONNECTED;
			if (!IRC_WriteStrClient(from, ERR_NOSUCHNICK_MSG,
						Client_ID(from), currentTarget))
				return DISCONNECTED;
		}

	send_next_target:
		currentTarget = strtok_r(NULL, ",", &lastCurrentTarget);
		if (currentTarget)
			Conn_SetPenalty(Client_Conn(Client), 1);
	}

	return CONNECTED;
} /* Send_Message */


static bool
Send_Message_Mask(CLIENT * from, char * command, char * targetMask,
		  char * message, bool SendErrors)
{
	CLIENT *cl;
	bool client_match;
	char *mask = targetMask + 1;
	const char *check_wildcards;

	cl = NULL;

	if (strchr(Client_Modes(from), 'o') == NULL) {
		if (!SendErrors)
			return true;
		return IRC_WriteStrClient(from, ERR_NOPRIVILEGES_MSG,
					  Client_ID(from));
	}

	/*
	 * RFC 2812, sec. 3.3.1 requires that targetMask have at least one
	 * dot (".") and no wildcards ("*", "?") following the last one.
	 */
	check_wildcards = strrchr(targetMask, '.');
	assert(check_wildcards != NULL);
	if (check_wildcards &&
		check_wildcards[strcspn(check_wildcards, "*?")])
	{
		if (!SendErrors)
			return true;
		return IRC_WriteStrClient(from, ERR_WILDTOPLEVEL, targetMask);
	}

	/* #: hostmask, see RFC 2812, sec. 3.3.1 */
	if (targetMask[0] == '#') {
		for (cl = Client_First(); cl != NULL; cl = Client_Next(cl)) {
			if (Client_Type(cl) != CLIENT_USER)
				continue;
			client_match = MatchCaseInsensitive(mask, Client_Hostname(cl));
			if (client_match)
				if (!IRC_WriteStrClientPrefix(cl, from, "%s %s :%s",
						command, Client_ID(cl), message))
					return false;
		}
	} else {
		assert(targetMask[0] == '$'); /* $: server mask, see RFC 2812, sec. 3.3.1 */
		for (cl = Client_First(); cl != NULL; cl = Client_Next(cl)) {
			if (Client_Type(cl) != CLIENT_USER)
				continue;
			client_match = MatchCaseInsensitive(mask,
					Client_ID(Client_Introducer(cl)));
			if (client_match)
				if (!IRC_WriteStrClientPrefix(cl, from, "%s %s :%s",
						command, Client_ID(cl), message))
					return false;
		}
	}
	return CONNECTED;
} /* Send_Message_Mask */