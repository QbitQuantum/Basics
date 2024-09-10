void SPStar::set_shape() {
    // perhaps we should convert all our shapes into LPEs without source path
    // and with knotholders for parameters, then this situation will be handled automatically
    // by disabling the entire stack (including the shape LPE)
    if (hasBrokenPathEffect()) {
        g_warning ("The star shape has unknown LPE on it! Convert to path to make it editable preserving the appearance; editing it as star will remove the bad LPE");

        if (this->getRepr()->attribute("d")) {
            // unconditionally read the curve from d, if any, to preserve appearance
            Geom::PathVector pv = sp_svg_read_pathv(this->getRepr()->attribute("d"));
            SPCurve *cold = new SPCurve(pv);
            this->setCurveInsync( cold, TRUE);
            this->setCurveBeforeLPE(cold);
            cold->unref();
        }

        return;
    }

    SPCurve *c = new SPCurve ();

    bool not_rounded = (fabs (this->rounded) < 1e-4);

    // note that we pass randomized=true to sp_star_get_xy, because the curve must be randomized;
    // other places that call that function (e.g. the knotholder) need the exact point

    // draw 1st segment
    c->moveto(sp_star_get_xy (this, SP_STAR_POINT_KNOT1, 0, true));

    if (this->flatsided == false) {
        if (not_rounded) {
            c->lineto(sp_star_get_xy (this, SP_STAR_POINT_KNOT2, 0, true));
        } else {
            c->curveto(sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, 0, NEXT),
                sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT2, 0, PREV),
                sp_star_get_xy (this, SP_STAR_POINT_KNOT2, 0, true));
        }
    }

    // draw all middle segments
    for (gint i = 1; i < sides; i++) {
        if (not_rounded) {
            c->lineto(sp_star_get_xy (this, SP_STAR_POINT_KNOT1, i, true));
        } else {
            if (this->flatsided == false) {
                c->curveto(sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT2, i - 1, NEXT),
                        sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, i, PREV),
                        sp_star_get_xy (this, SP_STAR_POINT_KNOT1, i, true));
            } else {
                c->curveto(sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, i - 1, NEXT),
                        sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, i, PREV),
                        sp_star_get_xy (this, SP_STAR_POINT_KNOT1, i, true));
            }
        }

        if (this->flatsided == false) {
            if (not_rounded) {
                       c->lineto(sp_star_get_xy (this, SP_STAR_POINT_KNOT2, i, true));
            } else {
                c->curveto(sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, i, NEXT),
                    sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT2, i, PREV),
                    sp_star_get_xy (this, SP_STAR_POINT_KNOT2, i, true));
            }
        }
    }

    // draw last segment
	if (!not_rounded) {
		if (this->flatsided == false) {
			c->curveto(sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT2, sides - 1, NEXT),
				sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, 0, PREV),
				sp_star_get_xy (this, SP_STAR_POINT_KNOT1, 0, true));
		} else {
			c->curveto(sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, sides - 1, NEXT),
				sp_star_get_curvepoint (this, SP_STAR_POINT_KNOT1, 0, PREV),
				sp_star_get_xy (this, SP_STAR_POINT_KNOT1, 0, true));
		}
	}

    c->closepath();

    /* Reset the shape'scurve to the "original_curve"
     * This is very important for LPEs to work properly! (the bbox might be recalculated depending on the curve in shape)*/
    this->setCurveInsync( c, TRUE);
    this->setCurveBeforeLPE( c );

    if (hasPathEffect() && pathEffectsEnabled()) {
        SPCurve *c_lpe = c->copy();
        bool success = this->performPathEffect(c_lpe);

        if (success) {
            this->setCurveInsync( c_lpe, TRUE);
        } 

        c_lpe->unref();
    }

    c->unref();
}