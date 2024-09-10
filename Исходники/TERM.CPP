void MatchGraph::UNPAIR_ALL ()
{
    long u;

    for (v=1; v <= U; ++v) {
	if (BASE[(int)v] != v || LASTVTX[(int)v] == v)
	    continue;
	nextu = v;
	NEXTVTX[(int)LASTVTX[(int)nextu]] = DUMMYVERTEX;
	while (1) {
	    u = nextu;
	    nextu = NEXTVTX[(int)nextu];
	    UNLINK (u);
	    if (LASTVTX[(int)u] != u) {
		f = (LASTEDGE[2] == OPPEDGE(e)) ? LASTEDGE[1] : LASTEDGE[2];
		NEXTVTX[(int)LASTVTX[(int)BEND(f)]] = u;
	    }
	    newbase = BMATE (BMATE(u));
	    if (newbase != DUMMYVERTEX && newbase != u) {
		LINK[(int)u] = -DUMMYEDGE;
		REMATCH (newbase, MATE[(int)u]);
	    }
	    while (LASTVTX[(int)nextu] == nextu && nextu != DUMMYVERTEX)
		nextu = NEXTVTX[(int)nextu];
	    if (LASTVTX[(int)nextu] == nextu && nextu == DUMMYVERTEX)
		break;
	}
    }
}