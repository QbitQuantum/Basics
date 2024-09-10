void CCustomZone::PlayEntranceParticles(CGameObject* pObject)
{
	m_entrance_sound.play_at_pos		(0, pObject->Position());

	LPCSTR particle_str				= NULL;

	if(pObject->Radius()<SMALL_OBJECT_RADIUS)
	{
		if(!m_sEntranceParticlesSmall) 
			return;

		particle_str = m_sEntranceParticlesSmall.c_str();
	}
	else
	{
		if(!m_sEntranceParticlesBig) 
			return;

		particle_str				= m_sEntranceParticlesBig.c_str();
	}

	Fvector							vel;
	CPhysicsShellHolder* shell_holder=smart_cast<CPhysicsShellHolder*>(pObject);
	if(shell_holder)
		shell_holder->PHGetLinearVell(vel);
	else 
		vel.set						(0,0,0);
	
	//выбрать случайную косточку на объекте
	CParticlesPlayer* PP			= smart_cast<CParticlesPlayer*>(pObject);
	if (PP)
	{
		u16 play_bone				= PP->GetRandomBone(); 
		
		if (play_bone!=BI_NONE)
		{
			CParticlesObject* pParticles = CParticlesObject::Create(particle_str, TRUE);
			Fmatrix					xform;
			Fvector					dir;
			if(fis_zero				(vel.magnitude()))
				dir.set				(0,1,0);
			else
			{
				dir.set				(vel);
				dir.normalize		();
			}

			PP->MakeXFORM			(pObject,play_bone,dir,Fvector().set(0,0,0),xform);
			pParticles->UpdateParent(xform, vel);
			pParticles->Play		(false);
		}
	}
	if(m_zone_flags.test(eBoltEntranceParticles) && smart_cast<CBolt*>(pObject))
		PlayBoltEntranceParticles();
}