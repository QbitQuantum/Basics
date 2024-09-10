void CWeaponStatMgun::UpdateBarrelDir()
{
	IKinematics* K		= smart_cast<IKinematics*>(Visual());
	m_fire_bone_xform	= K->LL_GetTransform(m_fire_bone);

	m_fire_bone_xform.mulA_43		(XFORM());
	m_fire_pos.set					(0,0,0); 
	m_fire_bone_xform.transform_tiny(m_fire_pos);
	m_fire_dir.set					(0,0,1);
	m_fire_bone_xform.transform_dir	(m_fire_dir);

	m_allow_fire		= true;
	Fmatrix				XFi;
	XFi.invert			(XFORM());
	Fvector				dep;
	XFi.transform_dir	(dep,m_destEnemyDir);
	{// x angle
		m_i_bind_x_xform.transform_dir(dep); dep.normalize();
		m_tgt_x_rot		= angle_normalize_signed(m_bind_x_rot-dep.getP());
		float sv_x		= m_tgt_x_rot;
		
		clamp			(m_tgt_x_rot,-m_lim_x_rot.y,-m_lim_x_rot.x);
		if (!fsimilar(sv_x,m_tgt_x_rot,EPS_L)) m_allow_fire=FALSE;
	}
	{// y angle
		m_i_bind_y_xform.transform_dir(dep); dep.normalize();
		m_tgt_y_rot		= angle_normalize_signed(m_bind_y_rot-dep.getH());
		float sv_y		= m_tgt_y_rot;
		clamp			(m_tgt_y_rot,-m_lim_y_rot.y,-m_lim_y_rot.x);
		if (!fsimilar(sv_y,m_tgt_y_rot,EPS_L)) m_allow_fire=FALSE;
	}

	m_cur_x_rot		= angle_inertion_var(m_cur_x_rot,m_tgt_x_rot,0.5f,3.5f,PI_DIV_6,Device.fTimeDelta);
	m_cur_y_rot		= angle_inertion_var(m_cur_y_rot,m_tgt_y_rot,0.5f,3.5f,PI_DIV_6,Device.fTimeDelta);
}