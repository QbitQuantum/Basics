void CKinematics::AddWallmark(const Fmatrix* parent_xform, const Fvector3& start, const Fvector3& dir, ref_shader shader, float size)
{
	Fvector S,D,normal		= {0,0,0};
	// transform ray from world to model
	Fmatrix P;	P.invert	(*parent_xform);
	P.transform_tiny		(S,start);
	P.transform_dir			(D,dir);
	// find pick point
	float dist				= flt_max;
	BOOL picked				= FALSE;

	DEFINE_VECTOR			(Fobb,OBBVec,OBBVecIt);
	OBBVec					cache_obb;
	cache_obb.resize		(LL_BoneCount());

	for (u16 k=0; k<LL_BoneCount(); k++){
		CBoneData& BD		= LL_GetData(k);
		if (LL_GetBoneVisible(k)&&!BD.shape.flags.is(SBoneShape::sfNoPickable)){
			Fobb& obb		= cache_obb[k];
			obb.transform	(BD.obb,LL_GetBoneInstance(k).mTransform);
			if (CDB::TestRayOBB(S,D, obb))
				for (u32 i=0; i<children.size(); i++)
					if (LL_GetChild(i)->PickBone(normal,dist,S,D,k)) picked=TRUE;
		}
	}
	if (!picked) return; 
 
	// calculate contact point
	Fvector cp;	cp.mad		(S,D,dist); 
 
	// collect collide boxes
	Fsphere test_sphere;
    test_sphere.set			(cp,size); 
	U16Vec					test_bones;
	test_bones.reserve		(LL_BoneCount());
	for (k=0; k<LL_BoneCount(); k++){
		CBoneData& BD		= LL_GetData(k);  
		if (LL_GetBoneVisible(k)&&!BD.shape.flags.is(SBoneShape::sfNoPickable)){
			Fobb& obb		= cache_obb[k];
			if (CDB::TestSphereOBB(test_sphere, obb))
				test_bones.push_back(k);
		}
	}

	// find similar wm
	for (u32 wm_idx=0; wm_idx<wallmarks.size(); wm_idx++){
		intrusive_ptr<CSkeletonWallmark>& wm = wallmarks[wm_idx];		
		if (wm->Similar(shader,cp,0.02f)){ 
			if (wm_idx<wallmarks.size()-1) 
				wm = wallmarks.back();
			wallmarks.pop_back();
			break;
		}
	}

	// ok. allocate wallmark
	intrusive_ptr<CSkeletonWallmark>		wm = xr_new<CSkeletonWallmark>(this,parent_xform,shader,cp,Device.fTimeGlobal);
	wm->m_LocalBounds.set		(cp,size*2.f);
	wm->XFORM()->transform_tiny	(wm->m_Bounds.P,cp);
	wm->m_Bounds.R				= wm->m_Bounds.R; 

	Fvector tmp; tmp.invert		(D);
	normal.add(tmp).normalize	();

	// build UV projection matrix
	Fmatrix						mView,mRot;
	BuildMatrix					(mView,1/(0.9f*size),normal,cp);
	mRot.rotateZ				(::Random.randF(deg2rad(-20.f),deg2rad(20.f)));
	mView.mulA_43				(mRot);

	// fill vertices
	for (u32 i=0; i<children.size(); i++){
		CSkeletonX* S		= LL_GetChild(i);
		for (U16It b_it=test_bones.begin(); b_it!=test_bones.end(); b_it++)
			S->FillVertices		(mView,*wm,normal,size,*b_it);
	}

	wallmarks.push_back		(wm);
}