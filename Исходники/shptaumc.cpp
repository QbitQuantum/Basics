double TauMCMissile::get_aim(SpaceObject *tgt)
{
	STACKTRACE;
	Vector2 tv = tgt->get_vel();
	//double tvy = tgt->get_vy();
	//double rx  = min_delta(tgt->normal_x(), normal_x(), X_MAX);
	//double ry  = min_delta(tgt->normal_y(), normal_y(), Y_MAX);
	Vector2 r = min_delta(tgt->normal_pos(), normal_pos());
								 //rx*rx + ry*ry;
	double r2  = magnitude_sqr(r);
	double u2  = v * v;
								 //(tvx*tvx + tvy*tvy);
	double d2v = u2 - magnitude_sqr(tv);
	double t = r.dot(tv);		 //(rx*tvx + ry*tvy);
	double q, p;
	if (fabs(d2v/u2) > 0.01 ) {
		q = t*t + r2*d2v;
		if (q > 0) q = sqrt(q);
		else    return (1e10);
		p = (t+q)/d2v;
		q = (t-q)/d2v;
		if (p > 0) t = p;
		else       t = q;
		if (t < 0) return (1e10);
	} else {
		if (fabs(t)<1e-6) return (1e10);
		else    t = - 0.5 * r2 / t;
		if (t < 0) return (1e10);
	}
	t = normalize(atan3(tv.y*t + r.y, tv.x*t + r.x) - angle, PI2);
	if (t > PI) t -= PI2;
	return (t);
}