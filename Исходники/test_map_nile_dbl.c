int
main (int argc, char *argv[])
{
    int result = 0;
    int ret;
    char *err_msg = NULL;
    sqlite3 *db_handle;
    void *cache = spatialite_alloc_connection ();
    void *priv_data = rl2_alloc_private ();
    char *old_SPATIALITE_SECURITY_ENV = NULL;

    if (argc > 1 || argv[0] == NULL)
	argc = 1;		/* silencing stupid compiler warnings */

    old_SPATIALITE_SECURITY_ENV = getenv ("SPATIALITE_SECURITY");
#ifdef _WIN32
    putenv ("SPATIALITE_SECURITY=relaxed");
#else /* not WIN32 */
    setenv ("SPATIALITE_SECURITY", "relaxed", 1);
#endif

/* opening and initializing the "memory" test DB */
    ret = sqlite3_open_v2 (":memory:", &db_handle,
			   SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (ret != SQLITE_OK)
      {
	  fprintf (stderr, "sqlite3_open_v2() error: %s\n",
		   sqlite3_errmsg (db_handle));
	  return -1;
      }
    spatialite_init_ex (db_handle, cache, 0);
    rl2_init (db_handle, priv_data, 0);
    ret =
	sqlite3_exec (db_handle, "SELECT InitSpatialMetadata(1)", NULL, NULL,
		      &err_msg);
    if (ret != SQLITE_OK)
      {
	  fprintf (stderr, "InitSpatialMetadata() error: %s\n", err_msg);
	  sqlite3_free (err_msg);
	  return -2;
      }
    ret =
	sqlite3_exec (db_handle, "SELECT CreateRasterCoveragesTable()", NULL,
		      NULL, &err_msg);
    if (ret != SQLITE_OK)
      {
	  fprintf (stderr, "CreateRasterCoveragesTable() error: %s\n", err_msg);
	  sqlite3_free (err_msg);
	  return -3;
      }

/* SRTM NILE-DOUBLE (GRID) tests */
    ret = -100;
    if (!test_coverage (db_handle, RL2_SAMPLE_INT8, TILE_256, &ret))
	return ret;
    ret = -120;
    if (!test_coverage (db_handle, RL2_SAMPLE_INT8, TILE_1024, &ret))
	return ret;
    ret = -140;
    if (!test_coverage (db_handle, RL2_SAMPLE_UINT8, TILE_256, &ret))
	return ret;
    ret = -160;
    if (!test_coverage (db_handle, RL2_SAMPLE_UINT8, TILE_1024, &ret))
	return ret;
    ret = -180;
    if (!test_coverage (db_handle, RL2_SAMPLE_INT16, TILE_256, &ret))
	return ret;
    ret = -200;
    if (!test_coverage (db_handle, RL2_SAMPLE_INT16, TILE_1024, &ret))
	return ret;
    ret = -220;
    if (!test_coverage (db_handle, RL2_SAMPLE_UINT16, TILE_256, &ret))
	return ret;
    ret = -240;
    if (!test_coverage (db_handle, RL2_SAMPLE_UINT16, TILE_1024, &ret))
	return ret;
    ret = -260;
    if (!test_coverage (db_handle, RL2_SAMPLE_INT32, TILE_256, &ret))
	return ret;
    ret = -280;
    if (!test_coverage (db_handle, RL2_SAMPLE_INT32, TILE_1024, &ret))
	return ret;
    ret = -300;
    if (!test_coverage (db_handle, RL2_SAMPLE_UINT32, TILE_256, &ret))
	return ret;
    ret = -320;
    if (!test_coverage (db_handle, RL2_SAMPLE_UINT32, TILE_1024, &ret))
	return ret;
    ret = -340;
    if (!test_coverage (db_handle, RL2_SAMPLE_FLOAT, TILE_256, &ret))
	return ret;
    ret = -360;
    if (!test_coverage (db_handle, RL2_SAMPLE_FLOAT, TILE_1024, &ret))
	return ret;
    ret = -380;
    if (!test_coverage (db_handle, RL2_SAMPLE_DOUBLE, TILE_256, &ret))
	return ret;
    ret = -400;
    if (!test_coverage (db_handle, RL2_SAMPLE_DOUBLE, TILE_1024, &ret))
	return ret;

/* closing the DB */
    sqlite3_close (db_handle);
    spatialite_cleanup_ex (cache);
    rl2_cleanup_private (priv_data);
    spatialite_shutdown ();
    if (old_SPATIALITE_SECURITY_ENV)
      {
#ifdef _WIN32
	  char *env = sqlite3_mprintf ("SPATIALITE_SECURITY=%s",
				       old_SPATIALITE_SECURITY_ENV);
	  putenv (env);
	  sqlite3_free (env);
#else /* not WIN32 */
	  setenv ("SPATIALITE_SECURITY", old_SPATIALITE_SECURITY_ENV, 1);
#endif
      }
    else
      {
#ifdef _WIN32
	  putenv ("SPATIALITE_SECURITY=");
#else /* not WIN32 */
	  unsetenv ("SPATIALITE_SECURITY");
#endif
      }
    return result;
}