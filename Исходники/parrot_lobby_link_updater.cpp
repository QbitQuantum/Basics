bool CParrotLobbyLinkUpdater::ActMsg(CActMsg *msg) {
	if (msg->_action != "Refresh")
		return false;

	CNodeItem *node = findNode();
	LinkUpdatorEntries *entriesP;
	if (isEquals("ParrotLobbyUpdater_TOW")) {
		entriesP = &_entries[4];
	} else {
		if (node->_nodeNumber > 3)
			return true;
		entriesP = &_entries[node->_nodeNumber];
	}
	int count = entriesP->size();

	for (CTreeItem *item = node->getFirstChild(); item; item = item->scan(node)) {
		CLinkItem *link = dynamic_cast<CLinkItem *>(item);
		if (!link || count == 0)
			continue;

		CString linkName = link->getName();
		char c = linkName.lastChar();
		if (c >= 'a' && c <= 'd')
			linkName.deleteLastChar();

		for (uint idx = 0; idx < entriesP->size(); ++idx) {
			const LinkUpdatorEntry &entry = (*entriesP)[idx];
			if (entry._linkStr == linkName) {
				int val = entry._vals[CParrotLobbyObject::_flags];
				if (val)
					linkName += (char)(0x60 + val);

				link->_name = linkName;
				break;
			}
		}
	}

	return true;
}