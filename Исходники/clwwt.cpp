void CalcClustalWWeights(const Tree &tree, WEIGHT Weights[])
	{
#if	TRACE
	Log("CalcClustalWWeights\n");
	tree.LogMe();
#endif

	const unsigned uLeafCount = tree.GetLeafCount();
	if (0 == uLeafCount)
		return;
	else if (1 == uLeafCount)
		{
		Weights[0] = (WEIGHT) 1.0;
		return;
		}
	else if (2 == uLeafCount)
		{
		Weights[0] = (WEIGHT) 0.5;
		Weights[1] = (WEIGHT) 0.5;
		return;
		}

	if (!tree.IsRooted())
		Quit("CalcClustalWWeights requires rooted tree");

	const unsigned uNodeCount = tree.GetNodeCount();
	unsigned *LeavesUnderNode = new unsigned[uNodeCount];
	memset(LeavesUnderNode, 0, uNodeCount*sizeof(unsigned));

	const unsigned uRootNodeIndex = tree.GetRootNodeIndex();
	unsigned uLeavesUnderRoot = CountLeaves(tree, uRootNodeIndex, LeavesUnderNode);
	if (uLeavesUnderRoot != uLeafCount)
		Quit("WeightsFromTreee: Internal error, root count %u %u",
		  uLeavesUnderRoot, uLeafCount);

#if	TRACE
	Log("Node  Leaves    Length  Strength\n");
	Log("----  ------  --------  --------\n");
	//    1234  123456  12345678  12345678
#endif

	double *Strengths = new double[uNodeCount];
	for (unsigned uNodeIndex = 0; uNodeIndex < uNodeCount; ++uNodeIndex)
		{
		if (tree.IsRoot(uNodeIndex))
			{
			Strengths[uNodeIndex] = 0.0;
			continue;
			}
		const unsigned uParent = tree.GetParent(uNodeIndex);
		const double dLength = tree.GetEdgeLength(uNodeIndex, uParent);
		const unsigned uLeaves = LeavesUnderNode[uNodeIndex];
		const double dStrength = dLength / (double) uLeaves;
		Strengths[uNodeIndex] = dStrength;
#if	TRACE
		Log("%4u  %6u  %8g  %8g\n", uNodeIndex, uLeaves, dLength, dStrength);
#endif
		}

#if	TRACE
	Log("\n");
	Log("                 Seq  Path..Weight\n");
	Log("--------------------  ------------\n");
#endif
	for (unsigned n = 0; n < uLeafCount; ++n)
		{
		const unsigned uLeafNodeIndex = tree.LeafIndexToNodeIndex(n);
#if	TRACE
		Log("%20.20s  %4u ", tree.GetLeafName(uLeafNodeIndex), uLeafNodeIndex);
#endif
		if (!tree.IsLeaf(uLeafNodeIndex))
			Quit("CalcClustalWWeights: leaf");

		double dWeight = 0;
		unsigned uNode = uLeafNodeIndex;
		while (!tree.IsRoot(uNode))
			{
			dWeight += Strengths[uNode];
			uNode = tree.GetParent(uNode);
#if	TRACE
			Log("->%u(%g)", uNode, Strengths[uNode]);
#endif
			}
		if (dWeight < 0.0001)
			{
#if	TRACE
			Log("zero->one");
#endif
			dWeight = 1.0;
			}
		Weights[n] = (WEIGHT) dWeight;
#if	TRACE
		Log(" = %g\n", dWeight);
#endif
		}

	delete[] Strengths;
	delete[] LeavesUnderNode;

	Normalize(Weights, uLeafCount);
	}