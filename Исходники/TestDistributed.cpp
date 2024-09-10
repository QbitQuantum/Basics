// TestZiDebugFormat
//------------------------------------------------------------------------------
void TestDistributed::TestZiDebugFormat() const
{
	FBuildOptions options;
	options.m_ConfigFile = "Data/TestDistributed/fbuild.bff";
	options.m_AllowDistributed = true;
	options.m_NumWorkerThreads = 0;
	options.m_NoLocalConsumptionOfRemoteJobs = true; // ensure all jobs happen on the remote worker
	options.m_AllowLocalRace = false;
	options.m_ForceCleanBuild = true;
	FBuild fBuild( options );

	JobQueueRemote jqr( 1 );

	// start a client to emulate the other end
	Server s;
	s.Listen( Protocol::PROTOCOL_PORT );

	TEST_ASSERT( fBuild.Initialize() );

	TEST_ASSERT( fBuild.Build( AStackString<>( "remoteZi" ) ) );
}