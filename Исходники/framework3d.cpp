void Framework3D::Main()
{
	XTRACE_FUNCTION;

	Initialize();
	while( Tick() );
	ShutDown();
}