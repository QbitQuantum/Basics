//-----------------------------------------------------------------------------------------------
void Initialize( HINSTANCE applicationInstanceHandle )
{
	CreateOpenGLWindow( applicationInstanceHandle );
	OpenGLRenderer::Initalize();
	InitializeTime();
	LoadTextures();
	LoadDeveloperConsole();
	g_game.Initialize();
}