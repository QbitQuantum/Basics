//int __cdecl wmain(int argc, _In_reads_(argc) WCHAR **argv)
//int __cdecl wmain(int argc, WCHAR **argv)
int __cdecl wmain2(int argc, WCHAR **argv)
{
    SQLHENV     hEnv = NULL;
    SQLHDBC     hDbc = NULL;
    SQLHSTMT    hStmt = NULL;
    WCHAR*      pwszConnStr;
    WCHAR       wszInput[SQL_QUERY_SIZE];

    // Allocate an environment

    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) == SQL_ERROR)
    {
        fwprintf(stderr, L"Unable to allocate an environment handle\n");
        exit(-1);
    }

    // Register this as an application that expects 3.x behavior,
    // you must register something if you use AllocHandle

    TRYODBC(hEnv,
            SQL_HANDLE_ENV,
            SQLSetEnvAttr(hEnv,
                SQL_ATTR_ODBC_VERSION,
                (SQLPOINTER)SQL_OV_ODBC3,
                0));

    // Allocate a connection
    TRYODBC(hEnv,
            SQL_HANDLE_ENV,
            SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc));

    if (argc > 1)
    {
        pwszConnStr = *++argv;
    } 
    else
    {
        pwszConnStr = L"";
    }

    // Connect to the driver.  Use the connection string if supplied
    // on the input, otherwise let the driver manager prompt for input.

    TRYODBC(hDbc,
        SQL_HANDLE_DBC,
        SQLDriverConnect(hDbc,
                         GetDesktopWindow(),
                         pwszConnStr,
                         SQL_NTS,
                         NULL,
                         0,
                         NULL,
                         SQL_DRIVER_COMPLETE));

    fwprintf(stderr, L"Connected!\n");

    TRYODBC(hDbc,
            SQL_HANDLE_DBC,
            SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt));

    wprintf(L"Enter SQL commands, type (control)Z to exit\nSQL COMMAND>");

    // Loop to get input and execute queries

    while(_fgetts(wszInput, SQL_QUERY_SIZE-1, stdin))
    {
        RETCODE     RetCode;
        SQLSMALLINT sNumResults;

        // Execute the query

        if (!(*wszInput))
        {
            wprintf(L"SQL COMMAND>");
            continue;
        }
        RetCode = SQLExecDirect(hStmt,wszInput, SQL_NTS);

        switch(RetCode)
        {
        case SQL_SUCCESS_WITH_INFO:
            {
                HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
                // fall through
            }
        case SQL_SUCCESS:
            {
                // If this is a row-returning query, display
                // results
                TRYODBC(hStmt,
                        SQL_HANDLE_STMT,
                        SQLNumResultCols(hStmt,&sNumResults));

                if (sNumResults > 0)
                {
                    DisplayResults(hStmt,sNumResults);
                } 
                else
                {
                    SQLLEN cRowCount;

                    TRYODBC(hStmt,
                        SQL_HANDLE_STMT,
                        SQLRowCount(hStmt,&cRowCount));

                    if (cRowCount >= 0)
                    {
                        wprintf(L"%Id %s affected\n",
                                 cRowCount,
                                 cRowCount == 1 ? L"row" : L"rows");
                    }
                }
                break;
            }

        case SQL_ERROR:
            {
                HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
                break;
            }

        default:
            fwprintf(stderr, L"Unexpected return code %hd!\n", RetCode);

        }
        TRYODBC(hStmt,
                SQL_HANDLE_STMT,
                SQLFreeStmt(hStmt, SQL_CLOSE));

        wprintf(L"SQL COMMAND>");
    }

Exit:

    // Free ODBC handles and exit

    if (hStmt)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    if (hDbc)
    {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    }

    if (hEnv)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    }

    wprintf(L"\nDisconnected.");

    return 0;

}