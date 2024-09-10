void S_Shutdown()
{
	if (si.Shutdown)
		si.Shutdown();

	Com_Memset( &si, 0, sizeof(si) );

	Cmd_RemoveCommand( "play" );
	Cmd_RemoveCommand( "music" );
	Cmd_RemoveCommand( "s_list" );
	Cmd_RemoveCommand( "s_stop" );
	Cmd_RemoveCommand( "s_info" );

	S_CodecShutdown();
}