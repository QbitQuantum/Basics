CRect CStandardNodePositioning::BoundingRect 
    (const CStandardLayoutNodeInfo* node)
{
    // walk along this branch

    CRect result = node->rect;
    for ( ; node != NULL; node = node->nextInBranch)
    {
        result.UnionRect (result, node->rect);

        // shift sub-branches

        for ( CStandardLayoutNodeInfo* branch = node->firstSubBranch
            ; branch != NULL
            ; branch = branch->nextBranch)
        {
            result.UnionRect (result, BoundingRect (branch));
        }
    }

    return result;
}