	//--------------------------------------------------------------------------------------
	void PrePixelLightTransform::_SetParameters ()
	{
		Engine& engine = Engine::Instance();
		Device* device = engine.GetDevice();
		Environment* env = engine.GetEnvironment();
		ICamera* camera = engine.GetCamera();

		Matrix44f wvp = *m_pTransform * camera->GetViewProj();

		device->SetShaderParameter(m_hTransform, *m_pTransform);
		if( NULL == m_pColor )
		{
			device->SetShaderParameter(m_hColor, vector4f(1,1,1,1) );
		}
		else
		{
			device->SetShaderParameter(m_hColor, *m_pColor);
		}
		device->SetShaderParameter(m_hNormalTransform, Matrix33f( *m_pTransform ) );
		device->SetShaderParameter(m_hWorldViewProjMatrixLoc, wvp);
		device->SetShaderParameter(m_hLightDirectionLoc, -env->GetCurrentLight().GetWorldDirection());//phong光是像素到光源的方向，所以这里反向
		device->SetShaderParameter(m_hCameraPositionLoc, camera->GetPosition() );
		device->SetShaderParameter(m_hAmbientLoc, env->GetAmbient());
		device->SetShaderParameter(m_hLightLoc, env->GetCurrentLight().GetColor());
		//clean up
		m_pTransform = NULL;
		m_pColor = NULL;
	}