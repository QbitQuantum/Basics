void CPEDef::ExecuteCollision(PAPI::Particle* particles, u32 p_cnt, float dt, CParticleEffect* owner, CollisionCallback cb)
{
	pVector pt,n;
	// Must traverse list in reverse order so Remove will work
	for(int i = p_cnt-1; i >= 0; i--){
		Particle &m = particles[i];

		bool pick_needed;
		int pick_cnt=0;
		do{		
			pick_needed = false;
			Fvector 	dir;
			dir.sub		(m.pos,m.posB);
			float dist 	= dir.magnitude();
			if (dist>=EPS){
				dir.div	(dist);
#ifdef _EDITOR                
				if (Tools->RayPick(m.posB,dir,dist,&pt,&n)){
#else
				collide::rq_result	RQ;
                collide::rq_target	RT = m_Flags.is(dfCollisionDyn)?collide::rqtBoth:collide::rqtStatic;
				if (g_pGameLevel->ObjectSpace.RayPick(m.posB,dir,dist,RT,RQ,NULL)){	
					pt.mad	(m.posB,dir,RQ.range);
					if (RQ.O){
						n.set(0.f,1.f,0.f);
					}else{
						CDB::TRI*	T		=  	g_pGameLevel->ObjectSpace.GetStaticTris()+RQ.element;
						Fvector*	verts	=	g_pGameLevel->ObjectSpace.GetStaticVerts();
						n.mknormal(verts[T->verts[0]],verts[T->verts[1]],verts[T->verts[2]]);
					}
#endif
					pick_cnt++;
					if (cb&&(pick_cnt==1)) if (!cb(owner,m,pt,n)) break;
					if (m_Flags.is(dfCollisionDel)){ 
	                   	ParticleManager()->RemoveParticle(owner->m_HandleEffect,i);
					}else{
						// Compute tangential and normal components of velocity
						float nmag = m.vel * n;
						pVector vn(n * nmag); 	// Normal Vn = (V.N)N
						pVector vt(m.vel - vn);	// Tangent Vt = V - Vn

						// Compute _new velocity heading out:
						// Don't apply friction if tangential velocity < cutoff
						if(vt.length2() <= m_fCollideSqrCutoff){
							m.vel = vt - vn * m_fCollideResilience;
						}else{
							m.vel = vt * m_fCollideOneMinusFriction - vn * m_fCollideResilience;
						}
						m.pos	= m.posB + m.vel * dt; 
						pick_needed = true;
					}
				}
			}else{
				m.pos	= m.posB;
			}
		}while(pick_needed&&(pick_cnt<2));
	}
}

//------------------------------------------------------------------------------
// I/O part
//------------------------------------------------------------------------------
BOOL CPEDef::Load(IReader& F)
{
	R_ASSERT		(F.find_chunk(PED_CHUNK_VERSION));
	u16 version		= F.r_u16();

	if (version!=PED_VERSION)
		return FALSE;

	R_ASSERT		(F.find_chunk(PED_CHUNK_NAME));
	F.r_stringZ		(m_Name);

	R_ASSERT		(F.find_chunk(PED_CHUNK_EFFECTDATA));
	m_MaxParticles	= F.r_u32();

	{
		u32 action_list	= F.find_chunk(PED_CHUNK_ACTIONLIST); 
		R_ASSERT(action_list);
		m_Actions.w		(F.pointer(),action_list);
	}

	F.r_chunk		(PED_CHUNK_FLAGS,&m_Flags);

	if (m_Flags.is(dfSprite))
	{
		R_ASSERT	(F.find_chunk(PED_CHUNK_SPRITE));
		F.r_stringZ	(m_ShaderName);
		F.r_stringZ	(m_TextureName);
	}

	if (m_Flags.is(dfFramed))
	{
		R_ASSERT	(F.find_chunk(PED_CHUNK_FRAME));
		F.r			(&m_Frame,sizeof(SFrame));
	}

	if (m_Flags.is(dfTimeLimit))
	{
		R_ASSERT(F.find_chunk(PED_CHUNK_TIMELIMIT));
		m_fTimeLimit= F.r_float();
	}

	if (m_Flags.is(dfCollision))
	{
		R_ASSERT(F.find_chunk(PED_CHUNK_COLLISION));
		m_fCollideOneMinusFriction 	= F.r_float();
		m_fCollideResilience		= F.r_float();
		m_fCollideSqrCutoff			= F.r_float();
	}

	if (m_Flags.is(dfVelocityScale))
	{
		R_ASSERT(F.find_chunk(PED_CHUNK_VEL_SCALE));
		F.r_fvector3				(m_VelocityScale); 
	}

	if (m_Flags.is(dfAlignToPath))
	{
		if (F.find_chunk(PED_CHUNK_ALIGN_TO_PATH)){
			F.r_fvector3			(m_APDefaultRotation);
		}
	}

#ifdef _EDITOR
    if (pCreateEAction&&F.find_chunk(PED_CHUNK_EDATA))
	{
        m_EActionList.resize(F.r_u32());
        for (EPAVecIt it=m_EActionList.begin(); it!=m_EActionList.end(); ++it)
		{
            PAPI::PActionEnum type		= (PAPI::PActionEnum)F.r_u32();
            (*it)						= pCreateEAction(type);
            (*it)->Load					(F);
        }
		Compile							(m_EActionList);
    } 
#endif

	return TRUE;
}