	r1v_lmap	(Fvector3 _P, Fvector _N, base_basis _T, base_basis _B, base_color _CC, Fvector2 tc_base, Fvector2 tc_lmap )
	{
		base_color_c	_C;	_CC._get	(_C);
		_N.normalize		();
		std::pair<s16,u8>	tc_u		= s24_tc_base	(tc_base.x);
		std::pair<s16,u8>	tc_v		= s24_tc_base	(tc_base.y);
		P				= _P;
		N				= u8_vec4		(_N,u8_clr(_C.hemi));
		T				= u8_vec4		(_T,tc_u.second);
		B				= u8_vec4		(_B,tc_v.second);
		tc0x			= tc_u.first	;	
		tc0y			= tc_v.first	;
		tc1x			= s16_tc_lmap	(tc_lmap.x);
		tc1y			= s16_tc_lmap	(tc_lmap.y);
	}