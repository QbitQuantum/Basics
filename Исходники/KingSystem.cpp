/**
* @brief	Generates a list of the top 10 clan leaders eligible to nominate a King.
* 			NOTE: These players are senators.
*/
void CKingSystem::LoadRecommendList()
{
	FastGuard lock(m_lock);
	m_top10ClanSet.clear();
	for (int i = 1; i <= 10; i++)
	{
		// Lookup the clan ranking #i.
		_KNIGHTS_RATING * pRating = 
			g_pMain->m_KnightsRatingArray[m_byNation].GetData(i);
		CKnights * pKnights = nullptr;

		// Ignore this entry if no such clan is ranked #i
		if (pRating == nullptr
			// or for whatever reason the clan no longer exists...
				|| (pKnights = g_pMain->GetClanPtr(pRating->sClanID)) == nullptr)
				continue;

		// Add user as senator.
		UpdateElectionList(3, false, pRating->sClanID, pKnights->m_strChief);

		// If the senator's online, we can send them an announcement
		// to tell them they can nominate a King.
		CUser * pUser = g_pMain->GetUserPtr(pKnights->m_strChief, TYPE_CHARACTER);
		if (pUser != nullptr)
		{
			Packet result;
			std::string notice;

			// %s can nominate a King
			g_pMain->GetServerResource(IDS_KING_RECOMMEND_REQUEST_MESSAGE, &notice, pKnights->m_strChief.c_str());

			// Wrap it in a "#### NOTICE : ####" block.
			g_pMain->GetServerResource(IDP_ANNOUNCEMENT, &notice, notice.c_str());

			// Construct & send the chat/announcement packet
			ChatPacket::Construct(&result, WAR_SYSTEM_CHAT, &notice);
			pUser->Send(&result);
		}

		// add to our top 10 ranked clan set.
		m_top10ClanSet.insert(pRating->sClanID);
	}
}