InterruptHandler::~InterruptHandler()
{
	StartTrace(InterruptHandler.Dtor);
	if ( GetId() != 0 ) {
		THRKILL(GetId(), SIGTERM);
	}
	Terminate();
	CheckState(Thread::eTerminated);
	if (fServer) {
		fServer->RemovePIDFile();
	}
}