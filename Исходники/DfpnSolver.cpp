size_t DfpnSolver::ComputeMaxChildIndex(const std::vector<DfpnData>&
                                        childrenData) const
{
    HexAssert(!childrenData.empty());

    int numNonLosingChildren = 0;
    for (size_t i = 0; i < childrenData.size(); ++i)
        if (!childrenData[i].m_bounds.IsWinning())
            ++numNonLosingChildren;
    if (numNonLosingChildren < 2)
        return childrenData.size();

    // this needs experimenting!
    int childrenToLookAt = WideningBase() + (int) ceil(numNonLosingChildren
                                                       * WideningFactor());
    // Must examine at least two children when have two or more live,
    // since otherwise delta2 will be set to infinity in SelectChild.
    HexAssert(childrenToLookAt >= 2);

    int numNonLosingSeen = 0;
    for (size_t i = 0; i < childrenData.size(); ++i)
    {
        if (!childrenData[i].m_bounds.IsWinning())
            if (++numNonLosingSeen == childrenToLookAt)
                return i + 1;
    }
    return childrenData.size();
}