void ReleaseRenderTargets( void )
{
	s_pPowerOfTwoFrameBufferTexture.Shutdown();
	s_pCameraTexture.Shutdown();
	s_pWaterReflectionTexture.Shutdown();
	s_pWaterRefractionTexture.Shutdown();
	s_pQuarterSizedFB0.Shutdown();
	s_pQuarterSizedFB1.Shutdown();
	s_pFullFrameDepthTexture.Shutdown();
	s_pScopeTexture.Shutdown();

	for (int i=0; i<MAX_FB_TEXTURES; ++i)
		s_pFullFrameFrameBufferTexture[i].Shutdown();
}