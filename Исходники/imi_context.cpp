        fr.m_wstr.push_back(ch);

    fr.m_lexiconStates.push_back(TLexiconState(i, wid));
}

void
CIMIContext::_forwardTail(unsigned i, unsigned j)
{
    CLatticeFrame &fr = m_lattice[j];
    fr.m_type = CLatticeFrame::TAIL;

    fr.m_lexiconStates.push_back(TLexiconState(i, ENDING_WORD_ID));
}

static double exp2_tbl[32] = {
    exp2(-0), exp2(-1), exp2(-2), exp2(-3), exp2(-4), exp2(-5), exp2(-6), exp2(-7),
    exp2(-8), exp2(-9), exp2(-10), exp2(-11), exp2(-12), exp2(-13), exp2(-14),
    exp2(-15), exp2(-16), exp2(-17), exp2(-18), exp2(-19), exp2(-20), exp2(-21),
    exp2(-22), exp2(-23), exp2(-24), exp2(-25), exp2(-26), exp2(-27), exp2(-28),
    exp2(-29), exp2(-30), exp2(-31)
};

bool
CIMIContext::searchFrom(unsigned idx)
{
    bool affectCandidates = (idx <= m_candiEnds);

    for (; idx <= m_tailIdx; ++idx) {
        CLatticeFrame &fr = m_lattice[idx];

        if (fr.m_type == CLatticeFrame::UNUSED)