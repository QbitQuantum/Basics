int
main(int argc, char *argv[])
{
    LOGINREC *login;
    SQLHENV hEnv = 0;
    SQLHDBC hDbc = 0;
    SQLRETURN erc;
    const char *sql;

    setlocale(LC_ALL, "");

    memset(&options, 0, sizeof(options));
    options.headers = stderr;
    login = get_login(argc, argv, &options); /* get command-line parameters and call dblogin() */
    assert(login != NULL);

    /*
     * Override stdin, stdout, and stderr, as required
     */
    if (options.input_filename) {
        if (freopen(options.input_filename, "r", stdin) == NULL) {
            fprintf(stderr, "%s: unable to open %s: %s\n", options.appname, options.input_filename, strerror(errno));
            exit(1);
        }
    }

    if (options.output_filename) {
        if (freopen(options.output_filename, "w", stdout) == NULL) {
            fprintf(stderr, "%s: unable to open %s: %s\n", options.appname, options.output_filename, strerror(errno));
            exit(1);
        }
    }

    if (options.error_filename) {
        if (freopen(options.error_filename, "w", stderr) == NULL) {
            fprintf(stderr, "%s: unable to open %s: %s\n", options.appname, options.error_filename, strerror(errno));
            exit(1);
        }
    }

    if (options.fverbose) {
        options.verbose = stderr;
    } else {
        static const char null_device[] = "/dev/null";
        options.verbose = fopen(null_device, "w");
        if (options.verbose == NULL) {
            fprintf(stderr, "%s:%d unable to open %s for verbose operation: %s\n",
                    options.appname, __LINE__, null_device, strerror(errno));
            exit(1);
        }
    }

    fprintf(options.verbose, "%s:%d: Verbose operation enabled\n", options.appname, __LINE__);

    /*
     * Connect to the server
     */
    if ((erc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv)) != SQL_SUCCESS) {
        odbc_herror(SQL_HANDLE_ENV, hEnv, erc, "SQLAllocHandle", "failed to allocate an environment");
        exit(EXIT_FAILURE);
    }
    assert(hEnv);

    if ((erc = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)options.odbc_version, SQL_IS_UINTEGER)) != SQL_SUCCESS) {
        odbc_herror(SQL_HANDLE_DBC, hDbc, erc, "SQLSetEnvAttr", "failed to set SQL_OV_ODBC3");
        exit(EXIT_FAILURE);
    }

    if ((erc = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc)) != SQL_SUCCESS) {
        odbc_herror(SQL_HANDLE_DBC, hDbc, erc, "SQLAllocHandle", "failed to allocate a connection");
        exit(EXIT_FAILURE);
    }
    assert(hDbc);

    if ((erc = SQLConnect(hDbc, 	(SQLCHAR *) options.servername, SQL_NTS,
                          (SQLCHAR *) login->username, SQL_NTS,
                          (SQLCHAR *) login->password, SQL_NTS)) != SQL_SUCCESS) {
        odbc_herror(SQL_HANDLE_DBC, hDbc, erc, "SQLConnect", "failed");
        exit(EXIT_FAILURE);
    }

#if 0
    /* Switch to the specified database, if any */
    if (options.database)
        dbuse(dbproc, options.database);
#endif

    /*
     * Read the queries and write the results
     */
    while ((sql = next_query()) != NULL ) {
        SQLHSTMT hStmt;

        if ((erc = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt)) != SQL_SUCCESS) {
            odbc_perror(hStmt, erc, "SQLAllocHandle", "failed to allocate a statement handle");
            exit(EXIT_FAILURE);
        }

        /* "Prepare" the query and send it to the server */
        if ((erc = SQLPrepare(hStmt, (SQLCHAR *) sql, SQL_NTS)) != SQL_SUCCESS) {
            odbc_perror(hStmt, erc, "SQLPrepare", "failed");
            exit(EXIT_FAILURE);
        }

        if((erc = SQLExecute(hStmt)) != SQL_SUCCESS) {
            switch(erc) {
            case SQL_NEED_DATA:
                goto FreeStatement;
            case SQL_SUCCESS_WITH_INFO:
                if (0 != print_error_message(SQL_HANDLE_STMT, hStmt)) {
                    fprintf(stderr, "SQLExecute: continuing...\n");
                }
                break;
            default:
                odbc_perror(hStmt, erc, "SQLExecute", "failed");
                exit(EXIT_FAILURE);
            }
        }

        /* Write the output */
        print_results(hStmt);

FreeStatement:
        if ((erc = SQLFreeHandle(SQL_HANDLE_STMT, hStmt)) != SQL_SUCCESS) {
            odbc_perror(hStmt, erc, "SQLFreeHandle", "failed");
            exit(EXIT_FAILURE);
        }
    }

    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}