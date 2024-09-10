void Entity::GenerateBezierCurves(SBezierList *sbl) {
    SBezier sb;

    int i = sbl->l.n;

    switch(type) {
        case LINE_SEGMENT: {
            Vector a = SK.GetEntity(point[0])->PointGetNum();
            Vector b = SK.GetEntity(point[1])->PointGetNum();
            sb = SBezier::From(a, b);
            sbl->l.Add(&sb);
            break;
        }
        case CUBIC:
            ComputeInterpolatingSpline(sbl, false);
            break;

        case CUBIC_PERIODIC:
            ComputeInterpolatingSpline(sbl, true);
            break;

        case CIRCLE:
        case ARC_OF_CIRCLE: {
            Vector center = SK.GetEntity(point[0])->PointGetNum();
            Quaternion q = SK.GetEntity(normal)->NormalGetNum();
            Vector u = q.RotationU(), v = q.RotationV();
            double r = CircleGetRadiusNum();
            double thetaa, thetab, dtheta;

            if(r < LENGTH_EPS) {
                // If a circle or an arc gets dragged through zero radius,
                // then we just don't generate anything.
                break;
            }

            if(type == CIRCLE) {
                thetaa = 0;
                thetab = 2*PI;
                dtheta = 2*PI;
            } else {
                ArcGetAngles(&thetaa, &thetab, &dtheta);
            }
            int i, n;
            if(dtheta > (3*PI/2 + 0.01)) {
                n = 4;
            } else if(dtheta > (PI + 0.01)) {
                n = 3;
            } else if(dtheta > (PI/2 + 0.01)) {
                n = 2;
            } else {
                n = 1;
            }
            dtheta /= n;

            for(i = 0; i < n; i++) {
                double s, c;

                c = cos(thetaa);
                s = sin(thetaa);
                // The start point of the curve, and the tangent vector at
                // that start point.
                Vector p0 = center.Plus(u.ScaledBy( r*c)).Plus(v.ScaledBy(r*s)),
                       t0 =             u.ScaledBy(-r*s). Plus(v.ScaledBy(r*c));

                thetaa += dtheta;

                c = cos(thetaa);
                s = sin(thetaa);
                Vector p2 = center.Plus(u.ScaledBy( r*c)).Plus(v.ScaledBy(r*s)),
                       t2 =             u.ScaledBy(-r*s). Plus(v.ScaledBy(r*c));

                // The control point must lie on both tangents.
                Vector p1 = Vector::AtIntersectionOfLines(p0, p0.Plus(t0),
                                                          p2, p2.Plus(t2),
                                                          NULL);

                SBezier sb = SBezier::From(p0, p1, p2);
                sb.weight[1] = cos(dtheta/2);
                sbl->l.Add(&sb);
            }
            break;
        }

        case TTF_TEXT: {
            Vector topLeft = SK.GetEntity(point[0])->PointGetNum();
            Vector botLeft = SK.GetEntity(point[1])->PointGetNum();
            Vector n = Normal()->NormalN();
            Vector v = topLeft.Minus(botLeft);
            Vector u = (v.Cross(n)).WithMagnitude(v.Magnitude());

            SS.fonts.PlotString(font.str, str.str, 0, sbl, botLeft, u, v);
            break;
        }

        default:
            // Not a problem, points and normals and such don't generate curves
            break;
    }

    // Record our style for all of the Beziers that we just created.
    for(; i < sbl->l.n; i++) {
        sbl->l.elem[i].auxA = style.v;
    }
}