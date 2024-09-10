bool CRoutingZone::Add(CContact* pContact, bool& bUpdate, bool& bOutIPVerified)
{
	// If we are not a leaf, call add on the correct branch.
	if (!IsLeaf())
		return m_pSubZones[pContact->GetDistance().GetBitNumber(m_uLevel)]->Add(pContact, bUpdate, bOutIPVerified);
	else
	{
		// Do we already have a contact with this KadID?
		CContact* pContactUpdate = m_pBin->GetContact(pContact->GetClientID());
		if (pContactUpdate)
		{
			if(bUpdate)
			{
				if (pContactUpdate->GetUDPKey().GetKeyValue(theApp.GetPublicIP(false)) != 0
					&& pContactUpdate->GetUDPKey().GetKeyValue(theApp.GetPublicIP(false)) != pContact->GetUDPKey().GetKeyValue(theApp.GetPublicIP(false)))
				{
					// if our existing contact has a UDPSender-Key (which should be the case for all > = 0.49a clients)
					// except if our IP has changed recently, we demand that the key is the same as the key we received
					// from the packet which wants to update this contact in order to make sure this is not a try to
					// hijack this entry
					DebugLogWarning(_T("Kad: Sender (%s) tried to update contact entry but failed to provide the proper sender key (Sent Empty: %s) for the entry (%s) - denying update")
						, ipstr(ntohl(pContact->GetIPAddress())), pContact->GetUDPKey().GetKeyValue(theApp.GetPublicIP(false)) == 0 ? _T("Yes") : _T("No")
						, ipstr(ntohl(pContactUpdate->GetIPAddress())));
					bUpdate = false;
				}
				else if (pContactUpdate->GetVersion() >= KADEMLIA_VERSION1_46c && pContactUpdate->GetVersion() < KADEMLIA_VERSION6_49aBETA
					&& pContactUpdate->GetReceivedHelloPacket())
				{
					// legacy kad2 contacts are allowed only to update their RefreshTimer to avoid having them hijacked/corrupted by an attacker
					// (kad1 contacts do not have this restriction as they might turn out as kad2 later on)
					// only exception is if we didn't received a HELLO packet from this client yet
					if (pContactUpdate->GetIPAddress() == pContact->GetIPAddress() && pContactUpdate->GetTCPPort() == pContact->GetTCPPort()
						&& pContactUpdate->GetVersion() == pContact->GetVersion() && pContactUpdate->GetUDPPort() == pContact->GetUDPPort())
					{
						ASSERT( !pContact->IsIpVerified() ); // legacy kad2 nodes should be unable to verify their IP on a HELLO
						bOutIPVerified = pContactUpdate->IsIpVerified();
						m_pBin->SetAlive(pContactUpdate);
						theApp.emuledlg->kademliawnd->ContactRef(pContactUpdate);
						DEBUG_ONLY( AddDebugLogLine(DLP_VERYLOW, false, _T("Updated kad contact refreshtimer only for legacy kad2 contact (%s, %u)")
							, ipstr(ntohl(pContactUpdate->GetIPAddress())), pContactUpdate->GetVersion()) );
					}
					else{
						AddDebugLogLine(DLP_DEFAULT, false, _T("Rejected value update for legacy kad2 contact (%s -> %s, %u -> %u)")
							, ipstr(ntohl(pContactUpdate->GetIPAddress())), ipstr(ntohl(pContact->GetIPAddress())), pContactUpdate->GetVersion(), pContact->GetVersion());
						bUpdate = false;
					}
					
				}
				else{
#ifdef _DEBUG
					// just for outlining, get removed anyway
					//debug logging stuff - remove later
					if (pContact->GetUDPKey().GetKeyValue(theApp.GetPublicIP(false)) == 0){
						if (pContact->GetVersion() >= KADEMLIA_VERSION6_49aBETA && pContact->GetType() < 2)
							AddDebugLogLine(DLP_LOW, false, _T("Updating > 0.49a + type < 2 contact without valid key stored %s"), ipstr(ntohl(pContact->GetIPAddress())));
					}
					else
						AddDebugLogLine(DLP_VERYLOW, false, _T("Updating contact, passed key check %s"), ipstr(ntohl(pContact->GetIPAddress())));

					if (pContactUpdate->GetVersion() >= KADEMLIA_VERSION1_46c && pContactUpdate->GetVersion() < KADEMLIA_VERSION6_49aBETA){
						ASSERT( !pContactUpdate->GetReceivedHelloPacket() );
						AddDebugLogLine(DLP_VERYLOW, false, _T("Accepted update for legacy kad2 contact, because of first HELLO (%s -> %s, %u -> %u)")
							, ipstr(ntohl(pContactUpdate->GetIPAddress())), ipstr(ntohl(pContact->GetIPAddress())), pContactUpdate->GetVersion(), pContact->GetVersion());
					}
#endif
					// All other nodes (Kad1, Kad2 > 0.49a with UDPKey checked or not set, first hello updates) are allowed to do full updates
					if (m_pBin->ChangeContactIPAddress(pContactUpdate, pContact->GetIPAddress())
						&& pContact->GetVersion() >= pContactUpdate->GetVersion()) // do not let Kad1 responses overwrite Kad2 ones
					{
						pContactUpdate->SetUDPPort(pContact->GetUDPPort());
						pContactUpdate->SetTCPPort(pContact->GetTCPPort());
						pContactUpdate->SetVersion(pContact->GetVersion());
						pContactUpdate->SetUDPKey(pContact->GetUDPKey());
						if (!pContactUpdate->IsIpVerified()) // don't unset the verified flag (will clear itself on ipchanges)
							pContactUpdate->SetIpVerified(pContact->IsIpVerified());
						bOutIPVerified = pContactUpdate->IsIpVerified();
						m_pBin->SetAlive(pContactUpdate);
						theApp.emuledlg->kademliawnd->ContactRef(pContactUpdate);
						if (pContact->GetReceivedHelloPacket())
							pContactUpdate->SetReceivedHelloPacket();
					}
					else
						bUpdate = false;
				}
			}
			return false;
		}
		else if (m_pBin->GetRemaining())
		{
			bUpdate = false;
			// This bin is not full, so add the new contact.
			if(m_pBin->AddContact(pContact))
			{
				// Add was successful, add to the GUI and let contact know it's listed in the gui.
				if (theApp.emuledlg->kademliawnd->ContactAdd(pContact))
					pContact->SetGuiRefs(true);
				return true;
			}
			return false;
		}
		else if (CanSplit())
		{
			// This bin was full and split, call add on the correct branch.
			Split();
			return m_pSubZones[pContact->GetDistance().GetBitNumber(m_uLevel)]->Add(pContact, bUpdate, bOutIPVerified);
		}
		else{
			bUpdate = false;
			return false;
		}
	}
}