void
showPomdpSolveParams( PomdpSolveParams params )
{
  ConfigFile cfg;

  fprintf( params->report_file,
		 " //****************\\\\\n" );
  fprintf( params->report_file,
		 "||   %s    ||\n", params->opts->__exec_name__ );
  fprintf( params->report_file,
		 "||     v. %s       ||\n", params->opts->__version__ );
  fprintf( params->report_file,
		 " \\\\****************//\n" );
  fprintf( params->report_file,
		 "      PID=%d\n", getPid() );

  cfg = POMDP_SOLVE_OPTS_toConfigFile( params->opts );

  fprintf( params->report_file,
		 "- - - - - - - - - - - - - - - - - - - -\n" );

  CF_fprintf( cfg, params->report_file );

  fprintf( params->report_file,
		 "- - - - - - - - - - - - - - - - - - - -\n" );

  CF_delete( cfg );


} /* showPomdpSolveParams */