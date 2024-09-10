void CRepositoryNode::LoadModules(IModuleVector & modules, CLoadingNode * loading)
{
	clib::recursive_mutex::scoped_lock lock(m_mutex);
	if (m_loading == loading)
	{
		m_loading->Delete();
		m_loading = NULL;
		WTL::CLockWindowUpdate lock(*GetTreeView());
		for (IModuleVector::iterator itr = modules.begin(); itr != modules.end(); ++itr)
		{
			CModuleNode * newNode = new CModuleNode(m_owner, itr->get());
			newNode->InsertBelow(*GetTreeView(), m_bVirtualNode ? TVI_ROOT : *this);
			newNode->operator ()(itr->get());
		}
	}
}