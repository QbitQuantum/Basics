//-------------------------
//  FX_AddLight
//-------------------------
CLight *FX_AddLight( vec3_t org, float size1, float size2, float sizeParm,
							vec3_t rgb1, vec3_t rgb2, float rgbParm,
							int killTime, int flags = 0, 
							EMatImpactEffect matImpactFX /*MATIMPACTFX_NONE*/, int fxParm /*-1*/,
							int iGhoul2/*0*/, int entNum/*-1*/, int modelNum/*-1*/, int boltNum/*-1*/)
{
	if ( theFxHelper.mFrameTime < 0 )
	{ // disallow adding effects when the system is paused
		return 0;
	}

	CLight *fx = new CLight;

	if ( fx )
	{
		if (flags&FX_RELATIVE && iGhoul2>0)
		{
			fx->SetOrigin1( NULL );
			fx->SetOrgOffset( org );//offset
			fx->SetBoltinfo( iGhoul2, entNum, modelNum, boltNum );
		}
		else
		{
			fx->SetOrigin1( org );
		}
		fx->SetMatImpactFX(matImpactFX);
		fx->SetMatImpactParm(fxParm);

		// RGB----------------
		fx->SetRGBStart( rgb1 );
		fx->SetRGBEnd( rgb2 );

		if (( flags & FX_RGB_PARM_MASK ) == FX_RGB_WAVE )
		{
			fx->SetRGBParm( rgbParm * PI * 0.001f );
		}
		else if ( flags & FX_RGB_PARM_MASK )
		{
			// rgbParm should be a value from 0-100..
			fx->SetRGBParm(rgbParm * 0.01f * killTime + theFxHelper.mTime + theFxHelper.mTimeFraction);
		}

		// Size----------------
		fx->SetSizeStart( size1 );
		fx->SetSizeEnd( size2 );

		if (( flags & FX_SIZE_PARM_MASK ) == FX_SIZE_WAVE )
		{
			fx->SetSizeParm( sizeParm * PI * 0.001f );
		}
		else if ( flags & FX_SIZE_PARM_MASK )
		{
			fx->SetSizeParm(sizeParm * 0.01f * killTime + theFxHelper.mTime + theFxHelper.mTimeFraction);
		}

		fx->SetFlags( flags );

		FX_AddPrimitive( (CEffect**)&fx, killTime );
	}

	return fx;

}