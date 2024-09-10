void SkPathStroker::cubic_to(const SkPoint pts[4],
                      const SkVector& normalAB, const SkVector& unitNormalAB,
                      SkVector* normalCD, SkVector* unitNormalCD,
                      int subDivide) {
    SkVector    ab = pts[1] - pts[0];
    SkVector    cd = pts[3] - pts[2];
    SkVector    normalBC, unitNormalBC;

    bool    degenerateAB = degenerate_vector(ab);
    bool    degenerateCD = degenerate_vector(cd);

    if (degenerateAB && degenerateCD) {
DRAW_LINE:
        this->line_to(pts[3], normalAB);
        *normalCD = normalAB;
        *unitNormalCD = unitNormalAB;
        return;
    }

    if (degenerateAB) {
        ab = pts[2] - pts[0];
        degenerateAB = degenerate_vector(ab);
    }
    if (degenerateCD) {
        cd = pts[3] - pts[1];
        degenerateCD = degenerate_vector(cd);
    }
    if (degenerateAB || degenerateCD) {
        goto DRAW_LINE;
    }
    SkAssertResult(set_normal_unitnormal(cd, fRadius, normalCD, unitNormalCD));
    bool degenerateBC = !set_normal_unitnormal(pts[1], pts[2], fRadius,
                                               &normalBC, &unitNormalBC);

    if (degenerateBC || normals_too_curvy(unitNormalAB, unitNormalBC) ||
             normals_too_curvy(unitNormalBC, *unitNormalCD)) {
        // subdivide if we can
        if (--subDivide < 0) {
            goto DRAW_LINE;
        }
        SkPoint     tmp[7];
        SkVector    norm, unit, dummy, unitDummy;

        SkChopCubicAtHalf(pts, tmp);
        this->cubic_to(&tmp[0], normalAB, unitNormalAB, &norm, &unit,
                       subDivide);
        // we use dummys since we already have a valid (and more accurate)
        // normals for CD
        this->cubic_to(&tmp[3], norm, unit, &dummy, &unitDummy, subDivide);
    } else {
        SkVector    normalB, normalC;
        
        // need normals to inset/outset the off-curve pts B and C

        if (0) {    // this is normal to the line between our adjacent pts
            normalB = pts[2] - pts[0];
            normalB.rotateCCW();
            SkAssertResult(normalB.setLength(fRadius));

            normalC = pts[3] - pts[1];
            normalC.rotateCCW();
            SkAssertResult(normalC.setLength(fRadius));
        } else {    // miter-join
            SkVector    unitBC = pts[2] - pts[1];
            unitBC.normalize();
            unitBC.rotateCCW();

            normalB = unitNormalAB + unitBC;
            normalC = *unitNormalCD + unitBC;

            SkScalar dot = SkPoint::DotProduct(unitNormalAB, unitBC);
            SkAssertResult(normalB.setLength(SkScalarDiv(fRadius,
                                        SkScalarSqrt((SK_Scalar1 + dot)/2))));
            dot = SkPoint::DotProduct(*unitNormalCD, unitBC);
            SkAssertResult(normalC.setLength(SkScalarDiv(fRadius,
                                        SkScalarSqrt((SK_Scalar1 + dot)/2))));
        }

        fOuter.cubicTo( pts[1].fX + normalB.fX, pts[1].fY + normalB.fY,
                        pts[2].fX + normalC.fX, pts[2].fY + normalC.fY,
                        pts[3].fX + normalCD->fX, pts[3].fY + normalCD->fY);

        fInner.cubicTo( pts[1].fX - normalB.fX, pts[1].fY - normalB.fY,
                        pts[2].fX - normalC.fX, pts[2].fY - normalC.fY,
                        pts[3].fX - normalCD->fX, pts[3].fY - normalCD->fY);
    }
}