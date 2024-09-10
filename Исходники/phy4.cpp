void Tree::PruneTree(const Tree &tree, unsigned Subfams[],
                     unsigned uSubfamCount)
{
    if (!tree.IsRooted())
        Quit("Tree::PruneTree: requires rooted tree");

    Clear();

    m_uNodeCount = 2*uSubfamCount - 1;
    InitCache(m_uNodeCount);

    const unsigned uUnprunedNodeCount = tree.GetNodeCount();

    unsigned *uUnprunedToPrunedIndex = new unsigned[uUnprunedNodeCount];
    unsigned *uPrunedToUnprunedIndex = new unsigned[m_uNodeCount];

    for (unsigned n = 0; n < uUnprunedNodeCount; ++n)
        uUnprunedToPrunedIndex[n] = NULL_NEIGHBOR;

    for (unsigned n = 0; n < m_uNodeCount; ++n)
        uPrunedToUnprunedIndex[n] = NULL_NEIGHBOR;

// Create mapping between unpruned and pruned node indexes
    unsigned uInternalNodeIndex = uSubfamCount;
    for (unsigned uSubfamIndex = 0; uSubfamIndex < uSubfamCount; ++uSubfamIndex)
    {
        unsigned uUnprunedNodeIndex = Subfams[uSubfamIndex];
        uUnprunedToPrunedIndex[uUnprunedNodeIndex] = uSubfamIndex;
        uPrunedToUnprunedIndex[uSubfamIndex] = uUnprunedNodeIndex;
        for (;;)
        {
            uUnprunedNodeIndex = tree.GetParent(uUnprunedNodeIndex);
            if (tree.IsRoot(uUnprunedNodeIndex))
                break;

            // Already visited this node?
            if (NULL_NEIGHBOR != uUnprunedToPrunedIndex[uUnprunedNodeIndex])
                break;

            uUnprunedToPrunedIndex[uUnprunedNodeIndex] = uInternalNodeIndex;
            uPrunedToUnprunedIndex[uInternalNodeIndex] = uUnprunedNodeIndex;

            ++uInternalNodeIndex;
        }
    }

    const unsigned uUnprunedRootIndex = tree.GetRootNodeIndex();
    uUnprunedToPrunedIndex[uUnprunedRootIndex] = uInternalNodeIndex;
    uPrunedToUnprunedIndex[uInternalNodeIndex] = uUnprunedRootIndex;

#if	TRACE
    {
        Log("Pruned to unpruned:\n");
        for (unsigned i = 0; i < m_uNodeCount; ++i)
            Log(" [%u]=%u", i, uPrunedToUnprunedIndex[i]);
        Log("\n");
        Log("Unpruned to pruned:\n");
        for (unsigned i = 0; i < uUnprunedNodeCount; ++i)
        {
            unsigned n = uUnprunedToPrunedIndex[i];
            if (n != NULL_NEIGHBOR)
                Log(" [%u]=%u", i, n);
        }
        Log("\n");
    }
#endif

    if (uInternalNodeIndex != m_uNodeCount - 1)
        Quit("Tree::PruneTree, Internal error");

// Nodes 0, 1 ... are the leaves
    for (unsigned uSubfamIndex = 0; uSubfamIndex < uSubfamCount; ++uSubfamIndex)
    {
        char szName[32];
        sprintf(szName, "Subfam_%u", uSubfamIndex + 1);
        m_ptrName[uSubfamIndex] = strsave(szName);
    }

    for (unsigned uPrunedNodeIndex = uSubfamCount; uPrunedNodeIndex < m_uNodeCount;
            ++uPrunedNodeIndex)
    {
        unsigned uUnprunedNodeIndex = uPrunedToUnprunedIndex[uPrunedNodeIndex];

        const unsigned uUnprunedLeft = tree.GetLeft(uUnprunedNodeIndex);
        const unsigned uUnprunedRight = tree.GetRight(uUnprunedNodeIndex);

        const unsigned uPrunedLeft = uUnprunedToPrunedIndex[uUnprunedLeft];
        const unsigned uPrunedRight = uUnprunedToPrunedIndex[uUnprunedRight];

        const double dLeftLength =
            tree.GetEdgeLength(uUnprunedNodeIndex, uUnprunedLeft);
        const double dRightLength =
            tree.GetEdgeLength(uUnprunedNodeIndex, uUnprunedRight);

        m_uNeighbor2[uPrunedNodeIndex] = uPrunedLeft;
        m_uNeighbor3[uPrunedNodeIndex] = uPrunedRight;

        m_dEdgeLength1[uPrunedLeft] = dLeftLength;
        m_dEdgeLength1[uPrunedRight] = dRightLength;

        m_uNeighbor1[uPrunedLeft] = uPrunedNodeIndex;
        m_uNeighbor1[uPrunedRight] = uPrunedNodeIndex;

        m_bHasEdgeLength1[uPrunedLeft] = true;
        m_bHasEdgeLength1[uPrunedRight] = true;

        m_dEdgeLength2[uPrunedNodeIndex] = dLeftLength;
        m_dEdgeLength3[uPrunedNodeIndex] = dRightLength;

        m_bHasEdgeLength2[uPrunedNodeIndex] = true;
        m_bHasEdgeLength3[uPrunedNodeIndex] = true;
    }

    m_uRootNodeIndex = uUnprunedToPrunedIndex[uUnprunedRootIndex];

    m_bRooted = true;

    Validate();

    delete[] uUnprunedToPrunedIndex;
}