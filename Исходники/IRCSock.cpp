void CIRCSock::ReadLine(const CString& sData) {
	CString sLine = sData;

	sLine.TrimRight("\n\r");

	DEBUG("(" << m_pNetwork->GetUser()->GetUserName() << "/" << m_pNetwork->GetName() << ") IRC -> ZNC [" << sLine << "]");

	NETWORKMODULECALL(OnRaw(sLine), m_pNetwork->GetUser(), m_pNetwork, NULL, return);

	if (sLine.Equals("PING ", false, 5)) {
		// Generate a reply and don't forward this to any user,
		// we don't want any PING forwarded
		PutIRC("PONG " + sLine.substr(5));
		return;
	} else if (sLine.Token(1).Equals("PONG")) {
		// Block PONGs, we already responded to the pings
		return;
	} else if (sLine.Equals("ERROR ", false, 6)) {
		//ERROR :Closing Link: nick[24.24.24.24] (Excess Flood)
		CString sError(sLine.substr(6));
		sError.TrimPrefix();
		m_pNetwork->PutStatus("Error from Server [" + sError + "]");
		return;
	}

	CString sCmd = sLine.Token(1);

	if ((sCmd.length() == 3) && (isdigit(sCmd[0])) && (isdigit(sCmd[1])) && (isdigit(sCmd[2]))) {
		CString sServer = sLine.Token(0).LeftChomp_n();
		unsigned int uRaw = sCmd.ToUInt();
		CString sNick = sLine.Token(2);
		CString sRest = sLine.Token(3, true);

		switch (uRaw) {
			case 1: { // :irc.server.com 001 nick :Welcome to the Internet Relay Network nick
				if (m_bAuthed && sServer == "irc.znc.in") {
					// m_bAuthed == true => we already received another 001 => we might be in a traffic loop
					m_pNetwork->PutStatus("ZNC seems to be connected to itself, disconnecting...");
					Quit();
					return;
				}

				m_pNetwork->SetIRCServer(sServer);
				SetTimeout(540, TMO_READ);  // Now that we are connected, let nature take its course
				PutIRC("WHO " + sNick);

				m_bAuthed = true;
				m_pNetwork->PutStatus("Connected!");

				vector<CClient*>& vClients = m_pNetwork->GetClients();

				for (unsigned int a = 0; a < vClients.size(); a++) {
					CClient* pClient = vClients[a];
					CString sClientNick = pClient->GetNick(false);

					if (!sClientNick.Equals(sNick)) {
						// If they connected with a nick that doesn't match the one we got on irc, then we need to update them
						pClient->PutClient(":" + sClientNick + "!" + m_Nick.GetIdent() + "@" + m_Nick.GetHost() + " NICK :" + sNick);
					}
				}

				SetNick(sNick);

				NETWORKMODULECALL(OnIRCConnected(), m_pNetwork->GetUser(), m_pNetwork, NULL, NOTHING);

				m_pNetwork->ClearRawBuffer();
				m_pNetwork->AddRawBuffer(":" + sServer + " " + sCmd + " ", " " + sRest);

				break;
			}
			case 5:
				ParseISupport(sRest);
				m_pNetwork->UpdateExactRawBuffer(":" + sServer + " " + sCmd + " ", " " + sRest);
				break;
			case 10: { // :irc.server.com 010 nick <hostname> <port> :<info>
				CString sHost = sRest.Token(0);
				CString sPort = sRest.Token(1);
				CString sInfo = sRest.Token(2, true).TrimPrefix_n();
				m_pNetwork->PutStatus("Server [" + m_pNetwork->GetCurrentServer()->GetString(false) +
						"] redirects us to [" + sHost + ":" + sPort + "] with reason [" + sInfo + "]");
				m_pNetwork->PutStatus("Perhaps you want to add it as a new server.");
				// Don't send server redirects to the client
				return;
			}
			case 2:
			case 3:
			case 4:
			case 250:  // highest connection count
			case 251:  // user count
			case 252:  // oper count
			case 254:  // channel count
			case 255:  // client count
			case 265:  // local users
			case 266:  // global users
				m_pNetwork->UpdateRawBuffer(":" + sServer + " " + sCmd + " ", " " + sRest);
				break;
			case 305:
				m_pNetwork->SetIRCAway(false);
				break;
			case 306:
				m_pNetwork->SetIRCAway(true);
				break;
			case 324: {  // MODE
				sRest.Trim();
				CChan* pChan = m_pNetwork->FindChan(sRest.Token(0));

				if (pChan) {
					pChan->SetModes(sRest.Token(1, true));

					// We don't SetModeKnown(true) here,
					// because a 329 will follow
					if (!pChan->IsModeKnown()) {
						// When we JOIN, we send a MODE
						// request. This makes sure the
						// reply isn't forwarded.
						return;
					}
				}
			}
				break;
			case 329: {
				sRest.Trim();
				CChan* pChan = m_pNetwork->FindChan(sRest.Token(0));

				if (pChan) {
					unsigned long ulDate = sLine.Token(4).ToULong();
					pChan->SetCreationDate(ulDate);

					if (!pChan->IsModeKnown()) {
						pChan->SetModeKnown(true);
						// When we JOIN, we send a MODE
						// request. This makes sure the
						// reply isn't forwarded.
						return;
					}
				}
			}
				break;
			case 331: {
				// :irc.server.com 331 yournick #chan :No topic is set.
				CChan* pChan = m_pNetwork->FindChan(sLine.Token(3));

				if (pChan) {
					pChan->SetTopic("");
				}

				break;
			}
			case 332: {
				// :irc.server.com 332 yournick #chan :This is a topic
				CChan* pChan = m_pNetwork->FindChan(sLine.Token(3));

				if (pChan) {
					CString sTopic = sLine.Token(4, true);
					sTopic.LeftChomp();
					pChan->SetTopic(sTopic);
				}

				break;
			}
			case 333: {
				// :irc.server.com 333 yournick #chan setternick 1112320796
				CChan* pChan = m_pNetwork->FindChan(sLine.Token(3));

				if (pChan) {
					sNick = sLine.Token(4);
					unsigned long ulDate = sLine.Token(5).ToULong();

					pChan->SetTopicOwner(sNick);
					pChan->SetTopicDate(ulDate);
				}

				break;
			}
			case 352: {
				// :irc.yourserver.com 352 yournick #chan ident theirhost.com irc.theirserver.com theirnick H :0 Real Name
				sServer = sLine.Token(0);
				sNick = sLine.Token(7);
				CString sIdent = sLine.Token(4);
				CString sHost = sLine.Token(5);

				sServer.LeftChomp();

				if (sNick.Equals(GetNick())) {
					m_Nick.SetIdent(sIdent);
					m_Nick.SetHost(sHost);
				}

				m_pNetwork->SetIRCNick(m_Nick);
				m_pNetwork->SetIRCServer(sServer);

				const vector<CChan*>& vChans = m_pNetwork->GetChans();

				for (unsigned int a = 0; a < vChans.size(); a++) {
					vChans[a]->OnWho(sNick, sIdent, sHost);
				}

				break;
			}
			case 353: {  // NAMES
				sRest.Trim();
				// Todo: allow for non @+= server msgs
				CChan* pChan = m_pNetwork->FindChan(sRest.Token(1));
				// If we don't know that channel, some client might have
				// requested a /names for it and we really should forward this.
				if (pChan) {
					CString sNicks = sRest.Token(2, true).TrimPrefix_n();
					pChan->AddNicks(sNicks);
				}

				ForwardRaw353(sLine);

				// We forwarded it already, so return
				return;
			}
			case 366: {  // end of names list
				m_pNetwork->PutUser(sLine);  // First send them the raw

				// :irc.server.com 366 nick #chan :End of /NAMES list.
				CChan* pChan = m_pNetwork->FindChan(sRest.Token(0));

				if (pChan) {
					if (pChan->IsOn()) {
						// If we are the only one in the chan, set our default modes
						if (pChan->GetNickCount() == 1) {
							CString sModes = pChan->GetDefaultModes();

							if (sModes.empty()) {
								sModes = m_pNetwork->GetUser()->GetDefaultChanModes();
							}

							if (!sModes.empty()) {
								PutIRC("MODE " + pChan->GetName() + " " + sModes);
							}
						}
					}
				}

				return;  // return so we don't send them the raw twice
			}
			case 375:  // begin motd
			case 422:  // MOTD File is missing
				m_pNetwork->ClearMotdBuffer();
			case 372:  // motd
			case 376:  // end motd
				m_pNetwork->AddMotdBuffer(":" + sServer + " " + sCmd + " ", " " + sRest);
				break;
			case 437:
				// :irc.server.net 437 * badnick :Nick/channel is temporarily unavailable
				// :irc.server.net 437 mynick badnick :Nick/channel is temporarily unavailable
				// :irc.server.net 437 mynick badnick :Cannot change nickname while banned on channel
				if (m_pNetwork->IsChan(sRest.Token(0)) || sNick != "*")
					break;
			case 432: // :irc.server.com 432 * nick :Erroneous Nickname: Illegal characters
			case 433: {
				CString sBadNick = sRest.Token(0);

				if (!m_bAuthed) {
					SendAltNick(sBadNick);
					return;
				}
				break;
			}
			case 451:
				// :irc.server.com 451 CAP :You have not registered
				// Servers that dont support CAP will give us this error, dont send it to the client
				if (sNick.Equals("CAP"))
					return;
			case 470: {
				// :irc.unreal.net 470 mynick [Link] #chan1 has become full, so you are automatically being transferred to the linked channel #chan2
				// :mccaffrey.freenode.net 470 mynick #electronics ##electronics :Forwarding to another channel

				// freenode style numeric
				CChan* pChan = m_pNetwork->FindChan(sRest.Token(0));
				if (!pChan) {
					// unreal style numeric
					pChan = m_pNetwork->FindChan(sRest.Token(1));
				}
				if (pChan) {
					pChan->Disable();
					m_pNetwork->PutStatus("Channel [" + pChan->GetName() + "] is linked to "
							"another channel and was thus disabled.");
				}
				break;
			}
		}
	} else {
		CNick Nick(sLine.Token(0).TrimPrefix_n());
		sCmd = sLine.Token(1);
		CString sRest = sLine.Token(2, true);

		if (sCmd.Equals("NICK")) {
			CString sNewNick = sRest.TrimPrefix_n();
			bool bIsVisible = false;

			vector<CChan*> vFoundChans;
			const vector<CChan*>& vChans = m_pNetwork->GetChans();

			for (unsigned int a = 0; a < vChans.size(); a++) {
				CChan* pChan = vChans[a];

				if (pChan->ChangeNick(Nick.GetNick(), sNewNick)) {
					vFoundChans.push_back(pChan);

					if (!pChan->IsDetached()) {
						bIsVisible = true;
					}
				}
			}

			// Todo: use nick compare function here
			if (Nick.GetNick().Equals(GetNick())) {
				// We are changing our own nick, the clients always must see this!
				bIsVisible = true;
				SetNick(sNewNick);
			}

			NETWORKMODULECALL(OnNick(Nick, sNewNick, vFoundChans), m_pNetwork->GetUser(), m_pNetwork, NULL, NOTHING);

			if (!bIsVisible) {
				return;
			}
		} else if (sCmd.Equals("QUIT")) {
			CString sMessage = sRest.TrimPrefix_n();
			bool bIsVisible = false;

			// :[email protected] QUIT :message

			if (Nick.GetNick().Equals(GetNick())) {
				m_pNetwork->PutStatus("You quit [" + sMessage + "]");
				// We don't call module hooks and we don't
				// forward this quit to clients (Some clients
				// disconnect if they receive such a QUIT)
				return;
			}

			vector<CChan*> vFoundChans;
			const vector<CChan*>& vChans = m_pNetwork->GetChans();

			for (unsigned int a = 0; a < vChans.size(); a++) {
				CChan* pChan = vChans[a];

				if (pChan->RemNick(Nick.GetNick())) {
					vFoundChans.push_back(pChan);

					if (!pChan->IsDetached()) {
						bIsVisible = true;
					}
				}
			}

			NETWORKMODULECALL(OnQuit(Nick, sMessage, vFoundChans), m_pNetwork->GetUser(), m_pNetwork, NULL, NOTHING);

			if (!bIsVisible) {
				return;
			}
		} else if (sCmd.Equals("JOIN")) {
			CString sChan = sRest.Token(0).TrimPrefix_n();
			CChan* pChan;

			// Todo: use nick compare function
			if (Nick.GetNick().Equals(GetNick())) {
				m_pNetwork->AddChan(sChan, false);
				pChan = m_pNetwork->FindChan(sChan);
				if (pChan) {
					pChan->ResetJoinTries();
					pChan->Enable();
					pChan->SetIsOn(true);
					PutIRC("MODE " + sChan);
				}
			} else {
				pChan = m_pNetwork->FindChan(sChan);
			}

			if (pChan) {
				pChan->AddNick(Nick.GetNickMask());
				NETWORKMODULECALL(OnJoin(Nick.GetNickMask(), *pChan), m_pNetwork->GetUser(), m_pNetwork, NULL, NOTHING);

				if (pChan->IsDetached()) {
					return;
				}
			}
		} else if (sCmd.Equals("PART")) {
			CString sChan = sRest.Token(0).TrimPrefix_n();
			CString sMsg = sRest.Token(1, true).TrimPrefix_n();

			CChan* pChan = m_pNetwork->FindChan(sChan);
			bool bDetached = false;
			if (pChan) {
				pChan->RemNick(Nick.GetNick());
				NETWORKMODULECALL(OnPart(Nick.GetNickMask(), *pChan, sMsg), m_pNetwork->GetUser(), m_pNetwork, NULL, NOTHING);

				if (pChan->IsDetached())
					bDetached = true;
			}

			// Todo: use nick compare function
			if (Nick.GetNick().Equals(GetNick())) {
				m_pNetwork->DelChan(sChan);
			}

			/*
			 * We use this boolean because
			 * m_pNetwork->DelChan() will delete this channel
			 * and thus we would dereference an
			 * already-freed pointer!
			 */
			if (bDetached) {
				return;
			}
		} else if (sCmd.Equals("MODE")) {
			CString sTarget = sRest.Token(0);
			CString sModes = sRest.Token(1, true);
			if (sModes.Left(1) == ":")
				sModes = sModes.substr(1);

			CChan* pChan = m_pNetwork->FindChan(sTarget);
			if (pChan) {
				pChan->ModeChange(sModes, &Nick);

				if (pChan->IsDetached()) {
					return;
				}
			} else if (sTarget == m_Nick.GetNick()) {
				CString sModeArg = sModes.Token(0);
				bool bAdd = true;
/* no module call defined (yet?)
				MODULECALL(OnRawUserMode(*pOpNick, *this, sModeArg, sArgs), m_pNetwork->GetUser(), NULL, );
*/
				for (unsigned int a = 0; a < sModeArg.size(); a++) {
					const unsigned char& uMode = sModeArg[a];

					if (uMode == '+') {
						bAdd = true;
					} else if (uMode == '-') {
						bAdd = false;
					} else {
						if (bAdd) {
							m_scUserModes.insert(uMode);
						} else {
							m_scUserModes.erase(uMode);
						}
					}
				}
			}
		} else if (sCmd.Equals("KICK")) {
			// :[email protected] KICK #chan nick :msg
			CString sChan = sRest.Token(0);
			CString sKickedNick = sRest.Token(1);
			CString sMsg = sRest.Token(2, true);
			sMsg.LeftChomp();

			CChan* pChan = m_pNetwork->FindChan(sChan);

			if (pChan) {
				NETWORKMODULECALL(OnKick(Nick, sKickedNick, *pChan, sMsg), m_pNetwork->GetUser(), m_pNetwork, NULL, NOTHING);
				// do not remove the nick till after the OnKick call, so modules
				// can do Chan.FindNick or something to get more info.
				pChan->RemNick(sKickedNick);
			}

			if (GetNick().Equals(sKickedNick) && pChan) {
				pChan->SetIsOn(false);

				// Don't try to rejoin!
				pChan->Disable();
			}

			if ((pChan) && (pChan->IsDetached())) {
				return;
			}
		} else if (sCmd.Equals("NOTICE")) {
			// :[email protected] NOTICE #chan :Message
			CString sTarget = sRest.Token(0);
			CString sMsg = sRest.Token(1, true);
			sMsg.LeftChomp();

			if (sMsg.WildCmp("\001*\001")) {
				sMsg.LeftChomp();
				sMsg.RightChomp();

				if (sTarget.Equals(GetNick())) {
					if (OnCTCPReply(Nick, sMsg)) {
						return;
					}
				}

				m_pNetwork->PutUser(":" + Nick.GetNickMask() + " NOTICE " + sTarget + " :\001" + sMsg + "\001");
				return;
			} else {
				if (sTarget.Equals(GetNick())) {
					if (OnPrivNotice(Nick, sMsg)) {
						return;
					}
				} else {
					if (OnChanNotice(Nick, sTarget, sMsg)) {
						return;
					}
				}
			}

			if (Nick.GetNick().Equals(m_pNetwork->GetIRCServer())) {
				m_pNetwork->PutUser(":" + Nick.GetNick() + " NOTICE " + sTarget + " :" + sMsg);
			} else {
				m_pNetwork->PutUser(":" + Nick.GetNickMask() + " NOTICE " + sTarget + " :" + sMsg);
			}

			return;
		} else if (sCmd.Equals("TOPIC")) {
			// :[email protected] TOPIC #chan :This is a topic
			CChan* pChan = m_pNetwork->FindChan(sLine.Token(2));

			if (pChan) {
				CString sTopic = sLine.Token(3, true);
				sTopic.LeftChomp();

				NETWORKMODULECALL(OnTopic(Nick, *pChan, sTopic), m_pNetwork->GetUser(), m_pNetwork, NULL, return);

				pChan->SetTopicOwner(Nick.GetNick());
				pChan->SetTopicDate((unsigned long) time(NULL));
				pChan->SetTopic(sTopic);

				if (pChan->IsDetached()) {
					return; // Don't forward this
				}

				sLine = ":" + Nick.GetNickMask() + " TOPIC " + pChan->GetName() + " :" + sTopic;
			}
		} else if (sCmd.Equals("PRIVMSG")) {