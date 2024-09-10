void InstallAllocationFunctions()
{
	_set_new_mode( 1 ); // so if malloc() fails, we exit.
	_set_new_handler( CmdLib_NewHandler );
}