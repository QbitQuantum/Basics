//-----------------------------------------------------------------------------
// Called when the layoff texture needs to be released
//-----------------------------------------------------------------------------
void CMiniViewportEngineRenderArea::ReleaseLayoffTexture()
{
	m_ScreenBuffer.Shutdown();
	m_ScreenMaterial.Shutdown();
}