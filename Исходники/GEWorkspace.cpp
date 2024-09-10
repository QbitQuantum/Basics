rvGEWorkspace::~rvGEWorkspace ( )
{
	// Make sure all the wrappers get cleaned up
	rvGEWindowWrapper::GetWrapper ( mInterface->GetDesktop ( ) )->EnumChildren ( CleanupEnumProc, NULL );

	DestroyCursor ( mHandCursor );

	delete mInterface;
}