void DiffTrees(const Tree &Tree1, const Tree &Tree2, Tree &Diffs,
  unsigned IdToDiffsLeafNodeIndex[])
	{
#if	TRACE
	Log("Tree1:\n");
	Tree1.LogMe();
	Log("\n");
	Log("Tree2:\n");
	Tree2.LogMe();
#endif

	if (!Tree1.IsRooted() || !Tree2.IsRooted())
		Quit("DiffTrees: requires rooted trees");

	const unsigned uNodeCount = Tree1.GetNodeCount();
	const unsigned uNodeCount2 = Tree2.GetNodeCount();
	
	const unsigned uLeafCount = Tree1.GetLeafCount();
	const unsigned uLeafCount2 = Tree2.GetLeafCount();
	assert(uLeafCount == uLeafCount2);

	if (uNodeCount != uNodeCount2)
		Quit("DiffTrees: different node counts");

// Allocate tables so we can convert tree node index to
// and from the unique id with a O(1) lookup.
	unsigned *NodeIndexToId1 = new unsigned[uNodeCount];
	unsigned *IdToNodeIndex2 = new unsigned[uNodeCount];

	bool *bIsBachelor1 = new bool[uNodeCount];
	bool *bIsDiff1 = new bool[uNodeCount];

	for (unsigned uNodeIndex = 0; uNodeIndex < uNodeCount; ++uNodeIndex)
		{
		NodeIndexToId1[uNodeIndex] = uNodeCount;
		bIsBachelor1[uNodeIndex] = false;
		bIsDiff1[uNodeIndex] = false;

	// Use uNodeCount as value meaning "not set".
		IdToNodeIndex2[uNodeIndex] = uNodeCount;
		}

// Initialize node index <-> id lookup tables
	for (unsigned uNodeIndex = 0; uNodeIndex < uNodeCount; ++uNodeIndex)
		{
		if (Tree1.IsLeaf(uNodeIndex))
			{
			const unsigned uId = Tree1.GetLeafId(uNodeIndex);
			if (uId >= uNodeCount)
				Quit("Diff trees requires existing leaf ids in range 0 .. (N-1)");
			NodeIndexToId1[uNodeIndex] = uId;
			}

		if (Tree2.IsLeaf(uNodeIndex))
			{
			const unsigned uId = Tree2.GetLeafId(uNodeIndex);
			if (uId >= uNodeCount)
				Quit("Diff trees requires existing leaf ids in range 0 .. (N-1)");
			IdToNodeIndex2[uId] = uNodeIndex;
			}
		}

// Validity check. This verifies that the ids
// pre-assigned to the leaves in Tree1 are unique
// (note that the id<N check above does not rule
// out two leaves having duplicate ids).
	for (unsigned uId = 0; uId < uLeafCount; ++uId)
		{
		unsigned uNodeIndex2 = IdToNodeIndex2[uId];
		if (uNodeCount == uNodeIndex2)
			Quit("DiffTrees, check 2");
		}

// Ids assigned to internal nodes are N, N+1 ...
// An internal node id uniquely identifies a set
// of two or more leaves.
	unsigned uInternalNodeId = uLeafCount;

// Depth-first traversal of tree.
// The order guarantees that a node is visited before
// its parent is visited.
	for (unsigned uNodeIndex1 = Tree1.FirstDepthFirstNode();
	  NULL_NEIGHBOR != uNodeIndex1;
	  uNodeIndex1 = Tree1.NextDepthFirstNode(uNodeIndex1))
		{
#if	TRACE
		Log("Main loop: Node1=%u IsLeaf=%d IsBachelor=%d\n",
		  uNodeIndex1,
		  Tree1.IsLeaf(uNodeIndex1),
		  bIsBachelor1[uNodeIndex1]);
#endif

	// Leaves are trivial; nothing to do.
		if (Tree1.IsLeaf(uNodeIndex1) || bIsBachelor1[uNodeIndex1])
			continue;

	// If either child is a bachelor, flag
	// this node as a bachelor and continue.
		unsigned uLeft1 = Tree1.GetLeft(uNodeIndex1);
		if (bIsBachelor1[uLeft1])
			{
			bIsBachelor1[uNodeIndex1] = true;
			continue;
			}

		unsigned uRight1 = Tree1.GetRight(uNodeIndex1);
		if (bIsBachelor1[uRight1])
			{
			bIsBachelor1[uNodeIndex1] = true;
			continue;
			}

	// Both children are married.
	// Married nodes are guaranteed to have an id.
		unsigned uIdLeft = NodeIndexToId1[uLeft1];
		unsigned uIdRight = NodeIndexToId1[uRight1];

		if (uIdLeft == uNodeCount || uIdRight == uNodeCount)
			Quit("DiffTrees, check 5");

	// uLeft2 is the spouse of uLeft1, and similarly for uRight2.
		unsigned uLeft2 = IdToNodeIndex2[uIdLeft];
		unsigned uRight2 = IdToNodeIndex2[uIdRight];

		if (uLeft2 == uNodeCount || uRight2 == uNodeCount)
			Quit("DiffTrees, check 6");

	// If the spouses of uLeft1 and uRight1 have the same
	// parent, then this parent is the spouse of uNodeIndex1.
	// Otherwise, uNodeIndex1 is a diff.
		unsigned uParentLeft2 = Tree2.GetParent(uLeft2);
		unsigned uParentRight2 = Tree2.GetParent(uRight2);

#if	TRACE
		Log("L1=%u R1=%u L2=%u R2=%u PL2=%u PR2=%u\n",
		  uLeft1,
		  uRight1,
		  uLeft2,
		  uRight2,
		  uParentLeft2,
		  uParentRight2);
#endif

		if (uParentLeft2 == uParentRight2)
			{
			NodeIndexToId1[uNodeIndex1] = uInternalNodeId;
			IdToNodeIndex2[uInternalNodeId] = uParentLeft2;
			++uInternalNodeId;
			}
		else
			bIsBachelor1[uNodeIndex1] = true;
		}

	unsigned uDiffCount = 0;
	for (unsigned uNodeIndex = 0; uNodeIndex < uNodeCount; ++uNodeIndex)
		{
		if (bIsBachelor1[uNodeIndex])
			continue;
		if (Tree1.IsRoot(uNodeIndex))
			{
		// Special case: if no bachelors, consider the
		// root a diff.
			if (!bIsBachelor1[uNodeIndex])
				bIsDiff1[uNodeIndex] = true;
			continue;
			}
		const unsigned uParent = Tree1.GetParent(uNodeIndex);
		if (bIsBachelor1[uParent])
			{
			bIsDiff1[uNodeIndex] = true;
			++uDiffCount;
			}
		}

#if	TRACE
	Log("Tree1:\n");
	Log("Node    Id  Bach  Diff  Name\n");
	Log("----  ----  ----  ----  ----\n");
	for (unsigned n = 0; n < uNodeCount; ++n)
		{
		Log("%4u  %4u     %d     %d",
		  n,
		  NodeIndexToId1[n],
		  bIsBachelor1[n],
		  bIsDiff1[n]);
		if (Tree1.IsLeaf(n))
			Log("  %s", Tree1.GetLeafName(n));
		Log("\n");
		}
	Log("\n");
	Log("Tree2:\n");
	Log("Node    Id              Name\n");
	Log("----  ----              ----\n");
	for (unsigned n = 0; n < uNodeCount; ++n)
		{
		Log("%4u                  ", n);
		if (Tree2.IsLeaf(n))
			Log("  %s", Tree2.GetLeafName(n));
		Log("\n");
		}
#endif

	Diffs.CreateRooted();
	const unsigned uDiffsRootIndex = Diffs.GetRootNodeIndex();
	const unsigned uRootIndex1 = Tree1.GetRootNodeIndex();

	for (unsigned n = 0; n < uLeafCount; ++n)
		IdToDiffsLeafNodeIndex[n] = uNodeCount;

	BuildDiffs(Tree1, uRootIndex1, bIsDiff1, Diffs, uDiffsRootIndex,
	  IdToDiffsLeafNodeIndex);

#if TRACE
	Log("\n");
	Log("Diffs:\n");
	Diffs.LogMe();
	Log("\n");
	Log("IdToDiffsLeafNodeIndex:");
	for (unsigned n = 0; n < uLeafCount; ++n)
		{
		if (n%16 == 0)
			Log("\n");
		else
			Log(" ");
		Log("%u=%u", n, IdToDiffsLeafNodeIndex[n]);
		}
	Log("\n");
#endif

	for (unsigned n = 0; n < uLeafCount; ++n)
		if (IdToDiffsLeafNodeIndex[n] == uNodeCount)
			Quit("TreeDiffs check 7");

	delete[] NodeIndexToId1;
	delete[] IdToNodeIndex2;

	delete[] bIsBachelor1;
	delete[] bIsDiff1;
	}