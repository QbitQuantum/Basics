	virtual void		Execute()
	{
		CDB::COLLIDER		DB;
		DB.ray_options		(CDB::OPT_CULL);
		
		xr_vector<RC>		cache;
		{
			RC				rc;	
			rc.C[0].set		(0,0,0); 
			rc.C[1].set		(0,0,0); 
			rc.C[2].set		(0,0,0);
			
			cache.assign	(g_nodes.size()*2,rc);
		}

		FPU::m24r		();
		Query			Q;
		Q.Begin			(g_nodes.size());
		for (u32 N=Nstart; N<Nend; N++)
		{
			// initialize process
			thProgress	= float(N-Nstart)/float(Nend-Nstart);
			vertex&		BaseNode= g_nodes[N];
			Fvector&	BasePos	= BaseNode.Pos;
			Fvector		TestPos = BasePos; TestPos.y+=cover_height;
			
			float	c_total	[8]	= {0,0,0,0,0,0,0,0};
			float	c_passed[8]	= {0,0,0,0,0,0,0,0};
			
			// perform volumetric query
			Q.Init			(BasePos);
			Q.Perform		(N);
			
			// main cycle: trace rays and compute counts
			for (Nearest_it it=Q.q_List.begin(); it!=Q.q_List.end();  it++)
			{
				// calc dir & range
				u32		ID	= *it;
				R_ASSERT	(ID<g_nodes.size());
				if			(N==ID)		continue;
				vertex&		N			= g_nodes[ID];
				Fvector&	Pos			= N.Pos;
				Fvector		Dir;
				Dir.sub		(Pos,BasePos);
				float		range		= Dir.magnitude();
				Dir.div		(range);
				
				// raytrace
				int			sector		=	calcSphereSector(Dir);
				c_total		[sector]	+=	1.f;
				c_passed	[sector]	+=	rayTrace (&DB, TestPos, Dir, range, cache[ID].C); //
			}
			Q.Clear			();
			
			// analyze probabilities
			float	value	[8];
			for (int dirs=0; dirs<8; dirs++)	{
				R_ASSERT(c_passed[dirs]<=c_total[dirs]);
				if (c_total[dirs]==0)	value[dirs] = 0;
				else					value[dirs]	= float(c_passed[dirs])/float(c_total[dirs]);
				clamp(value[dirs],0.f,1.f);
			}
			
			BaseNode.cover	[0]	= (value[2]+value[3]+value[4]+value[5])/4.f; clamp(BaseNode.cover[0],0.f,1.f);	// left
			BaseNode.cover	[1]	= (value[0]+value[1]+value[2]+value[3])/4.f; clamp(BaseNode.cover[1],0.f,1.f);	// forward
			BaseNode.cover	[2]	= (value[6]+value[7]+value[0]+value[1])/4.f; clamp(BaseNode.cover[2],0.f,1.f);	// right
			BaseNode.cover	[3]	= (value[4]+value[5]+value[6]+value[7])/4.f; clamp(BaseNode.cover[3],0.f,1.f);	// back
		}
	}