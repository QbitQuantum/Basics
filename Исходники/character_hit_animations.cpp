void character_hit_animation_controller::PlayHitMotion( const Fvector &dir, const Fvector &bone_pos, u16 bi, CEntityAlive &ea )const
{
	IRenderVisual *pV = ea.Visual( );
	IKinematicsAnimated* CA = smart_cast<IKinematicsAnimated*>( pV );
	IKinematics* K = smart_cast<IKinematics*>( pV );
	
	//play_cycle(CA,all_shift_down,1,block_times[6],1) ;
	if( !( K->LL_BoneCount( ) > bi ) )
		return;

	Fvector dr = dir;
	Fmatrix m;
	GetBaseMatrix( m, ea );

#ifdef DEBUG
	if( ph_dbg_draw_mask1.test( phDbgHitAnims ) )
	{
		DBG_OpenCashedDraw();
		DBG_DrawLine( m.c, Fvector( ).sub( m.c, Fvector( ).mul( dir, 1.5 ) ), D3DCOLOR_XRGB( 255, 0, 255 ) );
		DBG_ClosedCashedDraw( 1000 );
	}
#endif

	m.invert( );
	m.transform_dir( dr );
//
	Fvector hit_point;
	K->LL_GetTransform( bi ).transform_tiny( hit_point, bone_pos );
	ea.XFORM( ).transform_tiny( hit_point );
	m.transform_tiny( hit_point );
	Fvector torqu;		
	torqu.crossproduct( dr, hit_point );
	hit_point.x = 0;


	float rotational_ammount = hit_point.magnitude( ) * g_params.power_factor * g_params.rotational_power_factor;//_abs(torqu.x)
	
	if( torqu.x < 0 )
		play_cycle( CA, hit_downr, 3, block_blends[7], 1 ) ;
	else
		play_cycle( CA, hit_downl, 3, block_blends[6], 1 ) ;

	if( !IsEffected( bi, *K ) )
		return;
	if( torqu.x<0 )
		play_cycle( CA, turn_right, 2, block_blends[4], rotational_ammount ) ;
	else
		play_cycle( CA, turn_left, 2, block_blends[5], rotational_ammount ) ;

	//CA->LL_SetChannelFactor(3,rotational_ammount);

	dr.x = 0;
	dr.normalize_safe();


	dr.mul(g_params.power_factor);
	if( dr.y > g_params.side_sensitivity_threshold )
		play_cycle( CA, rthit_motion, 2, block_blends[0], _abs( dr.y ) ) ;
	else if( dr.y < -g_params.side_sensitivity_threshold )
		play_cycle( CA, lthit_motion, 2, block_blends[1], _abs( dr.y ) ) ;

	if( dr.z<0.f )
		play_cycle( CA, fvhit_motion, 2, block_blends[2], _abs(dr.z) ) ;
	else
		play_cycle( CA, bkhit_motion, 2, block_blends[3], _abs( dr.z ) ) ;

	CA->LL_SetChannelFactor( 2, g_params.anim_channel_factor );


}