//-----------------------------------------------------------------------------
// Trim this surface against the specified shell, in the way that's appropriate
// for the specified Boolean operation type (and which operand we are). We
// also need a pointer to the shell that contains our own surface, since that
// contains our original trim curves.
//-----------------------------------------------------------------------------
SSurface SSurface::MakeCopyTrimAgainst(SShell *parent,
                                       SShell *sha, SShell *shb,
                                       SShell *into,
                                       int type)
{
    bool opA = (parent == sha);
    SShell *agnst = opA ? shb : sha;

    SSurface ret;
    // The returned surface is identical, just the trim curves change
    ret = *this;
    ret.trim = {};

    // First, build a list of the existing trim curves; update them to use
    // the split curves.
    STrimBy *stb;
    for(stb = trim.First(); stb; stb = trim.NextAfter(stb)) {
        STrimBy stn = *stb;
        stn.curve = (parent->curve.FindById(stn.curve))->newH;
        ret.trim.Add(&stn);
    }

    if(type == SShell::AS_DIFFERENCE && !opA) {
        // The second operand of a Boolean difference gets turned inside out
        ret.Reverse();
    }

    // Build up our original trim polygon; remember the coordinates could
    // be changed if we just flipped the surface normal, and we are using
    // the split curves (not the original curves).
    SEdgeList orig = {};
    ret.MakeEdgesInto(into, &orig, AS_UV);
    ret.trim.Clear();
    // which means that we can't necessarily use the old BSP...
    SBspUv *origBsp = SBspUv::From(&orig, &ret);

    // And now intersect the other shell against us
    SEdgeList inter = {};

    SSurface *ss;
    for(ss = agnst->surface.First(); ss; ss = agnst->surface.NextAfter(ss)) {
        SCurve *sc;
        for(sc = into->curve.First(); sc; sc = into->curve.NextAfter(sc)) {
            if(sc->source != SCurve::FROM_INTERSECTION) continue;
            if(opA) {
                if(sc->surfA.v != h.v || sc->surfB.v != ss->h.v) continue;
            } else {
                if(sc->surfB.v != h.v || sc->surfA.v != ss->h.v) continue;
            }

            int i;
            for(i = 1; i < sc->pts.n; i++) {
                Vector a = sc->pts.elem[i-1].p,
                       b = sc->pts.elem[i].p;

                Point2d auv, buv;
                ss->ClosestPointTo(a, &(auv.x), &(auv.y));
                ss->ClosestPointTo(b, &(buv.x), &(buv.y));

                int c = (ss->bsp) ? ss->bsp->ClassifyEdge(auv, buv, ss) : SBspUv::OUTSIDE;
                if(c != SBspUv::OUTSIDE) {
                    Vector ta = Vector::From(0, 0, 0);
                    Vector tb = Vector::From(0, 0, 0);
                    ret.ClosestPointTo(a, &(ta.x), &(ta.y));
                    ret.ClosestPointTo(b, &(tb.x), &(tb.y));

                    Vector tn = ret.NormalAt(ta.x, ta.y);
                    Vector sn = ss->NormalAt(auv.x, auv.y);

                    // We are subtracting the portion of our surface that
                    // lies in the shell, so the in-plane edge normal should
                    // point opposite to the surface normal.
                    bool bkwds = true;
                    if((tn.Cross(b.Minus(a))).Dot(sn) < 0) bkwds = !bkwds;
                    if(type == SShell::AS_DIFFERENCE && !opA) bkwds = !bkwds;
                    if(bkwds) {
                        inter.AddEdge(tb, ta, sc->h.v, 1);
                    } else {
                        inter.AddEdge(ta, tb, sc->h.v, 0);
                    }
                }
            }
        }
    }

    // Record all the points where more than two edges join, which I will call
    // the choosing points. If two edges join at a non-choosing point, then
    // they must either both be kept or both be discarded (since that would
    // otherwise create an open contour).
    SPointList choosing = {};
    SEdge *se;
    for(se = orig.l.First(); se; se = orig.l.NextAfter(se)) {
        choosing.IncrementTagFor(se->a);
        choosing.IncrementTagFor(se->b);
    }
    for(se = inter.l.First(); se; se = inter.l.NextAfter(se)) {
        choosing.IncrementTagFor(se->a);
        choosing.IncrementTagFor(se->b);
    }
    SPoint *sp;
    for(sp = choosing.l.First(); sp; sp = choosing.l.NextAfter(sp)) {
        if(sp->tag == 2) {
            sp->tag = 1;
        } else {
            sp->tag = 0;
        }
    }
    choosing.l.RemoveTagged();

    // The list of edges to trim our new surface, a combination of edges from
    // our original and intersecting edge lists.
    SEdgeList final = {};

    while(orig.l.n > 0) {
        SEdgeList chain = {};
        FindChainAvoiding(&orig, &chain, &choosing);

        // Arbitrarily choose an edge within the chain to classify; they
        // should all be the same, though.
        se = &(chain.l.elem[chain.l.n/2]);

        Point2d auv  = (se->a).ProjectXy(),
                buv  = (se->b).ProjectXy();

        Vector pt, enin, enout, surfn;
        ret.EdgeNormalsWithinSurface(auv, buv, &pt, &enin, &enout, &surfn,
                                        se->auxA, into, sha, shb);

        int indir_shell, outdir_shell, indir_orig, outdir_orig;

        indir_orig  = SShell::INSIDE;
        outdir_orig = SShell::OUTSIDE;

        agnst->ClassifyEdge(&indir_shell, &outdir_shell,
                            ret.PointAt(auv), ret.PointAt(buv), pt,
                            enin, enout, surfn);

        if(KeepEdge(type, opA, indir_shell, outdir_shell,
                               indir_orig,  outdir_orig))
        {
            for(se = chain.l.First(); se; se = chain.l.NextAfter(se)) {
                final.AddEdge(se->a, se->b, se->auxA, se->auxB);
            }
        }
        chain.Clear();
    }