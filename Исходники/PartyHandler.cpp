void Session::HandlePartyInvitationRequestMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyInvitationRequestMessage data;
	data.Deserialize(packet);
	
	std::string lower = Desperion::ToLowerCase(data.name);
	if(lower == Desperion::ToLowerCase(m_char->GetName())
		|| lower == m_data[FLAG_PSEUDO].stringValue)
		return;

	Session* S = SearchForSession(data.name);
	if(S == NULL)
	{
		Send(PartyCannotJoinErrorMessage(0, 1));
		return;
	}
	else if(m_party != NULL && m_party->PlayersSize() + m_party->GuestsSize() >= 8)
	{
		Send(PartyCannotJoinErrorMessage(0, 3));
		return;
	}
	for(std::map<int, Session*>::iterator it = S->m_partyInvitations.begin(); it != S->m_partyInvitations.end(); ++it)
	{
		if(it->second->GetData(FLAG_GUID).intValue == m_data[FLAG_GUID].intValue)
		{
			Send(PartyCannotJoinErrorMessage(0, 6));
			return;
		}
	}
	
	if(m_party == NULL)
	{
		std::vector<PartyMemberInformationsPtr> members;
		members.push_back(PartyMemberInformationsPtr(m_char->GetPartyMemberInformations()));
		m_party = new Party;
		PARTY_LOCK(m_party)
		m_party->SetPartyId(static_cast<int>(RandomUInt()));
		m_party->SetLeader(this);
		Send(PartyJoinMessage(m_party->GetPartyId(), 0, m_char->GetGuid(), 8, members, std::vector<PartyGuestInformationsPtr>(), false));
	}
	if(!lock)
		PARTY_LOCK(m_party)
	S->m_partyInvitations[m_party->GetPartyId()] = this;
	m_party->GuestPush(S);
	m_party->SetGuestHost(S->GetCharacter()->GetGuid(), m_char->GetGuid());
	m_party->Send(PartyNewGuestMessage(m_party->GetPartyId(), S->GetCharacter()->GetPartyGuestInformations(m_data[FLAG_GUID].intValue)));
	S->Send(PartyInvitationMessage(m_party->GetPartyId(), 0, 8, m_char->GetGuid(), m_char->GetName(), S->GetCharacter()->GetGuid()));
}