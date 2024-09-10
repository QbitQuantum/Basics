int main( int argc, char *argv[])
{
  Arb_connection *conn = NULL;
  int rc;
  int i;

  char server[128];
  char database[128];		/* schema */
  char user[128];
  char password[128];
  char application[128];
  char infile[256];
  Widget widgets[WIDGET_ARRSZ];
  short  iind[WIDGET_ARRSZ][MAX_TBL_COLS];
  
  memset( widgets, 0, sizeof(widgets));
  memset( iind, 0, sizeof(iind));


  get_env_param( argc, argv, 0, server, database, user, password);

  strcpy( application, __FILE__);

#if 0
  printf( "server   = '%s'\n"
	  "database = '%s'\n"
	  "user     = '******'\n"
	  "password = '******'\n"
	  "application = '%s'\n",
	  server, database, user, password, application);
#endif


  init_DLAYER_THREAD();
  rc = arb_database_login( server, database, user, password, application,
			   ALLOW_BCP, &conn);


  if( rc == SUCCESS)
    puts( "Login successful.");
  else
    {
      puts( "Login failed.");
      exit(1);
    }

  rc = arb_enable_logging( "widget1.log");
  if( rc == SUCCESS)
    puts( "Logging enabled.");
  else
    puts( "Logging failed."), abort();



  drop_table( conn, TABLENAME);
  create_testcols_table( conn);
  create_insert_procedure( conn);
  init_Widgets( widgets);


  populate_table( conn, widgets);
  arb_close(conn,1);

  exit_DLAYER_THREAD();

  return 0;
}