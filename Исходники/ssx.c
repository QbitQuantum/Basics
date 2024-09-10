static void
adj_ang_mom(SSDATA *d,int n,PROPERTIES *p,VECTOR v)
{
	VECTOR u,w;
	int i;

	invert(p->inertia);
	SUB_VEC(v,p->ang_mom,v);
	Transform(p->inertia,v,u);
	SCALE_VEC(u,p->total_mass);
	for (i=0;i<n;i++) {
		CROSS(u,d[i].pos,w);
		ADD_VEC(d[i].vel,w,d[i].vel);
		}
	}