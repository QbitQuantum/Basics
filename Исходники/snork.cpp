bool CSnork::trace_geometry(const Fvector &d, float &range)
{
	Fvector				dir;
	float				h, p;

	Fvector				Pl,Pc,Pr;
	Fvector				center;
	Center				(center);

	range				= trace (d);
	if (range > TRACE_RANGE) return false;
	
	float angle			= asin(1.f / range);

	// trace center ray
	dir					= d;

	dir.getHP			(h,p);
	p					+= angle;
	dir.setHP			(h,p);
	dir.normalize_safe	();

	range				= trace (dir);
	if (range > TRACE_RANGE) return false;

	Pc.mad				(center, dir, range);

	// trace left ray
	Fvector				temp_p;
	temp_p.mad			(Pc, XFORM().i, Radius() / 2);
	dir.sub				(temp_p, center);
	dir.normalize_safe	();

	range				= trace (dir);
	if (range > TRACE_RANGE) return false;

	Pl.mad				(center, dir, range);

	// trace right ray
	Fvector inv			= XFORM().i; 
	inv.invert			();
	temp_p.mad			(Pc, inv, Radius() / 2);
	dir.sub				(temp_p, center);
	dir.normalize_safe	();

	range				= trace (dir);
	if (range > TRACE_RANGE) return false;

	Pr.mad				(center, dir, range);

	float				h1,p1,h2,p2;

	Fvector().sub(Pl, Pc).getHP(h1,p1);
	Fvector().sub(Pc, Pr).getHP(h2,p2);

	return (fsimilar(h1,h2,0.1f) && fsimilar(p1,p2,0.1f));
}