// Return false when done
bool PhyEnumEdges(const Tree &tree, PhyEnumEdgeState &ES)
	{
	unsigned uNode1 = uInsane;

	if (!ES.m_bInit)
		{
		if (tree.GetNodeCount() <= 1)
			{
			ES.m_uNodeIndex1 = NULL_NEIGHBOR;
			ES.m_uNodeIndex2 = NULL_NEIGHBOR;
			return false;
			}
		uNode1 = tree.FirstDepthFirstNode();
		ES.m_bInit = true;
		}
	else
		{
		uNode1 = tree.NextDepthFirstNode(ES.m_uNodeIndex1);
		if (NULL_NEIGHBOR == uNode1)
			return false;
		if (tree.IsRooted() && tree.IsRoot(uNode1))
			{
			uNode1 = tree.NextDepthFirstNode(uNode1);
			if (NULL_NEIGHBOR == uNode1)
				return false;
			}
		}
	unsigned uNode2 = tree.GetParent(uNode1);

	ES.m_uNodeIndex1 = uNode1;
	ES.m_uNodeIndex2 = uNode2;
	return true;
	}