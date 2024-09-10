void CControllerPsyHit::death_glide_start()
{
	if (!check_conditions_final()) {
		m_man->deactivate	(this);
		return;
	}
	
	HUD().SetRenderable(false);

	// Start effector
	CEffectorCam* ce = Actor()->Cameras().GetCamEffector(eCEControllerPsyHit);
	VERIFY(!ce);
	
	Fvector src_pos		= Actor()->cam_Active()->vPosition;
	Fvector target_pos	= m_object->Position();
	target_pos.y		+= 1.2f;
	
	Fvector				dir;
	dir.sub				(target_pos,src_pos);
	
	float dist			= dir.magnitude();
	dir.normalize		();

	target_pos.mad		(src_pos,dir,dist-4.8f);
	
	Actor()->Cameras().AddCamEffector(new CControllerPsyHitCamEffector(eCEControllerPsyHit, src_pos,target_pos, m_man->animation().motion_time(m_stage[1], m_object->Visual())));
	smart_cast<CController *>(m_object)->draw_fire_particles();

	dir.sub(src_pos,target_pos);
	dir.normalize();
	float h,p;
	dir.getHP(h,p);
	dir.setHP(h,p+PI_DIV_3);
	Actor()->character_physics_support()->movement()->ApplyImpulse(dir,Actor()->GetMass() * 530.f);

	set_sound_state					(eStart);

	NET_Packet			P;
	Actor()->u_EventGen	(P, GEG_PLAYER_WEAPON_HIDE_STATE, Actor()->ID());
	P.w_u32				(INV_STATE_BLOCK_ALL);
	P.w_u8				(u8(true));
	Actor()->u_EventSend(P);
	
	m_blocked			= true;

	//////////////////////////////////////////////////////////////////////////
	// set direction
	SControlDirectionData			*ctrl_dir = (SControlDirectionData*)m_man->data(this, ControlCom::eControlDir); 
	VERIFY							(ctrl_dir);
	ctrl_dir->heading.target_speed	= 3.f;
	ctrl_dir->heading.target_angle	= m_man->direction().angle_to_target(Actor()->Position());

	//////////////////////////////////////////////////////////////////////////
}