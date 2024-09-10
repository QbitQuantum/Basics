void Helium::RendererInitializationWin::Shutdown()
{
	DynamicDrawer::DestroyStaticInstance();
	RenderResourceManager::DestroyStaticInstance();

	Renderer* pRenderer = Renderer::GetStaticInstance();
	if( pRenderer )
	{
		pRenderer->Shutdown();
		Renderer::DestroyStaticInstance();
	}

	WindowManager* pWindowManager = WindowManager::GetStaticInstance();
	if( pWindowManager )
	{
		if( m_pMainWindow )
		{
			m_pMainWindow->Destroy();
			while( m_pMainWindow )
			{
				pWindowManager->Update();
			}
		}

		pWindowManager->Shutdown();
		WindowManager::DestroyStaticInstance();
	}
}