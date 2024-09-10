BOOL	CreateNode(Fvector& vAt, vertex& N)
{
	// *** Query and cache polygons for ray-casting
	Fvector	PointUp;		PointUp.set(vAt);	PointUp.y	+= RCAST_Depth;		SnapXZ	(PointUp);
	Fvector	PointDown;		PointDown.set(vAt);	PointDown.y	-= RCAST_Depth;		SnapXZ	(PointDown);

	Fbox	BB;				BB.set	(PointUp,PointUp);		BB.grow(g_params.fPatchSize/2);	// box 1
	Fbox	B2;				B2.set	(PointDown,PointDown);	B2.grow(g_params.fPatchSize/2);	// box 2
	BB.merge(B2			);
	BoxQuery(BB,false	);
	u32	dwCount = XRC.r_count();
	if (dwCount==0)	{
//		Log("chasm1");
		return FALSE;			// chasm?
	}

	// *** Transfer triangles and compute sector
	R_ASSERT(dwCount<RCAST_MaxTris);
	static svector<tri,RCAST_MaxTris> tris;		tris.clear();
	for (u32 i=0; i<dwCount; i++)
	{
		tri&		D = tris.last();
		CDB::RESULT	&rp = XRC.r_begin()[i];
		CDB::TRI&	T = *(Level.get_tris()+rp.id);

		D.v[0].set	(rp.verts[0]);
		D.v[1].set	(rp.verts[1]);
		D.v[2].set	(rp.verts[2]);
		D.sector	= T.sector;
		D.N.mknormal(D.v[0],D.v[1],D.v[2]);
		if (D.N.y<=0)	continue;

		tris.inc	();
	}
	if (tris.size()==0)	{
//		Log("chasm2");
		return FALSE;			// chasm?
	}

	// *** Perform ray-casts and calculate sector
	WORD Sector = 0xfffe;	// mark as first time

	static svector<Fvector,RCAST_Total>	points;		points.clear();
	static svector<Fvector,RCAST_Total>	normals;	normals.clear();
	Fvector P,D; D.set(0,-1,0);

	float coeff = 0.5f*g_params.fPatchSize/float(RCAST_Count);

	for (int x=-RCAST_Count; x<=RCAST_Count; x++) 
	{
		P.x = vAt.x + coeff*float(x);
		for (int z=-RCAST_Count; z<=RCAST_Count; z++) {
			P.z = vAt.z + coeff*float(z);
			P.y = vAt.y + 10.f;

			float	tri_min_range	= flt_max;
			int		tri_selected	= -1;
			float	range,u,v;
			for (i=0; i<u32(tris.size()); i++) 
			{
				if (CDB::TestRayTri(P,D,tris[i].v,u,v,range,false)) 
				{
					if (range<tri_min_range) {
						tri_min_range	= range;
						tri_selected	= i;
					}
				}
			}
			if (tri_selected>=0) {
				P.y -= tri_min_range;
				points.push_back(P);
				normals.push_back(tris[tri_selected].N);
				WORD TS = WORD(tris[tri_selected].sector);
				if (Sector==0xfffe)	Sector = TS;
				else 				if (Sector!=TS) Sector=InvalidSector;
			}
		}
	}
	if (points.size()<3) {
//		Msg		("Failed to create node at [%f,%f,%f].",vAt.x,vAt.y,vAt.z);
		return	FALSE;
	}
	if (float(points.size())/float(RCAST_Total) < 0.7f) {
//		Msg		("Partial chasm at [%f,%f,%f].",vAt.x,vAt.y,vAt.z);
		return	FALSE;
	}

	// *** Calc normal
	Fvector vNorm;
	vNorm.set(0,0,0);
	for (u32 n=0; n<normals.size(); n++)
		vNorm.add(normals[n]);
	vNorm.div(float(normals.size()));
	vNorm.normalize();
	/*
	{
		// second algorithm (Magic)
		Fvector N,O;
		N.set(vNorm);
		O.set(points[0]);
		Mgc::OrthogonalPlaneFit(
			points.size(),(Mgc::Vector3*)points.begin(),
			*((Mgc::Vector3*)&O),
			*((Mgc::Vector3*)&N)
		);
		if (N.y<0) N.invert();
		N.normalize();
		vNorm.lerp(vNorm,N,.3f);
		vNorm.normalize();
	}
	*/

 
	// *** Align plane
	Fvector vOffs;
	vOffs.set(0,-1000,0);
	Fplane PL; 	PL.build(vOffs,vNorm);
	for (u32 p=0; p<points.size(); p++)
	{
		float dist = PL.classify(points[p]);
		if (dist>0) {
			vOffs = points[p];
			PL.build(vOffs,vNorm);
		}
	}

	// *** Create node and register it
	N.Sector		=Sector;						// sector
	N.Plane.build	(vOffs,vNorm);					// build plane
	D.set			(0,1,0);
	N.Plane.intersectRayPoint(PointDown,D,N.Pos);	// "project" position

	// *** Validate results
	vNorm.set(0,1,0);
	if (vNorm.dotproduct(N.Plane.n)<_cos(deg2rad(60.f)))  return FALSE;

	float y_old = vAt.y;
	float y_new = N.Pos.y;
	if (y_old>y_new) {
		// down
		if (y_old-y_new > g_params.fCanDOWN ) return FALSE;
	} else {
		// up
		if (y_new-y_old > g_params.fCanUP	) return FALSE;
	}
 
	// *** Validate plane
	{
		Fvector PLP; D.set(0,-1,0);
		int num_successed_rays = 0;
		for (int x=-RCAST_Count; x<=RCAST_Count; x++) 
		{
			P.x = N.Pos.x + coeff*float(x);
			for (int z=-RCAST_Count; z<=RCAST_Count; z++) {
				P.z = N.Pos.z + coeff*float(z);
				P.y = N.Pos.y;
				N.Plane.intersectRayPoint(P,D,PLP);	// "project" position
				P.y = PLP.y+RCAST_VALID*0.01f;
				
				float	tri_min_range	= flt_max;
				int		tri_selected	= -1;
				float	range,u,v;
				for (i=0; i<float(tris.size()); i++) 
				{
					if (CDB::TestRayTri(P,D,tris[i].v,u,v,range,false)) 
					{
						if (range<tri_min_range) {
							tri_min_range	= range;
							tri_selected	= i;
						}
					}
				}
				if (tri_selected>=0) {
					if (tri_min_range<RCAST_VALID) num_successed_rays++;
				}
			}
		}
		float perc = float(num_successed_rays)/float(RCAST_Total);
		if (perc < 0.5f) {
			//			Msg		("Floating node.");
			return	FALSE;
		}
	}

	// *** Mask check
	// ???

	return TRUE;
}