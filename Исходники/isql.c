/****************************
 * ExecuteSlash - meta commands
 ***************************/
static int
ExecuteSlash( SQLHDBC hDbc, char *szSQL, char cDelimiter, int bColumnNames, int bHTMLTable )
{
    SQLRETURN ret;

    szSQL ++;

    if ( memcmp( szSQL, "tables", 6 ) == 0 )
    {
        return display_tables( hDbc );
    }
    else if ( memcmp( szSQL, "columns", 7 ) == 0 )
    {
        return display_columns( hDbc, szSQL + 7 );
    }
    else if ( memcmp( szSQL, "ac", 2 ) == 0 )
    {
        if ( version3 )
        {
            ret = SQLSetConnectAttr( hDbc, SQL_ATTR_AUTOCOMMIT, 
                                     (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0 );

            if ( SQL_SUCCEEDED( ret ) )
            {
                ac_off = 0;
            }
        }
        else
        {
            ret = SQLSetConnectOption( hDbc, SQL_ATTR_AUTOCOMMIT, 
                                       SQL_AUTOCOMMIT_ON );

            if ( SQL_SUCCEEDED( ret ) )
            {
                ac_off = 0;
            }
        }

        if ( !bBatch )
        {
            printf( "AUTOCOMMIT ON (return status = %d)\n", ret );
        }

        if ( bVerbose && !SQL_SUCCEEDED( ret ))
        {
            DumpODBCLog( hEnv, hDbc, 0 );
        }
    }
    else if ( memcmp( szSQL, "noac", 4 ) == 0 )
    {
        if ( version3 )
        {
            ret = SQLSetConnectAttr( hDbc, SQL_ATTR_AUTOCOMMIT, 
                                     (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0 );

            if ( SQL_SUCCEEDED( ret ) )
            {
                ac_off = 1;
            }
        }
        else
        {
            ret = SQLSetConnectOption( hDbc, SQL_ATTR_AUTOCOMMIT, 
                                       SQL_AUTOCOMMIT_OFF );

            if ( SQL_SUCCEEDED( ret ) )
            {
                ac_off = 1;
            }
        }

        if ( !bBatch )
        {
            printf( "AUTOCOMMIT OFF (return status = %d)\n", ret );
        }

        if ( bVerbose && !SQL_SUCCEEDED( ret ))
        {
            DumpODBCLog( hEnv, hDbc, 0 );
        }
    }
    else if ( memcmp( szSQL, "commit", 6 ) == 0 )
    {
        if ( version3 )
        {
            ret = SQLEndTran( SQL_HANDLE_DBC, hDbc, SQL_COMMIT );
        }
        else
        {
            ret = SQLTransact( hEnv, hDbc, SQL_COMMIT );
        }

        if ( !bBatch )
        {
            printf( "COMMIT (return status = %d)\n", ret );
        }

        if ( bVerbose && !SQL_SUCCEEDED( ret ))
        {
            DumpODBCLog( hEnv, hDbc, 0 );
        }
    }
    else if ( memcmp( szSQL, "rollback", 8 ) == 0 )
    {
        if ( version3 )
        {
            ret = SQLEndTran( SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK );
        }
        else
        {
            ret = SQLTransact( hEnv, hDbc, SQL_ROLLBACK );
        }

        if ( !bBatch )
        {
            printf( "ROLLBACK (return status = %d)\n", ret );
        }

        if ( bVerbose && !SQL_SUCCEEDED( ret ))
        {
            DumpODBCLog( hEnv, hDbc, 0 );
        }
    }
    else if ( memcmp( szSQL, "quit", 4 ) == 0 )
    {
        return 0;
    }
    else
    {
        printf( "\nUnknown metacommand '%s'\n\n", szSQL );
    }

    return 1;
}