bool CommonBfJlModules::initialize(NodePtr pNode)
{
	assert(m_pBfsHandler != nullptr);
	assert(m_pGameHandler != nullptr);
	m_nTotalJobs = 0;
	setJobLevelRoot(pNode);
	std::vector<NodePtr> vNodes;
	NodePtr pTraversedNode = pNode;
	while (pTraversedNode != nullptr) {
		vNodes.push_back(pTraversedNode);
		pTraversedNode = pTraversedNode->getParent();
	}
	for (std::vector<NodePtr>::reverse_iterator rit = vNodes.rbegin(); rit != vNodes.rend(); ++rit) {
		m_pBfsHandler->initializeNode(*rit);
		m_pGameHandler->initializeNode(*rit);
	}
	return true;
}