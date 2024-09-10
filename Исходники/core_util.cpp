bool core_sqlsrv_get_odbc_error( sqlsrv_context& ctx, int record_number, sqlsrv_error_auto_ptr& error, logging_severity severity 
                                 TSRMLS_DC )
{
    SQLHANDLE h = ctx.handle();
    SQLSMALLINT h_type = ctx.handle_type();

    if( h == NULL ) {
        return false;
    }

    zval* ssphp_z = NULL;
    int zr = SUCCESS;
    zval* temp = NULL;
    SQLRETURN r = SQL_SUCCESS;
    SQLSMALLINT wmessage_len = 0;
    SQLWCHAR wsqlstate[ SQL_SQLSTATE_BUFSIZE ];
    SQLWCHAR wnative_message[ SQL_MAX_MESSAGE_LENGTH + 1 ];
    SQLSRV_ENCODING enc = ctx.encoding();

    switch( h_type ) {

        case SQL_HANDLE_STMT:
            {
                sqlsrv_stmt* stmt = static_cast<sqlsrv_stmt*>( &ctx );
                if( stmt->current_results != NULL ) {

                    error = stmt->current_results->get_diag_rec( record_number );
                    // don't use the CHECK* macros here since it will trigger reentry into the error handling system
                    if( error == NULL ) {
                        return false;
                    }
                    break;
                }

                // convert the error into the encoding of the context
                if( enc == SQLSRV_ENCODING_DEFAULT ) {
                    enc = stmt->conn->encoding();
                }
            }


        default:

            error = new ( sqlsrv_malloc( sizeof( sqlsrv_error ))) sqlsrv_error();
            r = SQLGetDiagRecW( h_type, h, record_number, wsqlstate, &error->native_code, wnative_message,
                                SQL_MAX_MESSAGE_LENGTH + 1, &wmessage_len );
            // don't use the CHECK* macros here since it will trigger reentry into the error handling system
            if( !SQL_SUCCEEDED( r ) || r == SQL_NO_DATA ) {
                return false;
            }

            SQLINTEGER sqlstate_len = 0;
            convert_string_from_utf16(enc, wsqlstate, sizeof(wsqlstate), (char**)&error->sqlstate, sqlstate_len);

            SQLINTEGER message_len = 0;
            convert_string_from_utf16(enc, wnative_message, wmessage_len, (char**)&error->native_message, message_len);
            break;
    }


    // log the error first
    LOG( severity, "%1!s!: SQLSTATE = %2!s!", ctx.func(), error->sqlstate );
    LOG( severity, "%1!s!: error code = %2!d!", ctx.func(), error->native_code );
    LOG( severity, "%1!s!: message = %2!s!", ctx.func(), error->native_message );

    error->format = false;

    return true;
}