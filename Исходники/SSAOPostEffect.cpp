	//-------------------------------------------------------------------------------------------------------
	void SSAOPostEffect::Process( Engine& engine, const RenderTarget* const org, const RenderTarget* const scene, RenderTarget* const out )
	{
		engine.GetDevice()->DisableDepthTest();
		engine.GetDevice()->DisableAlpha();

		{
			engine.GetDevice()->PushRenderTarget(m_pDownSimple_1);

			SSAOShader& ssao = engine.GetShaderManage()->GetShader<SSAOShader>(ShaderManage::SSAOShader);
			ssao.SetParamDepthTex( org->GetDepthBuffer() );
			ssao.SetParamJitterTex( m_JitterTex );
			ssao.SetParamNormalTex( engine.GetPipeline()->NormalRenderTarget()->GetColorBuffer() );
			ssao.SetParamAOEdgeFinder( AOEdgeFinder );
			ssao.SetParamAOIntensity( AOIntensity );
			ssao.SetParamJitterAmount( JitterAmount );
			ssao.SetParamStepSize( vector2f( 1.0 / m_pDownSimple_1->GetSize().m_x , 1.0 / m_pDownSimple_1->GetSize().m_y ) );
			engine.GetDevice()->Draw( *m_pRendBuffer, ssao, NULL );
			engine.GetDevice()->PopRenderTarget();

		}

		{//模糊
			//x
			engine.GetDevice()->PushRenderTarget(m_pDownSimple_2);
			engine.GetDevice()->Clear( Device::COLOR_BUFFER );
			Blur2x2Shader& bs = engine.GetShaderManage()->GetShader<Blur2x2Shader>(ShaderManage::Blur2x2Shader);
			bs.SetParamColorTexture( m_pDownSimple_1->GetColorBuffer() );
			bs.SetParamStepSize( vector2f( (1.0f / m_pDownSimple_2->GetSize().m_x) * GaussSpread, 0.0 ) );
			bs.SetParamGaussWeight( GaussWeight );
			engine.GetDevice()->Draw( *m_pRendBuffer, bs, NULL );
			engine.GetDevice()->PopRenderTarget();

			//y
			engine.GetDevice()->PushRenderTarget(m_pDownSimple_1);
			engine.GetDevice()->Clear( Device::COLOR_BUFFER );
			bs.SetParamColorTexture( m_pDownSimple_2->GetColorBuffer() );
			bs.SetParamStepSize( vector2f( 0.0, (1.0f / m_pDownSimple_1->GetSize().m_y) * GaussSpread ) );
			bs.SetParamGaussWeight( GaussWeight );
			engine.GetDevice()->Draw( *m_pRendBuffer, bs, NULL );
			engine.GetDevice()->PopRenderTarget();
		}

		engine.GetDevice()->PushRenderTarget( out );//如果画在了输出上面，则需要更换输出，下一个pe就用另外一张rt
		engine.GetDevice()->Clear( Device::COLOR_BUFFER );
		if( 1 )
		{
			SSAOCombine& sc = engine.GetShaderManage()->GetShader<SSAOCombine>(ShaderManage::SSAOCombine);
			sc.SetParamSceneTexture( scene->GetColorBuffer() );
			sc.SetParamSSVOTexture( m_pDownSimple_1->GetColorBuffer() );
			engine.GetDevice()->Draw( *m_pRendBuffer, sc, NULL );
		}
		else
		{
			QuadShader& qs = engine.GetShaderManage()->GetShader<QuadShader>(ShaderManage::QuadShader);
			//engine.GetDevice()->Draw( *m_pRendBuffer, qs, engine.GetPipeline()->NormalRenderTarget()->GetColorBuffer() );
			engine.GetDevice()->Draw( *m_pRendBuffer, qs, m_pDownSimple_1->GetColorBuffer() );
		}
		engine.GetDevice()->PopRenderTarget( );
	}