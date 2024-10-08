void CreateNetworkInfo(CRichEditCtrlX& rCtrl, CHARFORMAT& rcfDef, CHARFORMAT& rcfBold, bool bFullInfo)
{
	CString buffer;

	if (bFullInfo)
	{
		///////////////////////////////////////////////////////////////////////////
		// Ports Info
		///////////////////////////////////////////////////////////////////////////
		rCtrl.SetSelectionCharFormat(rcfBold);
		rCtrl << GetResString(IDS_CLIENT) << _T("\r\n");
		rCtrl.SetSelectionCharFormat(rcfDef);

		rCtrl << GetResString(IDS_PW_NICK) << _T(":\t") << thePrefs.GetUserNick() << _T("\r\n");
		rCtrl << GetResString(IDS_CD_UHASH) << _T("\t") << md4str((uchar*)thePrefs.GetUserHash()) << _T("\r\n");
		rCtrl << _T("TCP-") << GetResString(IDS_PORT) << _T(":\t") << thePrefs.GetPort() << _T("\r\n");
		rCtrl << _T("UDP-") << GetResString(IDS_PORT) << _T(":\t") << thePrefs.GetUDPPort() << _T("\r\n");
		rCtrl << _T("\r\n");
	}

	///////////////////////////////////////////////////////////////////////////
	// ED2K
	///////////////////////////////////////////////////////////////////////////
	rCtrl.SetSelectionCharFormat(rcfBold);
	rCtrl << _T("eD2K ") << GetResString(IDS_NETWORK) << _T("\r\n");
	rCtrl.SetSelectionCharFormat(rcfDef);

	rCtrl << GetResString(IDS_STATUS) << _T(":\t");
	if (theApp.serverconnect->IsConnected())
		rCtrl << GetResString(IDS_CONNECTED);
	else if(theApp.serverconnect->IsConnecting())
		rCtrl << GetResString(IDS_CONNECTING);
	else 
		rCtrl << GetResString(IDS_DISCONNECTED);
	rCtrl << _T("\r\n");

	//I only show this in full display as the normal display is not
	//updated at regular intervals.
	if (bFullInfo && theApp.serverconnect->IsConnected())
	{
		uint32_t uTotalUser = 0;
		uint32_t uTotalFile = 0;

		theApp.serverlist->GetUserFileStatus(uTotalUser, uTotalFile);
		rCtrl << GetResString(IDS_UUSERS) << _T(":\t") << GetFormatedUInt(uTotalUser) << _T("\r\n");
		rCtrl << GetResString(IDS_PW_FILES) << _T(":\t") << GetFormatedUInt(uTotalFile) << _T("\r\n");
	}

	if (theApp.serverconnect->IsConnected()){
		rCtrl << GetResString(IDS_IP) << _T(":") << GetResString(IDS_PORT) << _T(":") ;
		if (theApp.serverconnect->IsLowID() && theApp.GetPublicIP(true) == 0)
			buffer = GetResString(IDS_UNKNOWN);
		else
			buffer.Format(_T("%s:%u"), ipstr(theApp.GetPublicIP(true)), thePrefs.GetPort());
		rCtrl << _T("\t") << buffer << _T("\r\n");

		rCtrl << GetResString(IDS_ID) << _T(":\t");
		if (theApp.serverconnect->IsConnected()){
			buffer.Format(_T("%u"),theApp.serverconnect->GetClientID());
			rCtrl << buffer;
		}
		rCtrl << _T("\r\n");

		rCtrl << _T("\t");
		if (theApp.serverconnect->IsLowID())
			rCtrl << GetResString(IDS_IDLOW);
		else
			rCtrl << GetResString(IDS_IDHIGH);
		rCtrl << _T("\r\n");

		CServer* cur_server = theApp.serverconnect->GetCurrentServer();
		CServer* srv = cur_server ? theApp.serverlist->GetServerByAddress(cur_server->GetAddress(), cur_server->GetPort()) : NULL;
		if (srv){
			rCtrl << _T("\r\n");
			rCtrl.SetSelectionCharFormat(rcfBold);
			rCtrl << _T("eD2K ") << GetResString(IDS_SERVER) << _T("\r\n");
			rCtrl.SetSelectionCharFormat(rcfDef);

			rCtrl << GetResString(IDS_SW_NAME) << _T(":\t") << srv->GetListName() << _T("\r\n");
			rCtrl << GetResString(IDS_DESCRIPTION) << _T(":\t") << srv->GetDescription() << _T("\r\n");
			rCtrl << GetResString(IDS_IP) << _T(":") << GetResString(IDS_PORT) << _T(":\t") << srv->GetAddress() << _T(":") << srv->GetPort() << _T("\r\n");
			rCtrl << GetResString(IDS_VERSION) << _T(":\t") << srv->GetVersion() << _T("\r\n");
			rCtrl << GetResString(IDS_UUSERS) << _T(":\t") << GetFormatedUInt(srv->GetUsers()) << _T("\r\n");
			rCtrl << GetResString(IDS_PW_FILES) << _T(":\t") << GetFormatedUInt(srv->GetFiles()) << _T("\r\n");
			rCtrl << GetResString(IDS_FSTAT_CONNECTION) << _T(":\t");
			if (theApp.serverconnect->IsConnectedObfuscated())
				rCtrl << GetResString(IDS_OBFUSCATED);
			else
				rCtrl << GetResString(IDS_PRIONORMAL);
			rCtrl << _T("\r\n");
			

			if (bFullInfo)
			{
				rCtrl << GetResString(IDS_IDLOW) << _T(":\t") << GetFormatedUInt(srv->GetLowIDUsers()) << _T("\r\n");
				rCtrl << GetResString(IDS_PING) << _T(":\t") << srv->GetPing() << _T(" ms\r\n");

				rCtrl << _T("\r\n");
				rCtrl.SetSelectionCharFormat(rcfBold);
				rCtrl << _T("eD2K ") << GetResString(IDS_SERVER) << _T(" ") << GetResString(IDS_FEATURES) << _T("\r\n");
				rCtrl.SetSelectionCharFormat(rcfDef);

				rCtrl << GetResString(IDS_SERVER_LIMITS) << _T(": ") << GetFormatedUInt(srv->GetSoftFiles()) << _T("/") << GetFormatedUInt(srv->GetHardFiles()) << _T("\r\n");

				if (thePrefs.IsExtControlsEnabled())
				{
					rCtrl << GetResString(IDS_SRV_TCPCOMPR) << _T(": ");
					if (srv->GetTCPFlags() & SRV_TCPFLG_COMPRESSION)
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_SHORTTAGS) << _T(": ");
					if ((srv->GetTCPFlags() & SRV_TCPFLG_NEWTAGS) || (srv->GetUDPFlags() & SRV_UDPFLG_NEWTAGS))
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << _T("Unicode") << _T(": ");
					if ((srv->GetTCPFlags() & SRV_TCPFLG_UNICODE) || (srv->GetUDPFlags() & SRV_UDPFLG_UNICODE))
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_SERVERFEATURE_INTTYPETAGS) << _T(": ");
					if (srv->GetTCPFlags() & SRV_TCPFLG_TYPETAGINTEGER)
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_SRV_UDPSR) << _T(": ");
					if (srv->GetUDPFlags() & SRV_UDPFLG_EXT_GETSOURCES)
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_SRV_UDPSR) << _T(" #2: ");
					if (srv->GetUDPFlags() & SRV_UDPFLG_EXT_GETSOURCES2)
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_SRV_UDPFR) << _T(": ");
					if (srv->GetUDPFlags() & SRV_UDPFLG_EXT_GETFILES)
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_SRV_LARGEFILES) << _T(": ");
					if (srv->SupportsLargeFilesTCP() || srv->SupportsLargeFilesUDP())
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_PROTOCOLOBFUSCATION) << _T(" (UDP)") << _T(": ");
					if (srv->SupportsObfuscationUDP())
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");

					rCtrl << GetResString(IDS_PROTOCOLOBFUSCATION) << _T(" (TCP)") << _T(": ");
					if (srv->SupportsObfuscationTCP())
						rCtrl << GetResString(IDS_YES);
					else
						rCtrl << GetResString(IDS_NO);
					rCtrl << _T("\r\n");
				}
			}
		}
	}
	rCtrl << _T("\r\n");

	///////////////////////////////////////////////////////////////////////////
	// Kademlia
	///////////////////////////////////////////////////////////////////////////
	/* ismod: no KAD
    rCtrl.SetSelectionCharFormat(rcfBold);
	rCtrl << GetResString(IDS_KADEMLIA) << _T(" ") << GetResString(IDS_NETWORK) << _T("\r\n");
	rCtrl.SetSelectionCharFormat(rcfDef);
	
	rCtrl << GetResString(IDS_STATUS) << _T(":\t");
	if(Kademlia::CKademlia::IsConnected()){
		if(Kademlia::CKademlia::IsFirewalled())
			rCtrl << GetResString(IDS_FIREWALLED);
		else
			rCtrl << GetResString(IDS_KADOPEN);
		if (Kademlia::CKademlia::IsRunningInLANMode())
			rCtrl << _T(" (") << GetResString(IDS_LANMODE) << _T(")");
		rCtrl << _T("\r\n");
		rCtrl << _T("UDP ") + GetResString(IDS_STATUS) << _T(":\t");
		if(Kademlia::CUDPFirewallTester::IsFirewalledUDP(true))
			rCtrl << GetResString(IDS_FIREWALLED);
		else if (Kademlia::CUDPFirewallTester::IsVerified())
			rCtrl << GetResString(IDS_KADOPEN);
		else{
			CString strTmp = GetResString(IDS_UNVERIFIED);
			strTmp.MakeLower();
			rCtrl << GetResString(IDS_KADOPEN) + _T(" (") + strTmp + _T(")");
		}
		rCtrl << _T("\r\n");

		CString IP;
		IP = ipstr(ntohl(Kademlia::CKademlia::GetPrefs()->GetIPAddress()));
		buffer.Format(_T("%s:%i"), IP, thePrefs.GetUDPPort());
		rCtrl << GetResString(IDS_IP) << _T(":") << GetResString(IDS_PORT) << _T(":\t") << buffer << _T("\r\n");

		buffer.Format(_T("%u"),Kademlia::CKademlia::GetPrefs()->GetIPAddress());
		rCtrl << GetResString(IDS_ID) << _T(":\t") << buffer << _T("\r\n");
		if (Kademlia::CKademlia::GetPrefs()->GetUseExternKadPort() && Kademlia::CKademlia::GetPrefs()->GetExternalKadPort() != 0
			&& Kademlia::CKademlia::GetPrefs()->GetInternKadPort() != Kademlia::CKademlia::GetPrefs()->GetExternalKadPort())
		{
			buffer.Format(_T("%u"), Kademlia::CKademlia::GetPrefs()->GetExternalKadPort());
			rCtrl << GetResString(IDS_EXTERNUDPPORT) << _T(":\t") << buffer << _T("\r\n");
		}
		
		if (Kademlia::CUDPFirewallTester::IsFirewalledUDP(true)) {
			rCtrl << GetResString(IDS_BUDDY) << _T(":\t");
			switch ( theApp.clientlist->GetBuddyStatus() )
			{
				case Disconnected:
					rCtrl << GetResString(IDS_BUDDYNONE);
					break;
				case Connecting:
					rCtrl << GetResString(IDS_CONNECTING);
					break;
				case Connected:
					rCtrl << GetResString(IDS_CONNECTED);
					break;
			}
			rCtrl << _T("\r\n");
		}

		if (bFullInfo)
		{

			CString sKadID;
			Kademlia::CKademlia::GetPrefs()->GetKadID(&sKadID);
			rCtrl << GetResString(IDS_CD_UHASH) << _T("\t") << sKadID << _T("\r\n");

			rCtrl << GetResString(IDS_UUSERS) << _T(":\t") << GetFormatedUInt(Kademlia::CKademlia::GetKademliaUsers()) << _T(" (Experimental: ") <<  GetFormatedUInt(Kademlia::CKademlia::GetKademliaUsers(true)) << _T(")\r\n");
			//rCtrl << GetResString(IDS_UUSERS) << _T(":\t") << GetFormatedUInt(Kademlia::CKademlia::GetKademliaUsers()) << _T("\r\n");
			rCtrl << GetResString(IDS_PW_FILES) << _T(":\t") << GetFormatedUInt(Kademlia::CKademlia::GetKademliaFiles()) << _T("\r\n");
			rCtrl <<  GetResString(IDS_INDEXED) << _T(":\r\n");
			buffer.Format(GetResString(IDS_KADINFO_SRC) , Kademlia::CKademlia::GetIndexed()->m_uTotalIndexSource);
			rCtrl << buffer;
			buffer.Format(GetResString(IDS_KADINFO_KEYW), Kademlia::CKademlia::GetIndexed()->m_uTotalIndexKeyword);
			rCtrl << buffer;
			buffer.Format(_T("\t%s: %u\r\n"), GetResString(IDS_NOTES), Kademlia::CKademlia::GetIndexed()->m_uTotalIndexNotes);
			rCtrl << buffer;
			buffer.Format(_T("\t%s: %u\r\n"), GetResString(IDS_THELOAD), Kademlia::CKademlia::GetIndexed()->m_uTotalIndexLoad);
			rCtrl << buffer;
		}
	}
	else if (Kademlia::CKademlia::IsRunning())
		rCtrl << GetResString(IDS_CONNECTING) << _T("\r\n");
	else
		rCtrl << GetResString(IDS_DISCONNECTED) << _T("\r\n");
	rCtrl << _T("\r\n");
    */

	///////////////////////////////////////////////////////////////////////////
	// Web Interface
	///////////////////////////////////////////////////////////////////////////
	rCtrl.SetSelectionCharFormat(rcfBold);
	rCtrl << GetResString(IDS_WEBSRV) << _T("\r\n");
	rCtrl.SetSelectionCharFormat(rcfDef);
	rCtrl << GetResString(IDS_STATUS) << _T(":\t");
	rCtrl << (thePrefs.GetWSIsEnabled() ? GetResString(IDS_ENABLED) : GetResString(IDS_DISABLED)) << _T("\r\n");
	if (thePrefs.GetWSIsEnabled()){
		CString count;
		count.Format(_T("%i %s"), theApp.webserver->GetSessionCount(), GetResString(IDS_ACTSESSIONS));
		rCtrl << _T("\t") << count << _T("\r\n");
		CString strHostname;
		if (!thePrefs.GetYourHostname().IsEmpty() && thePrefs.GetYourHostname().Find(_T('.')) != -1)
			strHostname = thePrefs.GetYourHostname();
		else
			strHostname = ipstr(theApp.serverconnect->GetLocalIP());
		rCtrl << _T("URL:\t") << _T("http://") << strHostname << _T(":") << thePrefs.GetWSPort() << _T("/\r\n");
	}
}