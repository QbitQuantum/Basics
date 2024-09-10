/**
 *  \brief  Take ownership of a render client
 *
 *  Ownership of a render client was taken by session 'ownerSessionsName'. If it
 *  belonged to this session before, release ownership. Fill in
 *  'ownerSessionName' as owner of render client named 'name'.
 *
 *  \return as a pair: both pointer to sessionState CRootItem and the diff as string
 */
std::pair<CRootItem*, std::string> CStreamClientHdl::takeClientStateDiff(const CRootItem* const curState,
		                                                                 const std::string& name,
		                                                                 const std::string& ownerSessionsName)
{
	ostringstream oss;
	CRootItem* newState = new CRootItem(*curState);

	ServDescPtr srvPtr = m_session->getServiceByName(name);
	assert(srvPtr != NULL);

	CCategoryItem* base = newState->getCategoryPtr("/RenderClients");
	if(base == 0) {
		base = newState->mkPath("/RenderClients");
	}

	CStreamClientItem *newsci = new CStreamClientItem(newState, base, name);
	newsci->setHostName(srvPtr->getHostName());
	newsci->setDomainName(srvPtr->getDomainName());
	newsci->setPort(srvPtr->getPortNr());
	newsci->setOwnerSessionName(ownerSessionsName);

    pair<int,int> pospair = hasClient(name);
    int pos = pospair.first;
    int insertbefore = pospair.second;
	if(pos == -1) {
		// streaming client is not known -> append it as available
		int num_clients;

		CCategoryItem* base = newState->getCategoryPtr("/RenderClients");
		if(base == 0) {
			base = newState->mkPath("/RenderClients");
			num_clients = 0;
		}
		else {
			num_clients = base->getNumContentItems();
		}

		oss << "@@ -0,0 +" << num_clients + 1 << ",1 @@" << endl;
		oss << "+" << base->getPath() << "\t" << newsci->serialize();
		base->addChild(newsci);
	}
	else
	{
		// render client 'name' is already known, ownership was taken by 'ownerSessionsName'.
		// do not touch enabled/disabled state
		IContentItem *tmp = base->getContentItem(pos);
		CStreamClientItem *sci = reinterpret_cast<CStreamClientItem*>(tmp);

		if(*sci != *newsci) {
			oss << "@@ -" << pos << ",1 +" << pos << ",1 @@" << endl;
			oss << "-" << base->getPath() << "\t" << sci->serialize();
			oss << "+" << base->getPath() << "\t" << newsci->serialize();
			sci->setOwnerSessionName(ownerSessionsName);
		}
		else
		{
			delete newState;
			return make_pair((CRootItem*)0, string());
		}
	}
	return make_pair( newState, oss.str());
}