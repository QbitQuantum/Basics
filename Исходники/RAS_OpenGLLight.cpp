void RAS_OpenGLLight::BindShadowBuffer(RAS_ICanvas *canvas, KX_Camera *cam, MT_Transform& camtrans)
{
	GPULamp *lamp;
	float viewmat[4][4], winmat[4][4];
	int winsize;

	/* bind framebuffer */
	lamp = GetGPULamp();
	GPU_lamp_shadow_buffer_bind(lamp, viewmat, &winsize, winmat);

	if (GPU_lamp_shadow_buffer_type(lamp) == LA_SHADMAP_VARIANCE) {
		m_rasterizer->SetShadowMode(RAS_IRasterizer::RAS_SHADOW_VARIANCE);
	}
	else {
		m_rasterizer->SetShadowMode(RAS_IRasterizer::RAS_SHADOW_SIMPLE);
	}

	/* GPU_lamp_shadow_buffer_bind() changes the viewport, so update the canvas */
	canvas->UpdateViewPort(0, 0, winsize, winsize);

	/* setup camera transformation */
	MT_Matrix4x4 modelviewmat((float *)viewmat);
	MT_Matrix4x4 projectionmat((float *)winmat);

	MT_Transform trans = MT_Transform((float *)viewmat);
	camtrans.invert(trans);

	cam->SetModelviewMatrix(modelviewmat);
	cam->SetProjectionMatrix(projectionmat);

	cam->NodeSetLocalPosition(camtrans.getOrigin());
	cam->NodeSetLocalOrientation(camtrans.getBasis());
	cam->NodeUpdateGS(0);

	/* setup rasterizer transformations */
	/* SetViewMatrix may use stereomode which we temporarily disable here */
	RAS_IRasterizer::StereoMode stereomode = m_rasterizer->GetStereoMode();
	m_rasterizer->SetStereoMode(RAS_IRasterizer::RAS_STEREO_NOSTEREO);
	m_rasterizer->SetProjectionMatrix(projectionmat);
	m_rasterizer->SetViewMatrix(modelviewmat, cam->NodeGetWorldOrientation(), cam->NodeGetWorldPosition(), cam->NodeGetLocalScaling(), cam->GetCameraData()->m_perspective);
	m_rasterizer->SetStereoMode(stereomode);
}