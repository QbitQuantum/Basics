BOOL ESceneAIMapTool::CreateNode(Fvector& vAt, SAINode& N, bool bIC)
{
	// *** Query and cache polygons for ray-casting
	Fvector	PointUp;		PointUp.set(vAt);	PointUp.y	+= RCAST_Depth;		SnapXZ	(PointUp,m_Params.fPatchSize);
	Fvector	PointDown;		PointDown.set(vAt);	PointDown.y	-= RCAST_Depth;		SnapXZ	(PointDown,m_Params.fPatchSize);

	Fbox	BB;				BB.set	(PointUp,PointUp);		BB.grow(m_Params.fPatchSize/2);	// box 1
	Fbox	B2;				B2.set	(PointDown,PointDown);	B2.grow(m_Params.fPatchSize/2);	// box 2
	BB.merge				(B2);

    if (m_CFModel)
    {
    	/*
        for(u32 i=0; i<m_CFModel->get_tris_count(); ++i)
        {
            CDB::TRI* tri = (m_CFModel->get_tris()+i);
            if(tri->material!=0)
            	Msg("non-default material");
        }
        */
    	Scene->BoxQuery(PQ,BB,CDB::OPT_FULL_TEST,m_CFModel);
    }else
    	Scene->BoxQuery(PQ,BB,CDB::OPT_FULL_TEST,GetSnapList());

	DWORD	dwCount 		= PQ.r_count();
	if (dwCount==0){
//		Log("chasm1");
		return FALSE;			// chasm?
	}

	// *** Transfer triangles and compute sector
//	R_ASSERT(dwCount<RCAST_MaxTris);
	static xr_vector<tri> tris;	tris.reserve(RCAST_MaxTris);	tris.clear();
	for (DWORD i=0; i<dwCount; i++)
	{
    	SPickQuery::SResult* R = PQ.r_begin()+i;

        if (R->e_obj&&R->e_mesh)
        {
            CSurface* surf		= R->e_mesh->GetSurfaceByFaceID(R->tag);
//.			SGameMtl* mtl 		= GMLib.GetMaterialByID(surf->_GameMtl());
//.			if (mtl->Flags.is(SGameMtl::flPassable))continue;


            Shader_xrLC* c_sh	= Device.ShaderXRLC.Get(surf->_ShaderXRLCName());
            if (!c_sh->flags.bCollision) 			continue;
        }
  /*
		if(m_CFModel)
        {
            u16 mtl_id 	= R->material;

            if(std::find(m_ignored_materials.begin(), m_ignored_materials.end(), mtl_id) != m_ignored_materials.end() )
            {
//.                Msg("--ignore");
                continue;
            }
        }
*/
    	tris.push_back	(tri());
		tri&		D = tris.back();
		Fvector*	V = R->verts;   

		D.v[0]		= &V[0];
		D.v[1]		= &V[1];
		D.v[2]		= &V[2];
		D.N.mknormal(*D.v[0],*D.v[1],*D.v[2]);
		if (D.N.y<=0)	tris.pop_back	();
	}
	if (tris.size()==0){
//		Log("chasm2");
		return FALSE;			// chasm?
	}

	static xr_vector<Fvector>	points;		points.reserve(RCAST_Total); points.clear();
	static xr_vector<Fvector>	normals;	normals.reserve(RCAST_Total);normals.clear();
	Fvector P,D; D.set(0,-1,0);

	float coeff 	= 0.5f*m_Params.fPatchSize/float(RCAST_Count);

	for (int x=-RCAST_Count; x<=RCAST_Count; x++) 
	{
		P.x = vAt.x + coeff*float(x); 
		for (int z=-RCAST_Count; z<=RCAST_Count; z++) {
			P.z = vAt.z + coeff*float(z);
			P.y = vAt.y + 10.f;

			float	tri_min_range	= flt_max;
			int		tri_selected	= -1;
			float	range,u,v;
			for (i=0; i<DWORD(tris.size()); i++){
				if (ETOOLS::TestRayTriA(P,D,tris[i].v,u,v,range,false)){
					if (range<tri_min_range){
						tri_min_range	= range;
						tri_selected	= i;
					}
				}
			}
			if (tri_selected>=0) {
				P.y -= tri_min_range;
				points.push_back(P);
				normals.push_back(tris[tri_selected].N);
			}
		}
	}
	if (points.size()<3) {
//		Msg		("Failed to create node at [%f,%f,%f].",vAt.x,vAt.y,vAt.z);
		return	FALSE;
	}
//.
	float rc_lim = bIC?0.015f:0.7f;
	if (float(points.size())/float(RCAST_Total) < rc_lim) {
//		Msg		("Partial chasm at [%f,%f,%f].",vAt.x,vAt.y,vAt.z);
		return	FALSE;
	}

	// *** Calc normal
	Fvector vNorm;
	vNorm.set(0,0,0);
	for (DWORD n=0; n<normals.size(); n++)
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
	for (DWORD p=0; p<points.size(); p++)
	{
		float dist = PL.classify(points[p]);
		if (dist>0) {
			vOffs = points[p];
			PL.build(vOffs,vNorm);
		}
	}

	// *** Create node and register it
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
		if (y_old-y_new > m_Params.fCanDOWN ) return FALSE;
	} else {
		// up
		if (y_new-y_old > m_Params.fCanUP	) return FALSE;
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
				for (i=0; i<tris.size(); i++){
					if (ETOOLS::TestRayTriA(P,D,tris[i].v,u,v,range,false)){
						if (range<tri_min_range){
							tri_min_range	= range;
							tri_selected	= i;
						}
					}
				}
				if (tri_selected>=0){
					if (tri_min_range<RCAST_VALID) num_successed_rays++;
				}
			}
		}
		float perc = float(num_successed_rays)/float(RCAST_Total);
//.		if (!bIC&&(perc < 0.5f)){
		float perc_lim = bIC?0.015f:0.5f;
		if (perc < perc_lim){
			//			Msg		("Floating node.");
			return	FALSE;
		}
	}

	// *** Mask check
	// ???

	return TRUE;
}