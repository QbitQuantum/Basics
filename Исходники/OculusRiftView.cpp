/**
* Loads Oculus Rift shader effect files.
***/ 
void OculusRiftView::InitShaderEffects()
{
	//Currently, RiftUp DK1 and DK2 share the same shader effects
	shaderEffect[RIFTUP] = "OculusRift.fx";
	shaderEffect[OCULUS_RIFT_DK1] = "OculusRift.fx";
	shaderEffect[OCULUS_RIFT_DK1_CROPPED] = "OculusRiftCropped.fx";
	shaderEffect[OCULUS_RIFT_DK2] = "OculusRiftDK2.fx";
	shaderEffect[OCULUS_RIFT_DK2_CROPPED] = "OculusRiftDK2Cropped.fx";

	char viewPath[512];
	ProxyHelper helper = ProxyHelper();
	helper.GetPath(viewPath, "fx\\");

	strcat_s(viewPath, 512, shaderEffect[stereo_mode].c_str());

	D3DXCreateEffectFromFile(m_pActualDevice, viewPath, NULL, NULL, 0, NULL, &viewEffect, NULL);
}