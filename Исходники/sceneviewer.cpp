void CSceneViewerApp::ShutdownDefaultEnvCubemap( )
{
	CMatRenderContextPtr pRenderContext( g_pMaterialSystem );
	pRenderContext->BindLocalCubemap( NULL );
	m_DefaultEnvCubemap.Shutdown( );
}