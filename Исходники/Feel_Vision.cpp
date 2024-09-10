	void Vision::o_trace	(Fvector& P, float dt, float vis_threshold)	{
		RQR.r_clear			();
		xr_vector<feel_visible_Item>::iterator I=feel_visible.begin(),E=feel_visible.end();
		for (; I!=E; I++){
			if (0==I->O->CFORM())	{ I->fuzzy = -1; continue; }

			// verify relation
			if (positive(I->fuzzy) && I->O->Position().similar(I->cp_LR_dst,lr_granularity) && P.similar(I->cp_LR_src,lr_granularity))
				continue;

			I->cp_LR_dst		= I->O->Position();
			I->cp_LR_src		= P;

			// Fetch data
			Fvector				OP;
			Fmatrix				mE;
			const Fbox&			B = I->O->CFORM()->getBBox();
			const Fmatrix&		M = I->O->XFORM();

			// Build OBB + Ellipse and X-form point
			Fvector				c,r;
			Fmatrix				T,mR,mS;
			B.getcenter			(c);
			B.getradius			(r);
			T.translate			(c);
			mR.mul_43			(M,T);
			mS.scale			(r);
			mE.mul_43			(mR,mS); 
			mE.transform_tiny	(OP,I->cp_LP);
			I->cp_LAST			= OP;

			// 
			Fvector				D;	
			D.sub				(OP,P);
			float				f = D.magnitude();
			if (f>fuzzy_guaranteed){
				D.div						(f);
				// setup ray defs & feel params
				collide::ray_defs RD		(P,D,f,CDB::OPT_CULL,collide::rq_target(collide::rqtStatic|collide::rqtObstacle));
				SFeelParam	feel_params		(this,&*I,vis_threshold);
				// check cache
				if (I->Cache.result&&I->Cache.similar(P,D,f)){
					// similar with previous query
					feel_params.vis			= I->Cache_vis;
//					Log("cache 0");
				}else{
					float _u,_v,_range;
					if (CDB::TestRayTri(P,D,I->Cache.verts,_u,_v,_range,false)&&(_range>0 && _range<f))	{
						feel_params.vis		= 0.f;
//						Log("cache 1");
					}else{
						// cache outdated. real query.
						VERIFY(!fis_zero(RD.dir.square_magnitude()));
						if (g_pGameLevel->ObjectSpace.RayQuery	(RQR, RD, feel_vision_callback, &feel_params, NULL, NULL))	{
							I->Cache_vis	= feel_params.vis	;
							I->Cache.set	(P,D,f,TRUE	)		;
						}else{
							I->Cache.set	(P,D,f,FALSE)		;
						}
//						Log("query");
					}
				}
//				Log("Vis",feel_params.vis);
				if (feel_params.vis<feel_params.vis_threshold){
					// INVISIBLE, choose next point
					I->fuzzy				-=	fuzzy_update_novis*dt;
					clamp					(I->fuzzy,-.5f,1.f);
					I->cp_LP.random_dir		();
					I->cp_LP.mul			(.7f);
				}else{
					// VISIBLE
					I->fuzzy				+=	fuzzy_update_vis*dt;
					clamp					(I->fuzzy,-.5f,1.f);
				}
			}
			else {
				// VISIBLE, 'cause near
				I->fuzzy				+=	fuzzy_update_vis*dt;
				clamp					(I->fuzzy,-.5f,1.f);
			}
		}
	}