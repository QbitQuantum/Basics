// Child reaper
int
ForkWork::Reaper( int exitPid, int /*exitStatus*/ )
{
	ForkWorker	*worker;

	// Let's find out if it's one of our children...
	workerList.Rewind( );
	while ( workerList.Next( worker ) ) {
		if ( worker->getPid() == exitPid ) {
			workerList.DeleteCurrent( );
			delete worker;	
		return 0;
		}
	}
	return 0;
}