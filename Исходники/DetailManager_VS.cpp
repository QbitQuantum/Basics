void CDetailManager::hw_Render()
{
	// Render-prepare
	//	Update timer
	//	Can't use RDEVICE.fTimeDelta since it is smoothed! Don't know why, but smoothed value looks more choppy!
	float fDelta = RDEVICE.fTimeGlobal-m_global_time_old;
	if ( (fDelta<0) || (fDelta>1))	fDelta = 0.03;
	m_global_time_old = RDEVICE.fTimeGlobal;

	m_time_rot_1	+= (PI_MUL_2*fDelta/swing_current.rot1);
	m_time_rot_2	+= (PI_MUL_2*fDelta/swing_current.rot2);
	m_time_pos		+= fDelta*swing_current.speed;

	//float		tm_rot1		= (PI_MUL_2*RDEVICE.fTimeGlobal/swing_current.rot1);
	//float		tm_rot2		= (PI_MUL_2*RDEVICE.fTimeGlobal/swing_current.rot2);
	float		tm_rot1		= m_time_rot_1;
	float		tm_rot2		= m_time_rot_2;

	Fvector4	dir1,dir2;
	dir1.set				(_sin(tm_rot1),0,_cos(tm_rot1),0).normalize().mul(swing_current.amp1);
	dir2.set				(_sin(tm_rot2),0,_cos(tm_rot2),0).normalize().mul(swing_current.amp2);

	// Setup geometry and DMA
	RCache.set_Geometry		(hw_Geom);

	// Wave0
	float		scale			=	1.f/float(quant);
	Fvector4	wave;
	//wave.set				(1.f/5.f,		1.f/7.f,	1.f/3.f,	RDEVICE.fTimeGlobal*swing_current.speed);
	wave.set				(1.f/5.f,		1.f/7.f,	1.f/3.f,	m_time_pos);
	RCache.set_c			(&*hwc_consts,	scale,		scale,		ps_r__Detail_l_aniso,	ps_r__Detail_l_ambient);				// consts
	RCache.set_c			(&*hwc_wave,	wave.div(PI_MUL_2));	// wave
	RCache.set_c			(&*hwc_wind,	dir1);																					// wind-dir
	hw_Render_dump			(&*hwc_array,	1, 0, c_hdr );

	// Wave1
	//wave.set				(1.f/3.f,		1.f/7.f,	1.f/5.f,	RDEVICE.fTimeGlobal*swing_current.speed);
	wave.set				(1.f/3.f,		1.f/7.f,	1.f/5.f,	m_time_pos);
	RCache.set_c			(&*hwc_wave,	wave.div(PI_MUL_2));	// wave
	RCache.set_c			(&*hwc_wind,	dir2);																					// wind-dir
	hw_Render_dump			(&*hwc_array,	2, 0, c_hdr );

	// Still
	RCache.set_c			(&*hwc_s_consts,scale,		scale,		scale,				1.f);
	RCache.set_c			(&*hwc_s_xform,	RDEVICE.mFullTransform);
	hw_Render_dump			(&*hwc_s_array,	0, 1, c_hdr );
}