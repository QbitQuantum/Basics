	//--------------------------------------------------------------------------------------
	void VolumeLightPost::_SetParameters ()
	{
		Engine& engine = Engine::Instance();
		Device* device = engine.GetDevice();
		device->SetShaderParameter( m_hTextureHandle, *m_pTexOrginial );

		const Matrix44f& mvp = engine.GetCamera()->GetViewProj();
		vector4f lp( engine.GetCamera()->GetPosition() + engine.GetEnvironment()->GetCurrentLight().GetWorldDirection() * engine.GetCamera()->GetMiddle()  );
		lp *= mvp ;//与摄像机的位置没有关系，所以始终只乘投影矩阵
		lp /= lp.m_w;
		float alpha = 1.0 - Math::Clamp0to1( ( lp.m_x*lp.m_x+lp.m_y*lp.m_y - 1.0 ) / 7.0 );//这个计算公式计算的是在看到太阳前的alpha衰减，假设太阳的曝光极致是在一个屏幕空间内，所以减去2.0，修改这里需要对应修改Environment的Unpdata
		vector2f lps = vector2f(lp.m_x * 0.5 + 0.5, lp.m_y * 0.5 + 0.5);
		device->SetShaderParameter( m_hLightPositionOnScreenHandle, lps );
#ifdef WIN32
		device->SetShaderParameter( m_hExposureHandle, 0.000016f );//最终曝光强度
		device->SetShaderParameter( m_hDecayHandle, 0.98f );//暗线衰减
		device->SetShaderParameter( m_hDensityHandle, 1.2f );//暗线的长度
		device->SetShaderParameter( m_hWeightHandle, 800.0f * alpha );//黑白色差权重
#else
#ifdef LOWVOLUMELIGHT
		device->SetShaderParameter( m_hExposureHandle, 0.0003f );//最终曝光强度
		device->SetShaderParameter( m_hDecayHandle, 0.87f );//暗线衰减
		device->SetShaderParameter( m_hDensityHandle, 0.6f );//暗线的长度
		device->SetShaderParameter( m_hWeightHandle, 550.0f * alpha );//黑白色差权重
#else
		device->SetShaderParameter( m_hExposureHandle, 0.00032f );//最终曝光强度
		device->SetShaderParameter( m_hDecayHandle, 0.88f );//暗线衰减
		device->SetShaderParameter( m_hDensityHandle, 0.8f );//暗线的长度
		device->SetShaderParameter( m_hWeightHandle, 320.0f * alpha );//黑白色差权重
#endif
#endif
	}