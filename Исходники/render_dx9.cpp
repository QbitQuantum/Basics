bool InitResourceDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();

	D3DCAPS9 caps;
	device->GetDeviceCaps(&caps);

	if ( caps.PixelShaderVersion < D3DPS_VERSION(3,0) )
	{
		printf("Requires Pixel Shader 3.0\n");
		return false;
	}

	for ( int i=0; i<TEX_TEXTURES; i++ )
	{
		g_pTextures[i] = NULL;
		g_pSurfaces[i] = NULL;
	}

	if ( !ReInitResourceDX9() )
		return false;

	g_pParticleFX = GutLoadFXShaderDX9("../../shaders/GPUParticle.fx");
	if ( NULL==g_pParticleFX )
		return false;

	g_pParticleRenderFX = GutLoadFXShaderDX9("../../shaders/GPUParticle_render.fx");
	if ( NULL==g_pParticleRenderFX )
		return false;

	g_pPostFX = GutLoadFXShaderDX9("../../shaders/Posteffect.fx");
	if ( NULL==g_pPostFX )
		return false;

	g_pNoiseTexture = GutLoadTexture_DX9("../../textures/noise_512x512.tga");
	if ( NULL==g_pNoiseTexture )
		return false;

	g_pParticleTexture = GutLoadTexture_DX9("../../textures/particle.tga");
	if ( NULL==g_pParticleTexture )
		return false;

	return true;
}