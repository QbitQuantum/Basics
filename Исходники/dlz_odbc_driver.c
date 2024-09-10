/*%
 * create an instance of the driver.  Remember, only 1 copy of the driver's
 * code is ever loaded, the driver has to remember which context it's
 * operating in.  This is done via use of the dbdata argument which is
 * passed into all query functions.
 */
static isc_result_t
odbc_create(const char *dlzname, unsigned int argc, char *argv[],
	    void *driverarg, void **dbdata)
{
	isc_result_t result;
	odbc_instance_t *odbc_inst = NULL;
	dbinstance_t *db = NULL;
	SQLRETURN sqlRes;

#ifdef ISC_PLATFORM_USETHREADS
	/* if multi-threaded, we need a few extra variables. */
	int dbcount;
	int i;
	char *endp;

#endif /* ISC_PLATFORM_USETHREADS */

	UNUSED(dlzname);
	UNUSED(driverarg);

#ifdef ISC_PLATFORM_USETHREADS
	/* if debugging, let user know we are multithreaded. */
	isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
		      DNS_LOGMODULE_DLZ, ISC_LOG_DEBUG(1),
		      "Odbc driver running multithreaded");
#else /* ISC_PLATFORM_USETHREADS */
	/* if debugging, let user know we are single threaded. */
	isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
		      DNS_LOGMODULE_DLZ, ISC_LOG_DEBUG(1),
		      "Odbc driver running single threaded");
#endif /* ISC_PLATFORM_USETHREADS */

	/* verify we have at least 5 arg's passed to the driver */
	if (argc < 5) {
		isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
			      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
			      "Odbc driver requires at least "
			      "4 command line args.");
		return (ISC_R_FAILURE);
	}

	/* no more than 8 arg's should be passed to the driver */
	if (argc > 8) {
		isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
			      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
			      "Odbc driver cannot accept more than "
			      "7 command line args.");
		return (ISC_R_FAILURE);
	}

	/* multithreaded build can have multiple DB connections */
#ifdef ISC_PLATFORM_USETHREADS

	/* check how many db connections we should create */
	dbcount = strtol(argv[1], &endp, 10);
	if (*endp != '\0' || dbcount < 0) {
		isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
			      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
			      "Odbc driver database connection count "
			      "must be positive.");
		return (ISC_R_FAILURE);
	}

#endif /* ISC_PLATFORM_USETHREADS */

	/* allocate memory for odbc instance */
	odbc_inst = isc_mem_get(ns_g_mctx, sizeof(odbc_instance_t));
	if (odbc_inst == NULL)
		return (ISC_R_NOMEMORY);
	memset(odbc_inst, 0, sizeof(odbc_instance_t));

	/* parse connection string and get paramters. */

	/* get odbc database dsn - required */
	odbc_inst->dsn = (SQLCHAR *) getParameterValue(argv[2],
						       "dsn=");
	if (odbc_inst->dsn == NULL) {
		isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
			      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
			      "odbc driver requires a dns parameter.");
		result = ISC_R_FAILURE;
		goto cleanup;
	}
	/* get odbc database username */
	/* if no username was passed, set odbc_inst.user = NULL; */
	odbc_inst->user = (SQLCHAR *) getParameterValue(argv[2],
							"user="******"pass="******"Odbc driver unable to allocate memory");
			result = ISC_R_NOMEMORY;
			goto cleanup;
		}
		/*set ODBC version = 3 */
		sqlRes = SQLSetEnvAttr(odbc_inst->sql_env,
				       SQL_ATTR_ODBC_VERSION,
				       (void *) SQL_OV_ODBC3, 0);
		if (!sqlOK(sqlRes)) {
			isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
				      DNS_LOGMODULE_DLZ, ISC_LOG_INFO,
				      "Unable to configure ODBC environment");
			result = ISC_R_NOMEMORY;
			goto cleanup;
		}
	}

#ifdef ISC_PLATFORM_USETHREADS

	/* allocate memory for database connection list */
	odbc_inst->db = isc_mem_get(ns_g_mctx, sizeof(db_list_t));
	if (odbc_inst->db == NULL) {
		result = ISC_R_NOMEMORY;
		goto cleanup;
	}


	/* initialize DB connection list */
	ISC_LIST_INIT(*odbc_inst->db);

	/* create the appropriate number of database instances (DBI) */
	/* append each new DBI to the end of the list */
	for (i=0; i < dbcount; i++) {

#endif /* ISC_PLATFORM_USETHREADS */

		/* how many queries were passed in from config file? */
		switch(argc) {
		case 5:
			result = build_sqldbinstance(ns_g_mctx, NULL, NULL,
						     NULL, argv[3], argv[4],
						     NULL, &db);
			break;
		case 6:
			result = build_sqldbinstance(ns_g_mctx, NULL, NULL,
						     argv[5], argv[3], argv[4],
						     NULL, &db);
			break;
		case 7:
			result = build_sqldbinstance(ns_g_mctx, argv[6], NULL,
						     argv[5], argv[3], argv[4],
						     NULL, &db);
			break;
		case 8:
			result = build_sqldbinstance(ns_g_mctx, argv[6],
						     argv[7], argv[5], argv[3],
						     argv[4], NULL, &db);
			break;
		default:
			/* not really needed, should shut up compiler. */
			result = ISC_R_FAILURE;
		}

		/* unsuccessful?, log err msg and cleanup. */
		if (result != ISC_R_SUCCESS) {
			isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
				      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
				      "Odbc driver could not create "
				      "database instance object.");
			goto cleanup;
		}

#ifdef ISC_PLATFORM_USETHREADS

		/* when multithreaded, build a list of DBI's */
		ISC_LINK_INIT(db, link);
		ISC_LIST_APPEND(*odbc_inst->db, db, link);

#endif

		result = odbc_connect(odbc_inst, (odbc_db_t **) &(db->dbconn));

		if (result != ISC_R_SUCCESS) {

#ifdef ISC_PLATFORM_USETHREADS

			/*
			 * if multi threaded, let user know which
			 * connection failed.  user could be
			 * attempting to create 10 db connections and
			 * for some reason the db backend only allows
			 * 9.
			 */
			isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
				      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
				      "Odbc driver failed to create database "
				      "connection number %u after 3 attempts",
				      i+1);
#else
			isc_log_write(dns_lctx, DNS_LOGCATEGORY_DATABASE,
				      DNS_LOGMODULE_DLZ, ISC_LOG_ERROR,
				      "Odbc driver failed to create database "
				      "connection after 3 attempts");
#endif
			goto cleanup;
		}

#ifdef ISC_PLATFORM_USETHREADS

		/* set DB = null for next loop through. */
		db = NULL;

	}	/* end for loop */

#else
	/* tell odbc_inst about the db connection we just created. */
	odbc_inst->db = db;

#endif

	/* set dbdata to the odbc_instance we created. */
	*dbdata = odbc_inst;

	/* hey, we got through all of that ok, return success. */
	return(ISC_R_SUCCESS);

 cleanup:

	destroy_odbc_instance(odbc_inst);

	return result;
}