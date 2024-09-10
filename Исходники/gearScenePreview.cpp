void gearScenePreview::reinitPreviewWorld()
{
	if(m_pPreviewWorldPtr)
		m_pPreviewWorldPtr->resetWorld();
	m_pPreviewWorldPtr=monoWrapper::mono_engine_getWorld(1);
	m_pPreviewWorldPtr->getActiveCamera()->setNear(1.0f);
	object3d* light=engine_createLight(m_pPreviewWorldPtr, "Light", gxLight::LIGHT_DIRECTIONAL);
	((gxLight*)light)->setDiffuseColor(vector4f(0.75f, 0.75f, 0.75f, 1.0f));
	((gxLight*)light)->setAmbientColor(vector4f(0.2f, 0.2f, 0.2f, 1.0f));
	((gxLight*)light)->setSpecularColor(vector4f(0.5f, 0.5f, 0.5f, 1.0f));
	((gxLight*)light)->setConstantAttenuation(0.5f);
	light->updatePositionf(-1, -10, 1);
	m_pLightPtr=light;
}