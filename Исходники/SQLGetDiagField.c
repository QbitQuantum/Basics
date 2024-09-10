static SQLRETURN extract_sql_error_field( EHEAD *head,
                SQLSMALLINT rec_number,
                SQLSMALLINT diag_identifier,
                SQLPOINTER diag_info_ptr,
                SQLSMALLINT buffer_length,
                SQLSMALLINT *string_length_ptr )
{
    ERROR *ptr;

    /*
     * check the header fields first
     */

    switch( diag_identifier )
    {
      case SQL_DIAG_CURSOR_ROW_COUNT:
      case SQL_DIAG_ROW_COUNT:
        {
            SQLLEN val;
            SQLRETURN ret;

            if ( head -> handle_type != SQL_HANDLE_STMT )
            {
                return SQL_ERROR;
            }
            else if ( head -> header_set )
            {
                switch( diag_identifier )
                {
                  case SQL_DIAG_CURSOR_ROW_COUNT:
                    if ( SQL_SUCCEEDED( head -> diag_cursor_row_count_ret ) && diag_info_ptr )
                    {
                        *((SQLLEN*)diag_info_ptr) = head -> diag_cursor_row_count;
                    }
                    return head -> diag_cursor_row_count_ret;

                  case SQL_DIAG_ROW_COUNT:
                    if ( SQL_SUCCEEDED( head -> diag_row_count_ret ) && diag_info_ptr )
                    {
                        *((SQLLEN*)diag_info_ptr) = head -> diag_row_count;
                    }
                    return head -> diag_row_count_ret;
                }
            }
            else if ( __get_connection( head ) -> unicode_driver &&
                CHECK_SQLGETDIAGFIELDW( __get_connection( head )))
            {
                ret = SQLGETDIAGFIELDW( __get_connection( head ),
                        SQL_HANDLE_STMT,
                        __get_driver_handle( head ),
                        0,
                        diag_identifier,
                        diag_info_ptr,
                        buffer_length,
                        string_length_ptr );

                return ret;
            }
            else if ( !__get_connection( head ) -> unicode_driver &&
                CHECK_SQLGETDIAGFIELD( __get_connection( head )))
            {
                ret = SQLGETDIAGFIELD( __get_connection( head ),
                        SQL_HANDLE_STMT,
                        __get_driver_handle( head ),
                        0,
                        diag_identifier,
                        diag_info_ptr,
                        buffer_length,
                        string_length_ptr );

                return ret;
            }
            else if ( CHECK_SQLROWCOUNT( __get_connection( head )))
            {
                ret = DEF_SQLROWCOUNT( __get_connection( head ),
                    __get_driver_handle( head ),
                    &val );

                if ( !SQL_SUCCEEDED( ret ))
                {
                    return ret;
                }
            }
            else
            {
                val = 0;
            }

            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &val, sizeof( val ));
            }
        }
        return SQL_SUCCESS;

      case SQL_DIAG_DYNAMIC_FUNCTION:
        {
            SQLRETURN ret;

            if ( head -> handle_type != SQL_HANDLE_STMT )
            {
                return SQL_ERROR;
            }
            else if ( head -> header_set )
            {
                if ( SQL_SUCCEEDED( head -> diag_dynamic_function_ret ) && diag_info_ptr )
                {
                    unicode_to_ansi_copy( diag_info_ptr, buffer_length, head -> diag_dynamic_function, buffer_length, __get_connection( head ));
                    if ( string_length_ptr )
                    {
                        *string_length_ptr = wide_strlen( head -> diag_dynamic_function );
                    }
                }
                return head -> diag_dynamic_function_ret;
            }
            else if ( __get_connection( head ) -> unicode_driver &&
                CHECK_SQLGETDIAGFIELDW( __get_connection( head )))
            {
                SQLWCHAR *s1 = NULL;

                if ( buffer_length > 0 )
                {
                    s1 = malloc( sizeof( SQLWCHAR ) * ( buffer_length + 1 ));
                }
                
                ret = SQLGETDIAGFIELDW( __get_connection( head ),
                        SQL_HANDLE_STMT,
                        __get_driver_handle( head ),
                        0,
                        diag_identifier,
                        s1 ? s1 : diag_info_ptr,
                        buffer_length,
                        string_length_ptr );

                if ( SQL_SUCCEEDED( ret ) && diag_info_ptr && s1 )
                {
                    unicode_to_ansi_copy( diag_info_ptr, buffer_length, s1, buffer_length, __get_connection( head ));
                }

                if ( s1 )
                {
                    free( s1 );
                }

                return ret;
            }
            else if ( !__get_connection( head ) -> unicode_driver &&
                CHECK_SQLGETDIAGFIELD( __get_connection( head )))
            {
                ret = SQLGETDIAGFIELD( __get_connection( head ),
                        SQL_HANDLE_STMT,
                        __get_driver_handle( head ),
                        0,
                        diag_identifier,
                        diag_info_ptr,
                        buffer_length,
                        string_length_ptr );

                return ret;
            }
            if ( diag_info_ptr )
            {
                strcpy( diag_info_ptr, "" );
            }
        }
        return SQL_SUCCESS;

      case SQL_DIAG_DYNAMIC_FUNCTION_CODE:
        {
            SQLINTEGER val;
            SQLRETURN ret;

            if ( head -> handle_type != SQL_HANDLE_STMT )
            {
                return SQL_ERROR;
            }
            else if ( head -> header_set )
            {
                if ( SQL_SUCCEEDED( head -> diag_dynamic_function_code_ret ) && diag_info_ptr )
                {
                    *((SQLINTEGER*)diag_info_ptr) = head -> diag_dynamic_function_code;
                }
                return head -> diag_dynamic_function_code_ret;
            }
            else if ( __get_connection( head ) -> unicode_driver &&
                CHECK_SQLGETDIAGFIELDW( __get_connection( head )))
            {
                ret = SQLGETDIAGFIELDW( __get_connection( head ),
                        SQL_HANDLE_STMT,
                        __get_driver_handle( head ),
                        0,
                        diag_identifier,
                        diag_info_ptr,
                        buffer_length,
                        string_length_ptr );

                return ret;
            }
            else if ( !__get_connection( head ) -> unicode_driver &&
                CHECK_SQLGETDIAGFIELD( __get_connection( head )))
            {
                ret = SQLGETDIAGFIELD( __get_connection( head ),
                        SQL_HANDLE_STMT,
                        __get_driver_handle( head ),
                        0,
                        diag_identifier,
                        diag_info_ptr,
                        buffer_length,
                        string_length_ptr );

                return ret;
            }
            else
            {
                val = SQL_DIAG_UNKNOWN_STATEMENT;
            }

            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &val, sizeof( val ));
            }
        }
        return SQL_SUCCESS;

      case SQL_DIAG_NUMBER:
        {
            SQLINTEGER val;
            
            val = head -> sql_diag_head.internal_count + 
                head -> sql_diag_head.error_count;

            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &val, sizeof( val ));
            }
        }
        return SQL_SUCCESS;

      case SQL_DIAG_RETURNCODE:
        {
            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &head -> return_code, 
                        sizeof( head -> return_code ));
            }
        }
        return SQL_SUCCESS;
    }

    /*
     * else check the records
     */

    if ( rec_number < 1 )
    {
        return SQL_ERROR;
    }

    if ( rec_number <= head -> sql_diag_head.internal_count )
    {
        /*
         * local errors
         */

        ptr = head -> sql_diag_head.internal_list_head;
        while( rec_number > 1 )
        {
            ptr = ptr -> next;
            rec_number --;
        }
		if ( !ptr ) 
		{
			return SQL_NO_DATA;
		}
    }
    else if ( !__is_env( head ) && __get_connection( head ) -> state != STATE_C2 )
    {
		rec_number -= head -> sql_diag_head.internal_count;

        if ( __get_connection( head ) -> unicode_driver &&
            CHECK_SQLGETDIAGFIELDW( __get_connection( head )))
        {
            SQLRETURN ret;
            SQLWCHAR *s1 = NULL;
			int char_buffer_len = sizeof( SQLWCHAR ) * buffer_length;

            if ( buffer_length > 0 )
            {
                s1 = malloc( char_buffer_len + sizeof( SQLWCHAR ));
            }

            ret = SQLGETDIAGFIELDW( __get_connection( head ),
                    head -> handle_type,
                    __get_driver_handle( head ),
                    rec_number,
                    diag_identifier,
                    s1 ? s1 : diag_info_ptr,
                    char_buffer_len,
                    string_length_ptr );

            if ( SQL_SUCCEEDED( ret ) && s1 && diag_info_ptr )
            {
                unicode_to_ansi_copy( diag_info_ptr, buffer_length, s1, SQL_NTS, __get_connection( head ));
            }

            if ( s1 )
            {
                free( s1 );
            }

			if ( string_length_ptr && *string_length_ptr > 0 ) 
			{
				*string_length_ptr /= sizeof( SQLWCHAR );
			}

            if ( SQL_SUCCEEDED( ret ) && diag_identifier == SQL_DIAG_SQLSTATE )
            {
                /*
                 * map 3 to 2 if required
                 */
                if ( diag_info_ptr )
                {
                    if ( diag_info_ptr )
                        __map_error_state( diag_info_ptr, __get_version( head ));
                }
            }

            return ret;
        }
		else if ( !__get_connection( head ) -> unicode_driver &&
            CHECK_SQLGETDIAGFIELD( __get_connection( head )))
        {
            SQLRETURN ret;

            ret = SQLGETDIAGFIELD( __get_connection( head ),
                    head -> handle_type,
                    __get_driver_handle( head ),
                    rec_number,
                    diag_identifier,
                    diag_info_ptr,
                    buffer_length,
                    string_length_ptr );

            if ( SQL_SUCCEEDED( ret ) && diag_identifier == SQL_DIAG_SQLSTATE )
            {
                /*
                 * map 3 to 2 if required
                 */
                if ( diag_info_ptr )
                {
                    if ( diag_info_ptr )
                        __map_error_state( diag_info_ptr, __get_version( head ));
                }
            }

            return ret;
        }
        else
        {
            ptr = head -> sql_diag_head.error_list_head;
            while( rec_number > 1 )
            {
                ptr = ptr -> next;
                rec_number --;
            }
			if ( !ptr ) 
			{
	    		return SQL_NO_DATA;
			}
        }
    }
    else 
    {
	    return SQL_NO_DATA;
    }

    /*
     * if we are here ptr should point to the local error
     * record
     */

    switch( diag_identifier )
    {
      case SQL_DIAG_CLASS_ORIGIN:
        {
            if ( SQL_SUCCEEDED( ptr -> diag_class_origin_ret ))
            {
                unicode_to_ansi_copy( diag_info_ptr, buffer_length, ptr -> diag_class_origin, buffer_length, __get_connection( head ));
                if ( string_length_ptr )
                {
                    *string_length_ptr = wide_strlen( ptr -> diag_class_origin );
                }
                return ptr -> diag_class_origin_ret;
            }
            else
            {
                return ptr -> diag_class_origin_ret;
            }
        }
        break;

      case SQL_DIAG_COLUMN_NUMBER:
        {
            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &ptr -> diag_column_number, sizeof( SQLINTEGER ));
            }
            return SQL_SUCCESS;
        }
        break;

      case SQL_DIAG_CONNECTION_NAME:
        {
            if ( SQL_SUCCEEDED( ptr -> diag_connection_name_ret ))
            {
                unicode_to_ansi_copy( diag_info_ptr, buffer_length, ptr -> diag_connection_name, buffer_length, __get_connection( head ));
                if ( string_length_ptr )
                {
                    *string_length_ptr = wide_strlen( ptr -> diag_connection_name );
                }
                return ptr -> diag_connection_name_ret;
            }
            else
            {
                return ptr -> diag_connection_name_ret;
            }
        }
        break;

      case SQL_DIAG_MESSAGE_TEXT:
        {
            char *str;
            int ret = SQL_SUCCESS;

            str = unicode_to_ansi_alloc( ptr -> msg, SQL_NTS, __get_connection( head ));

            if ( diag_info_ptr )
            {
                if ( buffer_length >= strlen( str ) + 1 )
                {
                    strcpy( diag_info_ptr, str );
                }
                else
                {
                    ret = SQL_SUCCESS_WITH_INFO;
                    memcpy( diag_info_ptr, str, buffer_length - 1 );
                    (( char * ) diag_info_ptr )[ buffer_length - 1 ] = '\0';
                }
            }
            if ( string_length_ptr )
            {
                *string_length_ptr = strlen( str );
            }

            if ( str )
            {
                free( str );
            }

            return ret;
        }
        break;

      case SQL_DIAG_NATIVE:
        {
            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &ptr -> native_error, sizeof( SQLINTEGER ));
            }
            return SQL_SUCCESS;
        }
        break;

      case SQL_DIAG_ROW_NUMBER:
        {
            if ( diag_info_ptr )
            {
                memcpy( diag_info_ptr, &ptr -> diag_row_number, sizeof( SQLLEN ));
            }
            return SQL_SUCCESS;
        }
        break;

      case SQL_DIAG_SERVER_NAME:
        {
            if ( SQL_SUCCEEDED( ptr -> diag_server_name_ret ))
            {
                unicode_to_ansi_copy( diag_info_ptr, buffer_length, ptr -> diag_server_name, buffer_length, __get_connection( head ));
                if ( string_length_ptr )
                {
                    *string_length_ptr = wide_strlen( ptr -> diag_server_name );
                }
                return ptr -> diag_server_name_ret;
            }
            else
            {
                return ptr -> diag_server_name_ret;
            }
        }
        break;

      case SQL_DIAG_SQLSTATE:
        {
            char *str;
            int ret = SQL_SUCCESS;

            str = unicode_to_ansi_alloc( ptr -> sqlstate, SQL_NTS, __get_connection( head ));

            if ( diag_info_ptr )
            {
                if ( buffer_length >= strlen( str ) + 1 )
                {
                    strcpy( diag_info_ptr, str );
                }
                else
                {
                    ret = SQL_SUCCESS_WITH_INFO;
                    memcpy( diag_info_ptr, str, buffer_length - 1 );
                    (( char * ) diag_info_ptr )[ buffer_length - 1 ] = '\0';
                }

                /*
                 * map 3 to 2 if required
                 */

                if ( diag_info_ptr )
                    __map_error_state( diag_info_ptr, __get_version( head ));
            }
            if ( string_length_ptr )
            {
                *string_length_ptr = strlen( str );
            }

            if ( str )
            {
                free( str );
            }

            return ret;
        }
        break;

      case SQL_DIAG_SUBCLASS_ORIGIN:
        {
            if ( SQL_SUCCEEDED( ptr -> diag_subclass_origin_ret ))
            {
                unicode_to_ansi_copy( diag_info_ptr, buffer_length, ptr -> diag_subclass_origin, buffer_length, __get_connection( head ));
                if ( string_length_ptr )
                {
                    *string_length_ptr = wide_strlen( ptr -> diag_subclass_origin );
                }
                return ptr -> diag_subclass_origin_ret;
            }
            else
            {
                return ptr -> diag_subclass_origin_ret;
            }
        }
        break;
    }

    return SQL_SUCCESS;
}