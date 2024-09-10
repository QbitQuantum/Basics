void CCar::SWheel::ApplyDamage(u16 level)
{
	inherited::ApplyDamage(level);
	if(!joint) return;
	if(level == 0 )return;
	float sf,df;
	//dJointID dj=joint->GetDJoint();
	switch(level) {

	case 1:
		joint->GetJointSDfactors(sf,df);
		sf/=20.f;df*=4.f;
		joint->SetJointSDfactors(sf,df);
		car->m_damage_particles.PlayWheel1(car,bone_id);
		break;
	case 2:
		
		//dVector3 v;
		Fvector v;
		
		//dJointGetHinge2Axis2(dj,v);
		joint->GetAxisDirDynamic( 1, v );

		v[0]+=0.1f;v[1]+=0.1f;v[2]+=0.1f;
		VERIFY( v.magnitude()>EPS_S );
		//accurate_normalize(v);
		v.normalize();

		//dJointSetHinge2Axis2(dj,v[0],v[1],v[2]);
		joint->SetAxisDir( v, 1 );
		joint->GetJointSDfactors(sf,df);
		sf/=30.f;df*=8.f;
		joint->SetJointSDfactors(sf,df);
		car->m_damage_particles.PlayWheel2(car,bone_id);
		break;
	default: NODEFAULT;
	}
	
}