bool CActing::Acting(shared_ptr<Behavior> a_Behavior, CCPoint a_Pos)
{
	if (m_nBehaviorCount > m_nMaxBehaviorCount && !Behavior::k_bIsDoing)
		return false;

	if (a_Behavior->Action(a_Pos))
	{
		m_listBehavior.push_back(a_Behavior);
		CreateIcon(a_Behavior->getIconFileName());
		m_nBehaviorCount++;
		if (m_nBehaviorCount > 3)
		{
			RemoveFirstMemory();
		}
		SortIcon();
		return true;
	}

	return false;
}