void FMessageBridge::HandleMessageBusShutdown( )
{
	Shutdown();
	Bus.Reset();
}