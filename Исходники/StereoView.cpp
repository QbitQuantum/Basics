void StereoView::InitShaderEffects()
{
	
	shaderEffect[SIDE_BY_SIDE] = "SideBySide.fx";

	char viewPath[512];
	ProxyHelper helper = ProxyHelper();
	helper.GetPath(viewPath, "fx\\");

	strcat_s(viewPath, 512, shaderEffect[stereo_mode].c_str());

	if (FAILED(D3DXCreateEffectFromFile(m_pActualDevice, viewPath, NULL, NULL, D3DXFX_DONOTSAVESTATE, NULL, &viewEffect, NULL))) {
		OutputDebugString("Effect creation failed\n");
	}
}