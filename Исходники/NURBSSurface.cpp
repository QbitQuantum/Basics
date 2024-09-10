double NURBSSurface::Getv(double u, CVector r)
{
	double sine = 10000.0;

	if(u<=0.0)          return 0.0;
	if(u>=1.0)          return 0.0;
	if(r.VAbs()<1.0e-5) return 0.0;

	int iter=0;
	double v, v1, v2;

	r.Normalize();
	v1 = 0.0; v2 = 1.0;

	while(qAbs(sine)>1.0e-4 && iter<200)
	{
		v=(v1+v2)/2.0;
		GetPoint(u, v, t_R);
		t_R.x = 0.0;
		t_R.Normalize();//t_R is the unit radial vector for u,v

		sine = (r.y*t_R.z - r.z*t_R.y);

		if(sine>0.0) v1 = v;
		else         v2 = v;
		iter++;
	}

	return (v1+v2)/2.0;
}