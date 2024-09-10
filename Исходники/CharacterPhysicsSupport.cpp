void CCharacterPhysicsSupport::in_Hit(float P,Fvector &dir, CObject *who,s16 element,Fvector p_in_object_space, float impulse,ALife::EHitType hit_type ,bool is_killing)
{
	if(m_EntityAlife.use_simplified_visual	())	return;
	if(m_flags.test(fl_block_hit))
	{
		VERIFY(!m_EntityAlife.g_Alive());
		if(Device.dwTimeGlobal-m_EntityAlife.GetLevelDeathTime()>=2000)
			m_flags.set(fl_block_hit,FALSE);
		else return;
	}
	is_killing=is_killing||(m_eState==esAlive&&!m_EntityAlife.g_Alive());
	if(m_EntityAlife.g_Alive()&&is_killing&&hit_type==ALife::eHitTypeExplosion&&P>70.f)
		CPHDestroyable::Destroy();
	if((!m_EntityAlife.g_Alive()||is_killing)&&!fis_zero(m_shot_up_factor)&&hit_type!=ALife::eHitTypeExplosion)
	{
		dir.y+=m_shot_up_factor;
		dir.normalize();
	}
	if(!m_pPhysicsShell&&is_killing)
	{
		TestForWounded();
		
		ActivateShell(who);
		if (!m_was_wounded)
		{
			impulse*=(hit_type==ALife::eHitTypeExplosion ? 1.f : skel_fatal_impulse_factor);
		}
		m_flags.set(fl_block_hit,TRUE);
	}
	if(!(m_pPhysicsShell&&m_pPhysicsShell->isActive()))
	{
		if(!is_killing&&m_EntityAlife.g_Alive())
			m_PhysicMovementControl->ApplyHit(dir,impulse,hit_type);
	}
	else
	{
		if(m_pPhysicsShell&&m_pPhysicsShell->isActive()) 
			m_pPhysicsShell->applyHit(p_in_object_space,dir,impulse,element,hit_type);
	}
}