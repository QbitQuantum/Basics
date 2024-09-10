static void MakeRootSeq(const Seq &s, const Tree &GuideTree, unsigned uLeafNodeIndex,
  const ProgNode Nodes[], Seq &sRoot)
	{
	sRoot.Copy(s);
	unsigned uNodeIndex = uLeafNodeIndex;
	for (;;)
		{
	  	unsigned uParent = GuideTree.GetParent(uNodeIndex);
		if (NULL_NEIGHBOR == uParent)
			break;
		bool bRight = (GuideTree.GetLeft(uParent) == uNodeIndex);
		uNodeIndex = uParent;
		const PWPath &Path = Nodes[uNodeIndex].m_Path;
		Seq sTmp;
		PathSeq(sRoot, Path, bRight, sTmp);
		sRoot.Copy(sTmp);
		}
	}