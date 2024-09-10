void OniTrackApp::shutdown()
{
	delete pSessionGenerator;
	
	context.Shutdown();
}