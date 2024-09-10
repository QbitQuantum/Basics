static SQLRETURN extract_sql_error_rec( EHEAD *head,
        SQLCHAR *sqlstate,
        SQLINTEGER rec_number,
        SQLINTEGER *native_error,
        SQLCHAR *message_text,
        SQLSMALLINT buffer_length,
        SQLSMALLINT *text_length )
{
    SQLRETURN ret;

    if ( sqlstate )
        strcpy((char*) sqlstate, "00000" );

    if ( rec_number <= head -> sql_diag_head.internal_count )
    {
        ERROR *ptr;
        SQLCHAR *as1 = NULL;

        ptr = head -> sql_diag_head.internal_list_head;
        while( rec_number > 1 )
        {
            ptr = ptr -> next;
            rec_number --;
        }

        as1 = (SQLCHAR*) unicode_to_ansi_alloc( ptr -> msg, SQL_NTS, __get_connection( head ));

        if ( sqlstate )
        {
            unicode_to_ansi_copy((char*) sqlstate, ptr -> sqlstate, SQL_NTS, __get_connection( head ));
        }
        if ( buffer_length < strlen((char*) as1 ) + 1 )
        {
            ret = SQL_SUCCESS_WITH_INFO;
        }
        else
        {
            ret = SQL_SUCCESS;
        }

        if ( message_text && as1 )
        {
            if ( ret == SQL_SUCCESS )
            {
                strcpy((char*) message_text, (char*) as1 );
            }
            else
            {
                memcpy( message_text, as1, buffer_length );
                message_text[ buffer_length - 1 ] = '\0';
            }
        }

        if ( text_length && as1 )
        {
            *text_length = strlen((char*) as1 );
        }

        if ( native_error )
        {
            *native_error = ptr -> native_error;
        }

        /*
         * map 3 to 2 if required
         */

        if ( SQL_SUCCEEDED( ret ) && sqlstate )
            __map_error_state( (char*) sqlstate, __get_version( head ));

        if ( as1 )
        {
            free( as1 );
        }
        return ret;
    }
    else if ( !__is_env( head ) && __get_connection( head ) -> state != STATE_C2 )
    {
        ERROR *ptr;
        SQLCHAR *as1 = NULL;
        SQLWCHAR *s1 = NULL, *s2 = NULL;

    	if ( rec_number <= head -> sql_diag_head.internal_count + 
            head -> sql_diag_head.error_count )
		{
        	rec_number -= head -> sql_diag_head.internal_count;
		}
		else
		{
        	rec_number -= ( head -> sql_diag_head.internal_count + head -> sql_diag_head.error_count );
		}

        s1 = malloc( sizeof( SQLWCHAR ) * ( 6 + 1 ));

        if ( buffer_length > 0 )
        {
            s2 = malloc( sizeof( SQLWCHAR ) * ( buffer_length + 1 ));
        }

        if ( __get_connection( head ) -> unicode_driver &&
            CHECK_SQLGETDIAGRECW( __get_connection( head )))
        {
            ret = SQLGETDIAGRECW( __get_connection( head ),
                    head -> handle_type,
                    __get_driver_handle( head ),
                    rec_number,
                    s1,
                    native_error,
                    s2,
                    buffer_length,
                    text_length );

            /*
             * map 3 to 2 if required
             */

            if ( SQL_SUCCEEDED( ret ) && sqlstate )
            {
                if ( sqlstate )
                {
                    unicode_to_ansi_copy((char*) sqlstate, s1, SQL_NTS, __get_connection( head ));
                    __map_error_state((char*) sqlstate, __get_version( head ));
                }
                if ( message_text )
                {
                    unicode_to_ansi_copy((char*) message_text, s2, SQL_NTS, __get_connection( head ));
                }
            }

        }
        else if ( !__get_connection( head ) -> unicode_driver &&
            CHECK_SQLGETDIAGREC( __get_connection( head )))
        {
            ret = SQLGETDIAGREC( __get_connection( head ),
                    head -> handle_type,
                    __get_driver_handle( head ),
                    rec_number,
                    sqlstate,
                    native_error,
                    message_text,
                    buffer_length,
                    text_length );

            /*
             * map 3 to 2 if required
             */

            if ( SQL_SUCCEEDED( ret ) && sqlstate )
                __map_error_state((char*) sqlstate, __get_version( head ));
        }
        else
        {
            SQLCHAR *as1 = NULL;

            ptr = head -> sql_diag_head.error_list_head;
            while( rec_number > 1 )
            {
                ptr = ptr -> next;
                rec_number --;
            }

            as1 = (SQLCHAR*) unicode_to_ansi_alloc( ptr -> msg, SQL_NTS, __get_connection( head ));

            if ( sqlstate )
            {
                unicode_to_ansi_copy((char*) sqlstate, ptr -> sqlstate, SQL_NTS, __get_connection( head ));
            }
            if ( as1 && buffer_length < strlen((char*) as1 ) + 1 )
            {
                ret = SQL_SUCCESS_WITH_INFO;
            }
            else
            {
                ret = SQL_SUCCESS;
            }

            if ( message_text && as1 )
            {
                if ( ret == SQL_SUCCESS )
                {
                    strcpy((char*) message_text,(char*) as1 );
                }
                else
                {
                    memcpy( message_text, as1, buffer_length );
                    message_text[ buffer_length - 1 ] = '\0';
                }
            }

            if ( text_length && as1 )
            {
                *text_length = strlen((char*) as1 );
            }

            if ( native_error )
            {
                *native_error = ptr -> native_error;
            }

            /*
             * map 3 to 2 if required
             */

            if ( SQL_SUCCEEDED( ret ) && sqlstate )
                __map_error_state((char*) sqlstate, __get_version( head ));

            if ( as1 )
            {
                free( as1 );
            }
        }

        if ( s1 )
            free( s1 );

        if ( s2 )
            free( s2 );

        return ret;
    }
    else 
    {
	    return SQL_NO_DATA;
    }
}