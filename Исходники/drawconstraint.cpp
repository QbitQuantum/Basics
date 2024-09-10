void Constraint::DoArcForAngle(Vector a0, Vector da, Vector b0, Vector db,
                                   Vector offset, Vector *ref)
{
    Vector gr = SS.GW.projRight.ScaledBy(1/SS.GW.scale);
    Vector gu = SS.GW.projUp.ScaledBy(1/SS.GW.scale);

    if(workplane.v != Entity::FREE_IN_3D.v) {
        a0 = a0.ProjectInto(workplane);
        b0 = b0.ProjectInto(workplane);
        da = da.ProjectVectorInto(workplane);
        db = db.ProjectVectorInto(workplane);
    }

    bool skew;
    Vector pi = Vector::AtIntersectionOfLines(a0, a0.Plus(da),
                                              b0, b0.Plus(db), &skew);

    if(!skew) {
        *ref = pi.Plus(offset);
        // We draw in a coordinate system centered at the intersection point.
        // One basis vector is da, and the other is normal to da and in
        // the plane that contains our lines (so normal to its normal).
        Vector dna = (da.Cross(db)).Cross(da);
        da = da.WithMagnitude(1); dna = dna.WithMagnitude(1);

        Vector rm = (*ref).Minus(pi);
        double rda = rm.Dot(da), rdna = rm.Dot(dna);
        double r = sqrt(rda*rda + rdna*rdna);
        double c = (da.Dot(db))/(da.Magnitude()*db.Magnitude());
        double thetaf = acos(c);

        Vector m = da.ScaledBy(cos(thetaf/2)).Plus(
                   dna.ScaledBy(sin(thetaf/2)));
        if(m.Dot(rm) < 0) {
            da = da.ScaledBy(-1); dna = dna.ScaledBy(-1);
        }

        Vector prev = da.ScaledBy(r).Plus(pi);
        int i, n = 30;
        for(i = 0; i <= n; i++) {
            double theta = (i*thetaf)/n;
            Vector p = da. ScaledBy(r*cos(theta)).Plus(
                       dna.ScaledBy(r*sin(theta))).Plus(pi);
            LineDrawOrGetDistance(prev, p);
            prev = p;
        }

        // The elliptical approximation isn't exactly right, but the correct
        // calculation (against the bounding box of the text) would be rather
        // complex and this looks pretty good.
        double tl = atan2(rm.Dot(gu), rm.Dot(gr));
        double adj = EllipticalInterpolation(
            ssglStrWidth(Label(), DEFAULT_TEXT_HEIGHT)/2,
            ssglStrHeight(DEFAULT_TEXT_HEIGHT)/2,
            tl);
        *ref = (*ref).Plus(rm.WithMagnitude(adj + 3/SS.GW.scale));
    } else {
        // The lines are skew; no wonderful way to illustrate that.
        *ref = a0.Plus(b0);
        *ref = (*ref).ScaledBy(0.5).Plus(disp.offset);
        gu = gu.WithMagnitude(1);
        Vector trans =
            (*ref).Plus(gu.ScaledBy(-1.5*ssglStrHeight(DEFAULT_TEXT_HEIGHT)));
        ssglWriteTextRefCenter("angle between skew lines", DEFAULT_TEXT_HEIGHT,
            trans, gr, gu, LineCallback, this);
    }
}