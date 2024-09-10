bool FEditorEngine::Init()
{
	guard;

	RegisterWindowClasses();

	Instance = new FInstance( this );
	Instance->Init();

	RenderPlugin = new FPlugin();
	RenderPlugin->LoadPlugin( GConfig->ReadString( L"RenderDevice" ) );
	if (!RenderPlugin->LoadInterface())
	{
		Logf( LOG_CRIT, L"Cannot load DeviceInterfacePtr() in render plugin '%s", RenderPlugin->GetFilepath() );
		Throw( L"Cannot load DeviceInterfacePtr() in render plugin", true );
	}
	Render = (FRenderDevice*)(RenderPlugin->GetInterface())();
	Render->Init();

	return true;

	unguard;
}