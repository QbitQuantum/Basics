/*
================
rvDebuggerApp::~rvDebuggerApp
================
*/
rvDebuggerApp::~rvDebuggerApp ( )
{
	if ( mAccelerators )
	{
		DestroyAcceleratorTable ( mAccelerators );
	}
}