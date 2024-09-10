/**
 * Intersect a ray with a revolve.  If an intersection occurs, a struct
 * seg will be acquired and filled in.
 *
 * Returns -
 * 0 MISS
 * >0 HIT
 */
int
rt_revolve_shot(struct soltab *stp, struct xray *rp, struct application *ap, struct seg *seghead)
{
    struct revolve_specific *rev =
	(struct revolve_specific *)stp->st_specific;
    struct seg *segp;

    struct hit *hitp;
    struct hit *hits[MAX_HITS], hit[MAX_HITS];

    size_t i, j, nseg, nhits;
    int in, out;

    fastf_t k, m, h, aa, bb;
    point_t dp, pr, xlated;
    vect_t vr, ur, norm, normS, normE;

    fastf_t start, end, angle;

    vect_t dir;
    point_t hit1, hit2;
    point2d_t hit2d, pt1, pt2;
    fastf_t a, b, c, disc, k1, k2, t1, t2;
    uint32_t *lng;
    struct line_seg *lsg;
    struct carc_seg *csg;

    nhits = 0;

    for (i=0; i<MAX_HITS; i++) hits[i] = &hit[i];

    vr[X] = VDOT(rev->xUnit, rp->r_dir);
    vr[Y] = VDOT(rev->yUnit, rp->r_dir);
    vr[Z] = VDOT(rev->zUnit, rp->r_dir);

    VSUB2(xlated, rp->r_pt, rev->v3d);
    pr[X] = VDOT(rev->xUnit, xlated);
    pr[Y] = VDOT(rev->yUnit, xlated);
    pr[Z] = VDOT(rev->zUnit, xlated);

    VMOVE(ur, vr);
    VUNITIZE(ur);

    if (rev->ang < M_2PI) {
	VREVERSE(normS, rev->yUnit);	/* start normal */
	start = (VDOT(normS, rev->v3d) - VDOT(normS, rp->r_pt)) / VDOT(normS, rp->r_dir);

	VCROSS(normE, rev->zUnit, rev->rEnd);	/* end normal */
	end = (VDOT(normE, rev->v3d) - VDOT(normE, rp->r_pt)) / VDOT(normE, rp->r_dir);

	VJOIN1(hit1, pr, start, vr);
	hit2d[Y] = hit1[Z];
	hit2d[X] = sqrt(hit1[X]*hit1[X] + hit1[Y]*hit1[Y]);

	VJOIN1(hit2, xlated, start, rp->r_dir);
	if (VDOT(rev->xUnit, hit2) < 0) {
	    /* set the sign of the 2D point's x coord */
	    hit2d[X] = -hit2d[X];
	}

	if (rt_sketch_contains(rev->skt, hit2d)) {
	    hit2d[X] = -hit2d[X];
	    if (rev->ang > M_PI && rt_sketch_contains(rev->skt, hit2d)) {
		/* skip it */
	    } else {
		hitp = hits[nhits++];
		hitp->hit_magic = RT_HIT_MAGIC;
		hitp->hit_dist = start;
		hitp->hit_surfno = (hit2d[X]>0) ? START_FACE_NEG : START_FACE_POS;
		VSET(hitp->hit_vpriv, -hit2d[X], hit2d[Y], 0);
	    }
	}

	VJOIN1(hit1, pr, end, vr);
	hit2d[Y] = hit1[Z];
	hit2d[X] = sqrt(hit1[X]*hit1[X] + hit1[Y]*hit1[Y]);

	VJOIN1(hit2, xlated, end, rp->r_dir);
	if (VDOT(rev->rEnd, hit2) < 0) {
	    /* set the sign of the 2D point's x coord */
	    hit2d[X] = -hit2d[X];
	}

	if (rt_sketch_contains(rev->skt, hit2d)) {
	    hit2d[X] = -hit2d[X];
	    if (rev->ang > M_PI && rt_sketch_contains(rev->skt, hit2d)) {
		/* skip it */
	    } else {
		if (nhits >= MAX_HITS) return -1; /* too many hits */
		hitp = hits[nhits++];
		hitp->hit_magic = RT_HIT_MAGIC;
		hitp->hit_dist = end;
		hitp->hit_surfno = (hit2d[X]>0) ? END_FACE_NEG : END_FACE_POS;
		VSET(hitp->hit_vpriv, -hit2d[X], hit2d[Y], 0);
	    }
	}
    }

    /**
     * calculate hyperbola parameters
     *
     * [ (x*x) / aa^2 ] - [ (y-h)^2 / bb^2 ] = 1
     *
     * x = aa cosh(t - k);
     * y = h + bb sinh(t - k);
     */

    VREVERSE(dp, pr);
    VSET(norm, ur[X], ur[Y], 0);

    k = VDOT(dp, norm) / VDOT(ur, norm);
    h = pr[Z] + k*vr[Z];

    if (NEAR_EQUAL(fabs(ur[Z]), 1.0, RT_DOT_TOL)) {
	aa = sqrt(pr[X]*pr[X] + pr[Y]*pr[Y]);
	bb = MAX_FASTF;
    } else {
	aa = sqrt((pr[X] + k*vr[X])*(pr[X] + k*vr[X]) + (pr[Y] + k*vr[Y])*(pr[Y] + k*vr[Y]));
	bb = sqrt(aa*aa * (1.0/(1 - ur[Z]*ur[Z]) - 1.0));
    }

    /**
     * if (ur[Z] == 1) {
     *	    bb = inf;
     *	    // ray becomes a line parallel to sketch's y-axis instead of a hyberbola
     * }
     * if (ur[Z] == 0) {
     *	    bb = 0;
     *	    // ray becomes a line parallel to sketch's x-axis instead of a hyperbola
     *	    // all hits must have x > aa
     * }
     */

    /* handle open sketches */
    if (!NEAR_ZERO(ur[Z], RT_DOT_TOL)) {
	for (i=0; i<rev->skt->vert_count && rev->ends[i] != -1; i++) {
	    V2MOVE(pt1, rev->skt->verts[rev->ends[i]]);
	    hit2d[Y] = pt1[Y];
	    if (NEAR_EQUAL(fabs(ur[Z]), 1.0, RT_DOT_TOL)) {
		/* ur[Z] == 1 */
		hit2d[X] = aa;
	    } else {
		hit2d[X] = aa*sqrt((hit2d[Y]-h)*(hit2d[Y]-h)/(bb*bb) + 1);
	    }
	    if (pt1[X] < 0) hit2d[X] = -fabs(hit2d[X]);
	    if (fabs(hit2d[X]) < fabs(pt1[X])) {
		/* valid hit */
		if (nhits >= MAX_HITS) return -1; /* too many hits */
		hitp = hits[nhits++];
		hitp->hit_magic = RT_HIT_MAGIC;
		hitp->hit_dist = (hit2d[Y] - pr[Z]) / vr[Z];
		hitp->hit_surfno = HORIZ_SURF;
		VJOIN1(hitp->hit_vpriv, pr, hitp->hit_dist, vr);
		hitp->hit_point[X] = hit2d[X];
		hitp->hit_point[Y] = hit2d[Y];
		hitp->hit_point[Z] = 0;

		angle = atan2(hitp->hit_vpriv[Y], hitp->hit_vpriv[X]);
		if (pt1[X] < 0) {
		    angle += M_PI;
		} else if (angle < 0) {
		    angle += M_2PI;
		}
		hit2d[X] = -hit2d[X];
		if (angle > rev->ang) {
		    nhits--;
		    continue;
		} else if ((angle + M_PI < rev->ang || angle - M_PI > 0)
			   && rt_sketch_contains(rev->skt, hit2d)
			   && hit2d[X] > 0) {
		    nhits--;
		    continue;
		}
		/* X and Y are used for uv(), Z is used for norm() */
		hitp->hit_vpriv[X] = pt1[X];
		hitp->hit_vpriv[Y] = angle;
		if (i+1 < rev->skt->vert_count && rev->ends[i+1] != -1 &&
		    NEAR_EQUAL(rev->skt->verts[rev->ends[i]][Y],
			       rev->skt->verts[rev->ends[i+1]][Y], SMALL)) {
		    hitp->hit_vpriv[Z] = rev->skt->verts[rev->ends[i+1]][X];
		    i++;
		    if (fabs(hit2d[X]) < fabs(hitp->hit_vpriv[Z])) {
			nhits--;
		    }
		} else {
		    hitp->hit_vpriv[Z] = 0;
		}
	    }
	}
    }

    /* find hyperbola intersection with each sketch segment */
    nseg = rev->skt->curve.count;
    for (i=0; i<nseg; i++) {
	lng = (uint32_t *)rev->skt->curve.segment[i];

	switch (*lng) {
	    case CURVE_LSEG_MAGIC:
		lsg = (struct line_seg *)lng;
		V2MOVE(pt1, rev->skt->verts[lsg->start]);
		V2MOVE(pt2, rev->skt->verts[lsg->end]);
		V2SUB2(dir, pt2, pt1);
		if (ZERO(dir[X])) {
		    m = 1.0;
		} else {
		    m = dir[Y] / dir[X];
		}

		if (NEAR_EQUAL(fabs(ur[Z]), 1.0, RT_DOT_TOL)) {
		    /* ray is vertical line at x=aa */
		    if (FMIN(pt1[X], pt2[X]) < aa && aa < FMAX(pt1[X], pt2[X])) {
			/* check the positive side of the sketch (x > 0) */
			k1 = (m * (aa - pt1[X]) + pt1[Y] - pr[Z]) / vr[Z];
			VJOIN1(hit1, pr, k1, vr);
			angle = atan2(hit1[Y], hit1[X]);
			hit2d[X] = -aa;		/* use neg to check for overlap in contains() */
			hit2d[Y] = hit1[Z];
			if (angle < 0) {
			    angle += M_2PI;
			}
			if (angle < rev->ang &&
			    !((angle + M_PI < rev->ang || angle - M_PI > 0)
			      && rt_sketch_contains(rev->skt, hit2d))) {
			    if (nhits >= MAX_HITS) return -1; /* too many hits */
			    hitp = hits[nhits++];
			    hitp->hit_point[X] = -hit2d[X];
			    hitp->hit_point[Y] = hit2d[Y];
			    hitp->hit_point[Z] = 0;
			    VMOVE(hitp->hit_vpriv, hit1);
			    if (ZERO(m)) {
				hitp->hit_vpriv[Z] = 0.0;
			    } else {
				hitp->hit_vpriv[Z] = -1.0/m;
			    }
			    hitp->hit_magic = RT_HIT_MAGIC;
			    hitp->hit_dist = k1;
			    hitp->hit_surfno = i;
			}
		    }
		    if (FMIN(pt1[X], pt2[X]) < -aa && -aa < FMAX(pt1[X], pt2[X])) {
			/* check negative side of the sketch (x < 0) */
			k1 = (m * (-aa - pt1[X]) + pt1[Y] - pr[Z]) / vr[Z];
			VJOIN1(hit1, pr, k1, vr);
			angle = atan2(hit1[Y], hit1[X]);
			hit2d[X] = aa;		/* use neg to check for overlap in contains() */
			hit2d[Y] = hit1[Z];
			if (angle < 0) {
			    angle += M_PI;
			}
			if (angle < rev->ang &&
			    !((angle + M_PI < rev->ang || angle - M_PI > 0)
			      && rt_sketch_contains(rev->skt, hit2d))) {
			    if (nhits >= MAX_HITS) return -1; /* too many hits */
			    hitp = hits[nhits++];
			    hitp->hit_point[X] = -hit2d[X];
			    hitp->hit_point[Y] = hit2d[Y];
			    hitp->hit_point[Z] = 0;
			    VMOVE(hitp->hit_vpriv, hit1);
			    if (ZERO(m)) {
				hitp->hit_vpriv[Z] = 0.0;
			    } else {
				hitp->hit_vpriv[Z] = 1.0/m;
			    }
			    hitp->hit_magic = RT_HIT_MAGIC;
			    hitp->hit_dist = k1;
			    hitp->hit_surfno = i;
			}
		    }
		} else if (NEAR_ZERO(ur[Z], RT_DOT_TOL)) {
		    /* ray is horizontal line at y = h; hit2d[X] > aa */
		    if (FMIN(pt1[Y], pt2[Y]) < h && h < FMAX(pt1[Y], pt2[Y])) {
			if (ZERO(m)) {
			    hit2d[X] = pt1[X];
			} else {
			    hit2d[X] = pt1[X] + (h-pt1[Y])/m;
			}
			hit2d[Y] = h;
			if (fabs(hit2d[X]) > aa) {
			    k1 = k + sqrt(hit2d[X]*hit2d[X] - aa*aa);
			    k2 = k - sqrt(hit2d[X]*hit2d[X] - aa*aa);

			    VJOIN1(hit1, pr, k1, vr);
			    angle = atan2(hit1[Y], hit1[X]);
			    if (hit2d[X] < 0) {
				angle += M_PI;
			    } else if (angle < 0) {
				angle += M_2PI;
			    }
			    hit2d[X] = -hit2d[X];
			    if (angle < rev->ang &&
				!((angle + M_PI < rev->ang || angle - M_PI > 0)
				  && rt_sketch_contains(rev->skt, hit2d))) {
				if (nhits >= MAX_HITS) return -1; /* too many hits */
				hitp = hits[nhits++];
				hitp->hit_point[X] = -hit2d[X];
				hitp->hit_point[Y] = hit2d[Y];
				hitp->hit_point[Z] = 0;
				VMOVE(hitp->hit_vpriv, hit1);
				if (ZERO(m)) {
				    hitp->hit_vpriv[Z] = 0.0;
				} else {
				    hitp->hit_vpriv[Z] = (hit2d[X]>0) ? 1.0/m : -1.0/m;
				}
				hitp->hit_magic = RT_HIT_MAGIC;
				hitp->hit_dist = k1;
				hitp->hit_surfno = i;
			    }

			    VJOIN1(hit2, pr, k2, vr);
			    angle = atan2(hit2[Y], hit2[X]);
			    if (-hit2d[X] < 0) {
				angle += M_PI;
			    } else if (angle < 0) {
				angle += M_2PI;
			    }
			    if (angle < rev->ang &&
				!((angle + M_PI < rev->ang || angle - M_PI > 0)
				  && rt_sketch_contains(rev->skt, hit2d))) {
				if (nhits >= MAX_HITS) return -1; /* too many hits */
				hitp = hits[nhits++];
				hitp->hit_point[X] = -hit2d[X];
				hitp->hit_point[Y] = hit2d[Y];
				hitp->hit_point[Z] = 0;
				VMOVE(hitp->hit_vpriv, hit2);
				if (ZERO(m)) {
				    hitp->hit_vpriv[Z] = 0.0;
				} else {
				    hitp->hit_vpriv[Z] = (hit2d[X]>0) ? 1.0/m : -1.0/m;
				}
				hitp->hit_magic = RT_HIT_MAGIC;
				hitp->hit_dist = k2;
				hitp->hit_surfno = i;
			    }
			}
		    }
		} else {

		    a = dir[X]*dir[X]/(aa*aa) - dir[Y]*dir[Y]/(bb*bb);
		    b = 2*(dir[X]*pt1[X]/(aa*aa) - dir[Y]*(pt1[Y]-h)/(bb*bb));
		    c = pt1[X]*pt1[X]/(aa*aa) - (pt1[Y]-h)*(pt1[Y]-h)/(bb*bb) - 1;
		    disc = b*b - (4.0 * a * c);
		    if (!NEAR_ZERO(a, RT_PCOEF_TOL)) {
			if (disc > 0) {
			    disc = sqrt(disc);
			    t1 =  (-b + disc) / (2.0 * a);
			    t2 =  (-b - disc) / (2.0 * a);
			    k1 = (pt1[Y]-pr[Z] + t1*dir[Y])/vr[Z];
			    k2 = (pt1[Y]-pr[Z] + t2*dir[Y])/vr[Z];

			    if (t1 > 0 && t1 < 1) {
				if (nhits >= MAX_HITS) return -1; /* too many hits */
				VJOIN1(hit1, pr, k1, vr);
				angle = atan2(hit1[Y], hit1[X]);
				V2JOIN1(hit2d, pt1, t1, dir);
				if (hit2d[X] < 0) {
				    angle += M_PI;
				} else if (angle < 0) {
				    angle += M_2PI;
				}
				hit2d[X] = -hit2d[X];
				if (angle < rev->ang) {
				    if ((angle + M_PI < rev->ang || angle - M_PI > 0)
					&& rt_sketch_contains(rev->skt, hit2d)) {
					/* overlap, so ignore it */
				    } else {
					hitp = hits[nhits++];
					hitp->hit_point[X] = -hit2d[X];
					hitp->hit_point[Y] = hit2d[Y];
					hitp->hit_point[Z] = 0;
					VMOVE(hitp->hit_vpriv, hit1);
					if (ZERO(m)) {
					    hitp->hit_vpriv[Z] = 0.0;
					} else {
					    hitp->hit_vpriv[Z] = (hit2d[X]>0) ? 1.0/m : -1.0/m;
					}
					hitp->hit_magic = RT_HIT_MAGIC;
					hitp->hit_dist = k1;
					hitp->hit_surfno = i;
				    }
				}
			    }
			    if (t2 > 0 && t2 < 1) {
				if (nhits >= MAX_HITS) return -1; /* too many hits */
				VJOIN1(hit2, pr, k2, vr);
				angle = atan2(hit2[Y], hit2[X]);
				V2JOIN1(hit2d, pt1, t2, dir);
				if (hit2d[X] < 0) {
				    angle += M_PI;
				} else if (angle < 0) {
				    angle += M_2PI;
				}
				hit2d[X] = -hit2d[X];
				if (angle < rev->ang) {
				    if ((angle + M_PI < rev->ang || angle - M_PI > 0)
					&& rt_sketch_contains(rev->skt, hit2d)) {
					/* overlap, so ignore it */
				    } else {
					hitp = hits[nhits++];
					hitp->hit_point[X] = -hit2d[X];
					hitp->hit_point[Y] = hit2d[Y];
					hitp->hit_point[Z] = 0;
					VMOVE(hitp->hit_vpriv, hit2);
					if (ZERO(m)) {
					    hitp->hit_vpriv[Z] = 0.0;
					} else {
					    hitp->hit_vpriv[Z] = (hit2d[X]>0) ? 1.0/m : -1.0/m;
					}
					hitp->hit_magic = RT_HIT_MAGIC;
					hitp->hit_dist = k2;
					hitp->hit_surfno = i;
				    }
				}
			    }
			}
		    } else if (!NEAR_ZERO(b, RT_PCOEF_TOL)) {
			t1 = -c / b;
			k1 = (pt1[Y]-pr[Z] + t1*dir[Y])/vr[Z];
			if (t1 > 0 && t1 < 1) {
			    if (nhits >= MAX_HITS) return -1; /* too many hits */

			    VJOIN1(hit1, pr, k1, vr);
			    angle = atan2(hit1[Y], hit1[X]);
			    V2JOIN1(hit2d, pt1, t1, dir);
			    if (hit2d[X] < 0) {
				angle += M_PI;
			    } else if (angle < 0) {
				angle += M_2PI;
			    }
			    hit2d[X] = -hit2d[X];
			    if (angle < rev->ang) {
				if ((angle + M_PI < rev->ang || angle - M_PI > 0)
				    && rt_sketch_contains(rev->skt, hit2d)) {
				    /* overlap, so ignore it */
				} else {
				    hitp = hits[nhits++];
				    hitp->hit_point[X] = -hit2d[X];
				    hitp->hit_point[Y] = hit2d[Y];
				    hitp->hit_point[Z] = 0;
				    VMOVE(hitp->hit_vpriv, hit1);
				    if (ZERO(m)) {
					hitp->hit_vpriv[Z] = 0.0;
				    } else {
					hitp->hit_vpriv[Z] = (hit2d[X]>0) ? 1.0/m : -1.0/m;
				    }
				    hitp->hit_magic = RT_HIT_MAGIC;
				    hitp->hit_dist = k1;
				    hitp->hit_surfno = i;
				}
			    }
			}
		    }
		}
		break;
	    case CURVE_CARC_MAGIC:
		/*
		  circle: (x-cx)^2 + (y-cy)^2 = cr^2
		  x = (1/2cx)y^2 + (-cy/cx)y + (1/2cx)(cy^2 + cx^2 - cr^2) + (1/2cx)(x^2)
		  x = f(y) + (1/2cx)x^2

		  hyperbola:
		  [(x-hx)/a]^2 - [(y-hy)/b]^2 = 1
		  x^2 = (a^2/b^2)y^2 + (-2*hy*a^2/b^2)y + (hy^2 * a^2/b^2) + a^2
		  x^2 = g(y)

		  plug the second equation into the first to get:
		  x = f(y) + (1/2cx)g(y)
		  then square that to get:
		  x^2 = {f(y) + (1/2cx)g(y)}^2 = g(y)
		  move all to one side to get:
		  0 = {f(y) + (1/2cx)g(y)}^2 - g(y)
		  this is a fourth order polynomial in y.
		*/
		{
		    bn_poly_t circleX;	/* f(y) */
		    bn_poly_t hypXsq;		/* g(y) */
		    bn_poly_t hypXsq_scaled;	/* g(y) / (2*cx) */
		    bn_poly_t sum;		/* f(y) + g(y)/(2cx) */
		    bn_poly_t sum_sq;		/* {f(y) + g(y)/(2cx)}^2 */
		    bn_poly_t answer;		/* {f(y) + g(y)/(2cx)}^2 - g(y) */
		    bn_complex_t roots[4];
		    int rootcnt;

		    fastf_t cx, cy, crsq = 0;	/* carc's (x, y) coords and radius^2 */
		    point2d_t center, radius;

		    /* calculate circle parameters */
		    csg = (struct carc_seg *)lng;

		    if (csg->radius <= 0.0) {
			/* full circle, "end" is center and "start" is on the circle */
			V2MOVE(center, rev->skt->verts[csg->end]);
			V2SUB2(radius, rev->skt->verts[csg->start], center);
			crsq = MAG2SQ(radius);
		    } else {
			point_t startpt, endpt, midpt;
			vect_t s_to_m;
			vect_t bisector;
			vect_t vertical;
			fastf_t distance;
			fastf_t magsq_s2m;

			VSET(vertical, 0, 0, 1);
			V2MOVE(startpt, rev->skt->verts[csg->start]);
			startpt[Z] = 0.0;
			V2MOVE(endpt, rev->skt->verts[csg->end]);
			endpt[Z] = 0.0;

			VBLEND2(midpt, 0.5, startpt, 0.5, endpt);
			VSUB2(s_to_m, midpt, startpt);
			VCROSS(bisector, vertical, s_to_m);
			VUNITIZE(bisector);
			magsq_s2m = MAGSQ(s_to_m);
			if (magsq_s2m > csg->radius*csg->radius) {
			    fastf_t max_radius;

			    max_radius = sqrt(magsq_s2m);
			    if (NEAR_EQUAL(max_radius, csg->radius, RT_LEN_TOL)) {
				csg->radius = max_radius;
			    } else {
				bu_log("Impossible radius for circular arc in extrusion (%s), is %g, cannot be more than %g!\n",
				       stp->st_dp->d_namep, csg->radius, sqrt(magsq_s2m));
				bu_log("Difference is %g\n", max_radius - csg->radius);
				return -1;
			    }
			}
			distance = sqrt(csg->radius*csg->radius - magsq_s2m);

			/* save arc center */
			if (csg->center_is_left) {
			    V2JOIN1(center, midpt, distance, bisector);
			} else {
			    V2JOIN1(center, midpt, -distance, bisector);
			}
		    }

		    cx = center[X];
		    cy = center[Y];

		    circleX.dgr = 2;
		    hypXsq.dgr = 2;
		    hypXsq_scaled.dgr = 2;
		    sum.dgr = 2;
		    sum_sq.dgr = 4;
		    answer.dgr = 4;

		    circleX.cf[0] = (cy*cy + cx*cx - crsq)/(2.0*cx);
		    circleX.cf[1] = -cy/cx;
		    circleX.cf[2] = 1/(2.0*cx);

		    hypXsq_scaled.cf[0] = hypXsq.cf[0] = aa*aa + h*h*aa*aa/(bb*bb);
		    hypXsq_scaled.cf[1] = hypXsq.cf[1] = -2.0*h*aa*aa/(bb*bb);
		    hypXsq_scaled.cf[2] = hypXsq.cf[2] = (aa*aa)/(bb*bb);

		    bn_poly_scale(&hypXsq_scaled, 1.0 / (2.0 * cx));
		    bn_poly_add(&sum, &hypXsq_scaled, &circleX);
		    bn_poly_mul(&sum_sq, &sum, &sum);
		    bn_poly_sub(&answer, &sum_sq, &hypXsq);

		    /* It is known that the equation is 4th order.  Therefore, if the
		     * root finder returns other than 4 roots, error.
		     */
		    rootcnt = rt_poly_roots(&answer, roots, stp->st_dp->d_namep);
		    if (rootcnt != 4) {
			if (rootcnt > 0) {
			    bu_log("tor:  rt_poly_roots() 4!=%d\n", rootcnt);
			    bn_pr_roots(stp->st_name, roots, rootcnt);
			} else if (rootcnt < 0) {
			    static int reported=0;
			    bu_log("The root solver failed to converge on a solution for %s\n", stp->st_dp->d_namep);
			    if (!reported) {
				VPRINT("while shooting from:\t", rp->r_pt);
				VPRINT("while shooting at:\t", rp->r_dir);
				bu_log("Additional torus convergence failure details will be suppressed.\n");
				reported=1;
			    }
			}
		    }

		    break;
		}
	    case CURVE_BEZIER_MAGIC:
		break;
	    case CURVE_NURB_MAGIC:
		break;
	    default:
		bu_log("rt_revolve_prep: ERROR: unrecognized segment type!\n");
		break;
	}

    }

    if (nhits%2 != 0) {
	bu_log("odd number of hits: %zu\n", nhits);
	for (i=0; i<nhits; i++) {
	    bu_log("\t(%6.2f, %6.2f)\t%6.2f\t%2d\n",
		   hits[i]->hit_point[X], hits[i]->hit_point[Y], hits[i]->hit_dist, hits[i]->hit_surfno);
	}
	return -1;
    }

    /* sort hitpoints (an arbitrary number of hits depending on sketch) */
    for (i=0; i<nhits; i+=2) {
	in = out = -1;
	for (j=0; j<nhits; j++) {
	    if (hits[j] == NULL) continue;
	    if (in == -1) {
		in = j;
		continue;
	    }
	    /* store shortest dist as 'in', second shortest as 'out' */
	    if (hits[j]->hit_dist <= hits[in]->hit_dist) {
		out = in;
		in = j;
	    } else if (out == -1 || hits[j]->hit_dist <= hits[out]->hit_dist) {
		out = j;
	    }
	}
	if (in == -1 || out == -1) {
	    bu_log("failed to find valid segment. nhits: %zu\n", nhits);
	    break;
	}

	if (ZERO(hits[in]->hit_dist - hits[out]->hit_dist)) {
	    hits[in] = NULL;
	    hits[out] = NULL;
	    continue;
	}

	RT_GET_SEG(segp, ap->a_resource);
	segp->seg_stp = stp;

	segp->seg_in = *hits[in];
	hits[in] = NULL;
	segp->seg_out = *hits[out];
	hits[out] = NULL;
	BU_LIST_INSERT(&(seghead->l), &(segp->l));
    }

    return nhits;
}