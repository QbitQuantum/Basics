//-------------------------------------------------------------------------------------------------------
void BloomPS::Process(IDriver& driver, const RenderTarget* const org, const RenderTarget* const scene, RenderTarget* const out, bool& isSwitch)
{
	float Range = 2; //控制模糊度

	//降采样
	//driver.PushRenderTarget(m_pDownSimple_1);
	//driver.Clear( IDriver::COLOR_BUFFER );
	//QuadShader& qs = driver.GetShaderManage().GetShader<QuadShader>(ShaderManage::QuadShader);
	//driver.Draw( *m_pRendBuffer, qs, scene->GetColorBuffer() );
	//driver.PopRenderTarget();

	//流明化
	driver.PushRenderTarget(m_pDownSimple_1);
	driver.Clear( IDriver::COLOR_BUFFER );
	Luminance& le = driver.GetShaderManage().GetShader<Luminance>(ShaderManage::Luminance);
	driver.Draw( *m_pRendBuffer, le, scene->GetColorBuffer() );
	driver.PopRenderTarget();

	//x方向模糊
	driver.PushRenderTarget(m_pDownSimple_2);
	driver.Clear( IDriver::COLOR_BUFFER );
	Gaussian& gauss = driver.GetShaderManage().GetShader<Gaussian>(ShaderManage::Gaussian);
	gauss.SetParamStep( vector2f( Range / m_pDownSimple_1->GetSize().m_x, 0.0f ) );
	driver.Draw( *m_pRendBuffer, gauss, m_pDownSimple_1->GetColorBuffer() );
	driver.PopRenderTarget();

	//y方向模糊
	driver.PushRenderTarget(m_pDownSimple_1);
	driver.Clear( IDriver::COLOR_BUFFER );
	gauss.SetParamStep( vector2f( 0.0f, Range / m_pDownSimple_2->GetSize().m_y ) );
	driver.Draw( *m_pRendBuffer, gauss, m_pDownSimple_2->GetColorBuffer() );
	driver.PopRenderTarget();

	driver.PushRenderTarget( out );//如果画在了输出上面，则需要更换输出，下一个pe就用另外一张rt
	isSwitch = true;
	driver.Clear( IDriver::COLOR_BUFFER );
	//if( 0 )
	{
		driver.EnableAlphaBlend(IDriver::BL_SRC_ALPHA, IDriver::BL_ONE_MINUS_SRC_ALPHA, IDriver::BL_SRC_ALPHA, IDriver::BL_ONE_MINUS_SRC_ALPHA );
		Combine& ce = driver.GetShaderManage().GetShader<Combine>(ShaderManage::Combine);
		ce.SetParamOrginial( scene->GetColorBuffer() );
		ce.SetParamSecen( m_pDownSimple_1->GetColorBuffer() );
		ce.SetParamOrginialWeight(1.0f);
		ce.SetParamSecenWeight(0.0f);//was 0.75
		driver.Draw( *m_pRendBuffer, ce, NULL );
	}
	//else
	//{
	//	QuadShader& qs = driver.GetShaderManage().GetShader<QuadShader>(ShaderManage::QuadShader);
	//	driver.Draw( *m_pRendBuffer, qs, m_pDownSimple_1->GetColorBuffer() );
	//	//driver.Draw( *m_pRendBuffer, ui, org->GetDepthBuffer() );
	//}
	driver.PopRenderTarget( );
}