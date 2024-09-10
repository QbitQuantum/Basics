void CPHShell::Activate(const Fmatrix &m0,float dt01,const Fmatrix &m2,bool disable){

	if(isActive())return;
	activate(disable);
//	ELEMENT_I i;
	mXFORM.set(m0);
	//for(i=elements.begin();elements.end() != i;++i){

	//	(*i)->Activate(m0,dt01, m2, disable);
	//}
	
	{		
		ELEMENT_I i=elements.begin(),e=elements.end();
		for(;i!=e;++i)(*i)->Activate(mXFORM,disable);
	}

	{
		JOINT_I i=joints.begin(),e=joints.end();
		for(;i!=e;++i) (*i)->Activate();
	}	
	
	Fmatrix m;
	{
		Fmatrix old_m = mXFORM;//+GetGlobalTransformDynamic update mXFORM;
		GetGlobalTransformDynamic	(&m);
		mXFORM = old_m;
	}
	m.invert();m.mulA_43		(mXFORM);
	TransformPosition(m);
	if(PKinematics())
	{
		SetCallbacks( );
	}

	//bActive=true;
	//bActivating=true;
	m_flags.set(flActive,TRUE);
	m_flags.set(flActivating,TRUE);
	spatial_register();
///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
	//mXFORM.set(m0);
	//Activate(disable);
	Fvector lin_vel;
	lin_vel.sub(m2.c,m0.c);
	set_LinearVel(lin_vel);
}