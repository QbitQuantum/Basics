//-----------------------------------------------------------------------------
// A single point must be selected when this function is called. We find two
// non-construction line segments that join at this point, and create a
// tangent arc joining them.
//-----------------------------------------------------------------------------
void GraphicsWindow::MakeTangentArc(void) {
    if(!LockedInWorkplane()) {
        Error("Must be sketching in workplane to create tangent "
              "arc.");
        return;
    }

    // The point corresponding to the vertex to be rounded.
    Vector pshared = SK.GetEntity(gs.point[0])->PointGetNum();
    ClearSelection();

    // First, find two requests (that are not construction, and that are
    // in our group and workplane) that generate entities that have an
    // endpoint at our vertex to be rounded.
    int i, c = 0;
    Entity *ent[2];
    Request *req[2];
    hRequest hreq[2];
    hEntity hent[2];
    bool pointf[2];
    for(i = 0; i < SK.request.n; i++) {
        Request *r = &(SK.request.elem[i]);
        if(r->group.v != activeGroup.v) continue;
        if(r->workplane.v != ActiveWorkplane().v) continue;
        if(r->construction) continue;
        if(r->type != Request::LINE_SEGMENT &&
           r->type != Request::ARC_OF_CIRCLE)
        {
            continue;
        }

        Entity *e = SK.GetEntity(r->h.entity(0));
        Vector ps = e->EndpointStart(),
               pf = e->EndpointFinish();
        
        if(ps.Equals(pshared) || pf.Equals(pshared)) {
            if(c < 2) {
                // We record the entity and request and their handles,
                // and whether the vertex to be rounded is the start or
                // finish of this entity.
                ent[c] = e;
                hent[c] = e->h;
                req[c] = r;
                hreq[c] = r->h;
                pointf[c] = (pf.Equals(pshared));
            }
            c++;
        }
    }
    if(c != 2) {
        Error("To create a tangent arc, select a point where two "
              "non-construction lines or cicles in this group and "
              "workplane join.");
        return;
    }

    Entity *wrkpl = SK.GetEntity(ActiveWorkplane());
    Vector wn = wrkpl->Normal()->NormalN();

    // Based on these two entities, we make the objects that we'll use to
    // numerically find the tangent arc.
    ParametricCurve pc[2];
    pc[0].MakeFromEntity(ent[0]->h, pointf[0]);
    pc[1].MakeFromEntity(ent[1]->h, pointf[1]);

    // And thereafter we mustn't touch the entity or req ptrs,
    // because the new requests/entities we add might force a
    // realloc.
    memset(ent, 0, sizeof(ent));
    memset(req, 0, sizeof(req));

    Vector pinter;
    double r, vv;
    // We now do Newton iterations to find the tangent arc, and its positions
    // t back along the two curves, starting from shared point of the curves
    // at t = 0. Lots of iterations helps convergence, and this is still
    // ~10 ms for everything.
    int iters = 1000;
    double t[2] = { 0, 0 }, tp[2];
    for(i = 0; i < iters + 20; i++) {
        Vector p0 = pc[0].PointAt(t[0]),
               p1 = pc[1].PointAt(t[1]),
               t0 = pc[0].TangentAt(t[0]),
               t1 = pc[1].TangentAt(t[1]);

        pinter = Vector::AtIntersectionOfLines(p0, p0.Plus(t0),
                                               p1, p1.Plus(t1),
                                               NULL, NULL, NULL);

        // The sign of vv determines whether shortest distance is
        // clockwise or anti-clockwise.
        Vector v = (wn.Cross(t0)).WithMagnitude(1);
        vv = t1.Dot(v);

        double dot = (t0.WithMagnitude(1)).Dot(t1.WithMagnitude(1));
        double theta = acos(dot);

        if(SS.tangentArcManual) {
            r = SS.tangentArcRadius;
        } else {
            r = 200/scale;
            // Set the radius so that no more than one third of the 
            // line segment disappears.
            r = min(r, pc[0].LengthForAuto()*tan(theta/2));
            r = min(r, pc[1].LengthForAuto()*tan(theta/2));;
        }
        // We are source-stepping the radius, to improve convergence. So
        // ramp that for most of the iterations, and then do a few at
        // the end with that constant for polishing.
        if(i < iters) {
            r *= 0.1 + 0.9*i/((double)iters);
        }

        // The distance from the intersection of the lines to the endpoint
        // of the arc, along each line.
        double el = r/tan(theta/2);

        // Compute the endpoints of the arc, for each curve
        Vector pa0 = pinter.Plus(t0.WithMagnitude(el)),
               pa1 = pinter.Plus(t1.WithMagnitude(el));

        tp[0] = t[0];
        tp[1] = t[1];

        // And convert those points to parameter values along the curve.
        t[0] += (pa0.Minus(p0)).DivPivoting(t0);
        t[1] += (pa1.Minus(p1)).DivPivoting(t1);
    }

    // Stupid check for convergence, and for an out of range result (as
    // we would get, for example, if the line is too short to fit the
    // rounding arc).
    if(fabs(tp[0] - t[0]) > 1e-3 || fabs(tp[1] - t[1]) > 1e-3 ||
        t[0] < 0.01 || t[1] < 0.01 ||
        t[0] > 0.99 || t[1] > 0.99 ||
        isnan(t[0]) || isnan(t[1]))
    {
        Error("Couldn't round this corner. Try a smaller radius, or try "
              "creating the desired geometry by hand with tangency "
              "constraints.");
        return;
    }

    // Compute the location of the center of the arc
    Vector center = pc[0].PointAt(t[0]),
           v0inter = pinter.Minus(center);
    int a, b;
    if(vv < 0) {
        a = 1; b = 2;
        center = center.Minus(v0inter.Cross(wn).WithMagnitude(r));
    } else {
        a = 2; b = 1;
        center = center.Plus(v0inter.Cross(wn).WithMagnitude(r));
    }

    SS.UndoRemember();

    hRequest harc = AddRequest(Request::ARC_OF_CIRCLE, false);
    Entity *earc = SK.GetEntity(harc.entity(0));
    hEntity hearc = earc->h;

    SK.GetEntity(earc->point[0])->PointForceTo(center);
    SK.GetEntity(earc->point[a])->PointForceTo(pc[0].PointAt(t[0]));
    SK.GetEntity(earc->point[b])->PointForceTo(pc[1].PointAt(t[1]));
    
    earc = NULL;

    pc[0].CreateRequestTrimmedTo(t[0], !SS.tangentArcDeleteOld,
                hent[0], hearc, (b == 1));
    pc[1].CreateRequestTrimmedTo(t[1], !SS.tangentArcDeleteOld,
                hent[1], hearc, (a == 1));

    // Now either make the original entities construction, or delete them
    // entirely, according to user preference.
    Request *re;
    SK.request.ClearTags();
    for(re = SK.request.First(); re; re = SK.request.NextAfter(re)) {
        if(re->h.v == hreq[0].v || re->h.v == hreq[1].v) {
            if(SS.tangentArcDeleteOld) {
                re->tag = 1;
            } else {
                re->construction = true;
            }
        }
    }
    if(SS.tangentArcDeleteOld) {
        DeleteTaggedRequests();
    }

    SS.later.generateAll = true;
}