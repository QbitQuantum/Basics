void CUDPFirewallTester::QueryNextClient(){ // try the next available client for the firewallcheck
	
	if (!IsFWCheckUDPRunning() || !GetUDPCheckClientsNeeded() || CKademlia::GetPrefs()->GetExternalKadPort() == 0)
		return; // check if more tests are needed and wait till we know our extern port

	if (!CKademlia::IsRunning() || CKademlia::GetRoutingZone() == NULL){
		ASSERT( false );
		return;
	}

	while (!m_liPossibleTestClients.IsEmpty()){
		CContact curContact = m_liPossibleTestClients.RemoveHead();
		// udp firewallchecks are not supported by clients with kadversion < 6
		if (curContact.GetVersion() <= KADEMLIA_VERSION5_48a)
			continue;

		// sanitize - do not test ourself
		if (ntohl(curContact.GetIPAddress()) == theApp.GetPublicIP() || curContact.GetClientID().CompareTo(CKademlia::GetPrefs()->GetKadID()) == 0)
			continue;

		// check if we actually requested a firewallcheck from this client at some point
		bool bAlreadyRequested = false;
		for (POSITION pos = m_liUsedTestClients.GetHeadPosition(); pos != NULL;){
			if (m_liUsedTestClients.GetNext(pos).contact.GetIPAddress() == curContact.GetIPAddress()){
				bAlreadyRequested = true;
				break;
			}
		}
		// check if we know itsIP already from kademlia - we need an IP which was never used for UDP yet
		if (!bAlreadyRequested && CKademlia::GetRoutingZone()->GetContact(curContact.GetIPAddress(), 0, false) == NULL){
			// ok, tell the clientlist to do the same search and start the check if ok
			if (theApp.clientlist->DoRequestFirewallCheckUDP(curContact)){
				UsedClient_Struct sAdd = { curContact, false };
				m_liUsedTestClients.AddHead(sAdd);
				m_byFWChecksRunningUDP++;
				break;
			}
		}
	}
}