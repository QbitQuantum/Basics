void CHelicopter::UpdateMGunDir()
{
	IKinematics* K		= smart_cast<IKinematics*>(Visual());
	m_fire_bone_xform	= K->LL_GetTransform(m_fire_bone);

	m_fire_bone_xform.mulA_43	(XFORM());
	m_fire_pos.set				(0,0,0); 
	m_fire_bone_xform.transform_tiny(m_fire_pos);
	m_fire_dir.set				(0,0,1);
	m_fire_bone_xform.transform_dir(m_fire_dir);
	
	m_fire_dir.sub				(m_enemy.destEnemyPos,m_fire_pos).normalize_safe();

	m_left_rocket_bone_xform	= K->LL_GetTransform(m_left_rocket_bone);
	m_left_rocket_bone_xform.mulA_43	(XFORM());
	m_left_rocket_bone_xform.c.y += 1.0f;
	//.fake
	m_right_rocket_bone_xform	= K->LL_GetTransform(m_right_rocket_bone);
	m_right_rocket_bone_xform.mulA_43	(XFORM());
	m_right_rocket_bone_xform.c.y += 1.0f;
	//.fake

	m_allow_fire		= TRUE;
	Fmatrix XFi;
	XFi.invert			(XFORM());
	Fvector dep;
	XFi.transform_tiny	(dep,m_enemy.destEnemyPos);
	{// x angle
		Fvector A_;		A_.sub(dep,m_bind_x);	m_i_bind_x_xform.transform_dir(A_); A_.normalize();
		m_tgt_rot.x		= angle_normalize_signed(m_bind_rot.x-A_.getP());
		float sv_x		= m_tgt_rot.x;
		clamp			(m_tgt_rot.x,-m_lim_x_rot.y,-m_lim_x_rot.x);
		if (!fsimilar(sv_x,m_tgt_rot.x,EPS_L)) m_allow_fire=FALSE;
	}
	{// y angle
		Fvector A_;		A_.sub(dep,m_bind_y);	m_i_bind_y_xform.transform_dir(A_); A_.normalize();
		m_tgt_rot.y		= angle_normalize_signed(m_bind_rot.y-A_.getH());
		float sv_y		= m_tgt_rot.y;
		clamp			(m_tgt_rot.y,-m_lim_y_rot.y,-m_lim_y_rot.x);
		if (!fsimilar(sv_y,m_tgt_rot.y,EPS_L)) m_allow_fire=FALSE;
	}
	
	if ((angle_difference(m_cur_rot.x,m_tgt_rot.x)>deg2rad(m_barrel_dir_tolerance))||
		(angle_difference(m_cur_rot.y,m_tgt_rot.y)>deg2rad(m_barrel_dir_tolerance)))
		m_allow_fire=FALSE;

}