void CEnvironment::Render( float fDeltaSec_ )
{
	DCam().LoadOnDevice();

	bool bInWater = false;
	// Water System
	if( !m_WaterSystem.Empty() )
	{
		m_WaterSystem.RenderPrepare( DCam() );
		if( m_WaterSystem.CheckPtInWater( DCam().Position(), NULL ) )
		{
			bInWater = true;
		}
	}

	// Blend Colors
	SColor SkyColor;
	SColor SunLightColor;
	SColor MoonLightColor;
	if( m_fBlendingAge<0.0f )
	{// not on blending
		SkyColor = m_SkyColor;
		SunLightColor = m_SunLightColor;
		MoonLightColor = m_MoonLightColor;
	}
	else
	{
		m_fBlendingAge += fDeltaSec_;
		if( m_fBlendingAge>m_fBlendingLife )
		{// end of blending
			m_fBlendingAge = -1.0f;

			SkyColor = m_SkyColor = m_SkyColorBlend;
			SunLightColor = m_SunLightColor = m_SunLightColorBlend;
			MoonLightColor = m_MoonLightColor = m_MoonLightColorBlend;
		}
		else
		{// blend it!

			float fBlendingRatio = m_fBlendingAge/m_fBlendingLife;

			SkyColor.Lerp( m_SkyColor, m_SkyColorBlend, fBlendingRatio );
			SunLightColor.Lerp( m_SunLightColor, m_SunLightColorBlend, fBlendingRatio );
			MoonLightColor.Lerp( m_MoonLightColor, m_MoonLightColorBlend, fBlendingRatio );
		}
	}

	// Render Environment 
	DRenderUtil().UpdateRenderState( DRenderUtility::SblkNormal );
	DCtrl()->SetClearColor( SkyColor.DWColor() );
	// 2004/04/01 by impurity fov is dynamic not using map and enviroment fov
//	DProj().ModifyFov( m_fFovSelf );
	DProj().ModifyNear( m_fClipNearSelf );
	DProj().ModifyFar( m_fClipFarSelf );
	DProj().LoadOnDevice();

	// time
	CalculateTimeState( fDeltaSec_ );

	DCtrl()->SetPixelFog( false, 0x000000, 0.0, 10.0f );

	//////////////////////////////////////////////////////////////////
	//::Sun (Pre-Calculation)
	{
		if( m_bDay )
		{
			int nTimeLocal = (int)m_TimeDetail.m_dwHours - (int)m_nDayStartHour;
			if( nTimeLocal<0 )
			{
				nTimeLocal += 24;
			}
			float fRisingRate = nTimeLocal /(float)(m_nDayEndHour-m_nDayStartHour) /2.0f;

			float fScale = (float)(m_nDayEndHour-m_nDayStartHour)/12.0f;
			// 분 적용
			fRisingRate += (((float)m_TimeDetail.m_dwMinutes/60.0f/24.0f) / fScale);
			// 초 적용
			fRisingRate += (((float)m_TimeDetail.m_dwSeconds/60.0f/24.0f/60.0f) / fScale);
		
			assert( fRisingRate<0.51f && fRisingRate>-0.01f );
			m_Sun.Rise( fRisingRate );
		}
		else
		{
			int nTimeLocal = (int)m_TimeDetail.m_dwHours - (int)m_nDayEndHour;
			if( nTimeLocal<0 )
			{
				nTimeLocal += 24;
			}
			float fRisingRate = nTimeLocal /(float)(24-(m_nDayEndHour-m_nDayStartHour)) /2.0f + 0.5f;
			
			float fScale = (float)(24-(m_nDayEndHour-m_nDayStartHour))/12.0f;
			// 분 적용
			fRisingRate += (((float)m_TimeDetail.m_dwMinutes/60.0f/24.0f) / fScale);
			// 초 적용
			fRisingRate += (((float)m_TimeDetail.m_dwSeconds/60.0f/24.0f/60.0f) / fScale);
			
			assert( fRisingRate>0.49f && fRisingRate<1.01f );
			m_Sun.Rise( fRisingRate );
		}
	}

	
	//////////////////////////////////////////////////////////////////
	// Sky
	m_SkyBox.CalculateBoxColor( m_Sun.RisingRate() );
	m_SkyBox.RenderBlending( fDeltaSec_ );

	// set state
	dword dwZPrev;
	Scud::g_pDevice->GetRenderState( D3DRS_ZENABLE, &dwZPrev );
	Scud::g_pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );

	//////////////////////////////////////////////////////////////////
	//::Ambient
	m_CurrentAmbient = LerpColorMap( m_Sun.RisingRate(), m_aAmbientMap );

	//////////////////////////////////////////////////////////////////
	//::Sun (Render)
	m_Sun.RenderBlending( fDeltaSec_ );

	//::Moon
	{
		float fRisingRate = m_Sun.RisingRate()+0.5f;
		if( fRisingRate>1.0f ) { fRisingRate-=1.0f; }
		m_Moon.Rise( fRisingRate );
	}
	m_Moon.RenderBlending( fDeltaSec_ );

	//::Cloud
	DCtrl()->SetPixelFog( true, SkyColor.DWColor(), m_Cloud.FadeOutBegin(), m_Cloud.FadeOutEnd() );
	m_Cloud.ProgressTexCoord( true, fDeltaSec_*m_Cloud.GetTexAni().X, fDeltaSec_*m_Cloud.GetTexAni().Y );
	m_Cloud.RenderBlending( fDeltaSec_ );
	DCtrl()->SetPixelFog( false, 0x000000, 0.0, 10.0f );

	//::Fog, and a Band of Fog
	if( !bInWater )
	{
		m_FogBand.CalculateFogColor( m_Sun.RisingRate() );
	}
	else
	{
		m_FogBand.SetColor( m_WaterColor );
	}
	m_FogBand.RenderBlending( fDeltaSec_ );
	//////////////////////////////////////////////////////////////////

	//::LensFlare (calculate only)
	{
		SVector vSunDir;
		m_Sun.AcquireDirection( vSunDir );
		m_LensFlare.CalculateSpots( m_Sun.RisingRate(), vSunDir );
	}


	// restore state
	Scud::g_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0 );
	Scud::g_pDevice->SetRenderState( D3DRS_ZENABLE, dwZPrev );
	DCam().LoadOnDevice();

	//////////////////////////////////////////////////////////////////
	// Lod
	if( !bInWater )
	{
		m_Lod.CaculateLod( m_fClipFar, m_FogBand.FogBegin(), m_FogBand.FogEnd() );
		// 2004/04/01 by impurity fov is dynamic not using map and enviroment fov
//		DProj().ModifyFov( m_fFov );
		DProj().ModifyNear( m_fClipNear );
		DProj().ModifyFar( m_Lod.ClipFar() );
		DProj().LoadOnDevice();

		// Apply Variable To Outer
		CalculateGlobalLight( SunLightColor, MoonLightColor );
		DCtrl()->SetPixelFog( true, m_FogBand.FogColor().DWColor(), m_Lod.FogBegin(), m_Lod.FogEnd() );
	}
	else
	{// mode in water
		// 2004/04/01 by impurity fov is dynamic not using map and enviroment fov
//		DProj().ModifyFov( m_fFov );
		DProj().ModifyNear( m_fClipNear );
		DProj().ModifyFar( 18.0f );
		DProj().LoadOnDevice();

		// Apply Variable To Outer
		CalculateGlobalLight( SunLightColor, MoonLightColor );
		DCtrl()->SetPixelFog( true, m_WaterColor, 1.0f, 25.0f );
	}

}