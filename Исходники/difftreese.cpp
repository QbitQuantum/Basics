void DiffTreesE(const Tree &NewTree, const Tree &OldTree,
  unsigned NewNodeIndexToOldNodeIndex[])
	{
#if	TRACE
	Log("DiffTreesE NewTree:\n");
	NewTree.LogMe();
	Log("\n");
	Log("OldTree:\n");
	OldTree.LogMe();
#endif

	if (!NewTree.IsRooted() || !OldTree.IsRooted())
		Quit("DiffTrees: requires rooted trees");

	const unsigned uNodeCount = NewTree.GetNodeCount();
	const unsigned uOldNodeCount = OldTree.GetNodeCount();
	const unsigned uLeafCount = NewTree.GetLeafCount();
	const unsigned uOldLeafCount = OldTree.GetLeafCount();
	if (uNodeCount != uOldNodeCount || uLeafCount != uOldLeafCount)
		Quit("DiffTreesE: different node counts");

	{
	unsigned *IdToOldNodeIndex = new unsigned[uNodeCount];
	for (unsigned uOldNodeIndex = 0; uOldNodeIndex < uNodeCount; ++uOldNodeIndex)
		{
		if (OldTree.IsLeaf(uOldNodeIndex))
			{
			unsigned Id = OldTree.GetLeafId(uOldNodeIndex);
			IdToOldNodeIndex[Id] = uOldNodeIndex;
			}
		}

// Initialize NewNodeIndexToOldNodeIndex[]
// All internal nodes are marked as changed, but may be updated later.
	for (unsigned uNewNodeIndex = 0; uNewNodeIndex < uNodeCount; ++uNewNodeIndex)
		{
		if (NewTree.IsLeaf(uNewNodeIndex))
			{
			unsigned uId = NewTree.GetLeafId(uNewNodeIndex);
			assert(uId < uLeafCount);

			unsigned uOldNodeIndex = IdToOldNodeIndex[uId];
			assert(uOldNodeIndex < uNodeCount);

			NewNodeIndexToOldNodeIndex[uNewNodeIndex] = uOldNodeIndex;
			}
		else
			NewNodeIndexToOldNodeIndex[uNewNodeIndex] = NODE_CHANGED;
		}
	delete[] IdToOldNodeIndex;
	}

// Depth-first traversal of tree.
// The order guarantees that a node is visited before
// its parent is visited.
	for (unsigned uNewNodeIndex = NewTree.FirstDepthFirstNode();
	  NULL_NEIGHBOR != uNewNodeIndex;
	  uNewNodeIndex = NewTree.NextDepthFirstNode(uNewNodeIndex))
		{
		if (NewTree.IsLeaf(uNewNodeIndex))
			continue;

	// If either child is changed, flag this node as changed and continue.
		unsigned uNewLeft = NewTree.GetLeft(uNewNodeIndex);
		unsigned uOldLeft = NewNodeIndexToOldNodeIndex[uNewLeft];
		if (NODE_CHANGED == uOldLeft)
			{
			NewNodeIndexToOldNodeIndex[uNewLeft] = NODE_CHANGED;
			continue;
			}

		unsigned uNewRight = NewTree.GetRight(uNewNodeIndex);
		unsigned uOldRight = NewNodeIndexToOldNodeIndex[uNewRight];
		if (NODE_CHANGED == NewNodeIndexToOldNodeIndex[uNewRight])
			{
			NewNodeIndexToOldNodeIndex[uNewRight] = NODE_CHANGED;
			continue;
			}

		unsigned uOldParentLeft = OldTree.GetParent(uOldLeft);
		unsigned uOldParentRight = OldTree.GetParent(uOldRight);
		if (uOldParentLeft == uOldParentRight)
			NewNodeIndexToOldNodeIndex[uNewNodeIndex] = uOldParentLeft;
		else
			NewNodeIndexToOldNodeIndex[uNewNodeIndex] = NODE_CHANGED;
		}

#if TRACE
	{
	Log("NewToOld ");
	for (unsigned uNewNodeIndex = 0; uNewNodeIndex < uNodeCount; ++uNewNodeIndex)
		{
		Log(" [%3u]=", uNewNodeIndex);
		if (NODE_CHANGED == NewNodeIndexToOldNodeIndex[uNewNodeIndex])
			Log("  X");
		else
			Log("%3u", NewNodeIndexToOldNodeIndex[uNewNodeIndex]);
		if ((uNewNodeIndex+1)%8 == 0)
			Log("\n         ");
		}
	Log("\n");
	}
#endif

#if	DEBUG
	{
	for (unsigned uNewNodeIndex = 0; uNewNodeIndex < uNodeCount; ++uNewNodeIndex)
		{
		unsigned uOld = NewNodeIndexToOldNodeIndex[uNewNodeIndex];
		if (NewTree.IsLeaf(uNewNodeIndex))
			{
			if (uOld >= uNodeCount)
				{
				Log("NewNode=%u uOld=%u > uNodeCount=%u\n",
				  uNewNodeIndex, uOld, uNodeCount);
				Quit("Diff check failed");
				}
			unsigned uIdNew = NewTree.GetLeafId(uNewNodeIndex);
			unsigned uIdOld = OldTree.GetLeafId(uOld);
			if (uIdNew != uIdOld)
				{
				Log("NewNode=%u uOld=%u IdNew=%u IdOld=%u\n",
				  uNewNodeIndex, uOld, uIdNew, uIdOld);
				Quit("Diff check failed");
				}
			continue;
			}

		if (NODE_CHANGED == uOld)
			continue;

		unsigned uNewLeft = NewTree.GetLeft(uNewNodeIndex);
		unsigned uNewRight = NewTree.GetRight(uNewNodeIndex);

		unsigned uOldLeft = OldTree.GetLeft(uOld);
		unsigned uOldRight = OldTree.GetRight(uOld);

		unsigned uNewLeftPartner = NewNodeIndexToOldNodeIndex[uNewLeft];
		unsigned uNewRightPartner = NewNodeIndexToOldNodeIndex[uNewRight];

		bool bSameNotRotated = (uNewLeftPartner == uOldLeft && uNewRightPartner == uOldRight);
		bool bSameRotated = (uNewLeftPartner == uOldRight && uNewRightPartner == uOldLeft);
		if (!bSameNotRotated && !bSameRotated)
			{
			Log("NewNode=%u NewL=%u NewR=%u\n", uNewNodeIndex, uNewLeft, uNewRight);
			Log("OldNode=%u OldL=%u OldR=%u\n", uOld, uOldLeft, uOldRight);
			Log("NewLPartner=%u NewRPartner=%u\n", uNewLeftPartner, uNewRightPartner);
			Quit("Diff check failed");
			}
		}
	}
#endif
	}