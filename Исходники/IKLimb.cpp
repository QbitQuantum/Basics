void CIKLimb::GoalMatrix(Matrix &M,SCalculateData* cd)
{
		VERIFY(cd->m_tri&&cd->m_tri_hight!=-dInfinity);
		const Fmatrix &obj=*cd->m_obj;
		CDB::TRI	*tri=cd->m_tri;
		CKinematics *K=cd->m_K;
		Fvector*	pVerts	= Level().ObjectSpace.GetStaticVerts();
		Fvector normal;
		normal.mknormal	(pVerts[tri->verts[0]],pVerts[tri->verts[1]],pVerts[tri->verts[2]]);
		VERIFY(!fis_zero(normal.magnitude()));

		Fmatrix iobj;iobj.invert(obj);iobj.transform_dir(normal);

		Fmatrix xm;xm.set(K->LL_GetTransform(m_bones[2]));

		//Fvector dbg;
		//dbg.set(Fvector().mul(normal,normal.y*tri_hight
		//	-normal.dotproduct(xm.i)*m_toe_position.x
		//	-normal.dotproduct(xm.j)*m_toe_position.y
		//	-normal.dotproduct(xm.k)*m_toe_position.z-m_toe_position.x
		//	));
		
		normal.invert();
		Fvector ax;ax.crossproduct(normal,xm.i);
		float s=ax.magnitude();
		if(!fis_zero(s))
		{
			ax.mul(1.f/s);

			xm.mulA_43(Fmatrix().rotation(ax,asinf(-s)));
		}

		Fvector otri;iobj.transform_tiny(otri,pVerts[tri->verts[0]]);
		float tp=normal.dotproduct(otri);
		Fvector add;
		add.set(Fvector().mul(normal,-m_toe_position.x+tp-xm.c.dotproduct(normal)));

		xm.c.add(add);
		
	
		Fmatrix H;
		CBoneData& bd=K->LL_GetData(m_bones[0]);
		H.set(bd.bind_transform);
	
		H.mulA_43(K->LL_GetTransform(bd.GetParentID()));
		H.c.set(K->LL_GetTransform(m_bones[0]).c);

	
#ifdef DEBUG
		if(ph_dbg_draw_mask.test(phDbgIKAnimGoalOnly))	xm.set(K->LL_GetTransform(m_bones[2]));
		if(ph_dbg_draw_mask.test(phDbgDrawIKGoal))
		{
			Fmatrix DBGG;
			DBGG.mul_43(obj,xm);
			DBG_DrawMatrix(DBGG,0.2f);

			
			DBGG.mul_43(obj,H);
			DBG_DrawMatrix(DBGG,0.2f);
		}
#endif
		H.invert();
		Fmatrix G; 
		G.mul_43(H,xm);
		XM2IM(G,M);
}