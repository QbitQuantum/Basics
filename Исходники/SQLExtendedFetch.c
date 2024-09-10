SQLRETURN fetch_row( CLHSTMT cl_statement, int row_number, int offset )
{
    SQLSMALLINT ret;

    /*
     * is the row in the cache ?
     */

    if ( row_number < cl_statement -> rowset_count )
    {
        CLBCOL *cbuf;

        /*
         * read the file buffer
         */

        if ( fseek( cl_statement -> rowset_file,
                    cl_statement -> buffer_length * row_number,
                    SEEK_SET ))
        {
            cl_statement -> cl_connection -> dh.__post_internal_error( &cl_statement -> dm_statement -> error,
                ERROR_S1000, 
                "General error: fseek fails",
                cl_statement -> dm_statement -> connection -> 
                    environment -> requested_version );
            return SQL_ERROR;
        }

        if ( fread( cl_statement -> rowset_buffer,
                cl_statement -> buffer_length, 
                1, 
                cl_statement -> rowset_file ) != 1 )
        {
            cl_statement -> cl_connection -> dh.__post_internal_error( &cl_statement -> dm_statement -> error,
                ERROR_S1000, 
                "General error: Unable to read from file buffer",
                cl_statement -> dm_statement -> connection -> 
                    environment -> requested_version );
            return SQL_ERROR;
        }

        /*
         * extract the data
         *
         * status ptr
         */

        memcpy( &ret, cl_statement -> rowset_buffer, 
                sizeof( SQLUSMALLINT ));

        /*
         * columninfo
         */

        cbuf = cl_statement -> bound_columns;

        while ( cbuf )
        {
            char *buffer = NULL;
            char *ind_ptr = NULL;

            /*
             * copy from the file buffer
             */

            memcpy( cbuf -> local_buffer,
                    cl_statement -> rowset_buffer + 
                    cbuf -> rs_buffer_offset,
                    cbuf -> bound_length );

            memcpy( &cbuf -> len_ind,
                    cl_statement -> rowset_buffer +
                    cbuf -> rs_ind_offset,
                    sizeof( cbuf -> len_ind ));

            if ( offset >= 0 )
            {
                /*
                 * copy to the application buffer
                 */

                if ( cl_statement -> row_bind_type )
                {
                    if ( cbuf -> bound_buffer )
                    {
                        buffer = ((char*)cbuf -> bound_buffer) +
                            cl_statement -> row_bind_type * offset;
                    }
                    if ( cbuf -> bound_ind )
                    {
                        ind_ptr = ( char * ) cbuf -> bound_ind;
                        ind_ptr += cl_statement -> row_bind_type * offset;
                    }
                }
                else
                {
                    if ( cbuf -> bound_buffer )
                    {
                        buffer = ((char*)cbuf -> bound_buffer) +
                            cbuf -> bound_length * offset;
                    }
                    if ( cbuf -> bound_ind )
                    {
                        ind_ptr = ( char * ) cbuf -> bound_ind;
                        ind_ptr += offset * sizeof( SQLULEN );
                    }
                }

                if ( buffer && cbuf -> len_ind >= 0 )
                {
                    if ( cbuf -> bound_type == SQL_C_CHAR )
                    {
                        strcpy( buffer,
                                cbuf -> local_buffer );
                    }
                    else
                    {
                        memcpy( buffer,
                                cbuf -> local_buffer,
                                cbuf -> bound_length );
                    }
                }

                if ( ind_ptr )
                {
                    memcpy( ind_ptr,
                            &cbuf -> len_ind,
                            sizeof( cbuf -> len_ind ));
                }
            }

            cbuf = cbuf -> next;
        }
        return SQL_SUCCESS;
    }
    else
    {
        if ( cl_statement -> rowset_complete )
        {
            return SQL_NO_DATA;
        }

        ret = SQLFETCH( cl_statement -> cl_connection,
                        cl_statement -> driver_stmt );

        if ( ret == SQL_NO_DATA )
        {
            /*
             * at the end
             */
            cl_statement -> rowset_complete = 1;
            cl_statement -> rowset_position = CL_AFTER_END;
        }
        else
        {
            CLBCOL *cbuf;

            /*
             * insert into the cache
             */

            /*
             * status ptr
             */

            memcpy( cl_statement -> rowset_buffer, 
                    &ret, sizeof( SQLUSMALLINT ));

            /*
             * columninfo
             */

            cbuf = cl_statement -> bound_columns;

            while ( cbuf )
            {
                char *buffer = NULL;
                char *ind_ptr = NULL;

                /*
                 * copy to the file buffer
                 */

                memcpy( cl_statement -> rowset_buffer + 
                        cbuf -> rs_buffer_offset,
                        cbuf -> local_buffer,
                        cbuf -> bound_length );

                memcpy( cl_statement -> rowset_buffer +
                        cbuf -> rs_ind_offset,
                        &cbuf -> len_ind,
                        sizeof( cbuf -> len_ind ));

                if ( offset >= 0 )
                {
                    /*
                     * copy to the application buffer
                     */

                    if ( cl_statement -> row_bind_type )
                    {
                        if ( cbuf -> bound_buffer )
                        {
                            buffer = ((char*)cbuf -> bound_buffer) +
                                cl_statement -> row_bind_type * offset;
                        }
                        if ( cbuf -> bound_ind )
                        {
                            ind_ptr = ( char * ) cbuf -> bound_ind;
                            ind_ptr += cl_statement -> row_bind_type * offset;
                        }
                    }
                    else
                    {
                        if ( cbuf -> bound_buffer )
                        {
                            buffer = ((char*)cbuf -> bound_buffer) +
                                cbuf -> bound_length * offset;
                        }
                        if ( cbuf -> bound_ind )
                        {
                            ind_ptr = ( char * ) cbuf -> bound_ind;
                            ind_ptr += offset * sizeof( SQLULEN );
                        }
                    }

                    /*
                     * Not quite sure if the check is valid, I think I can see where
                     * I got it from, but not sure if its correct
                     * 
                    if ( buffer && cbuf -> bound_ind && *cbuf -> bound_ind >= 0 )
                    */
                    if ( buffer && cbuf -> bound_ind )
                    {
                        if ( cbuf -> bound_type == SQL_C_CHAR )
                        {
                            strcpy( buffer,
                                    cbuf -> local_buffer );
                        }
                        else
                        {
                            memcpy( buffer,
                                    cbuf -> local_buffer,
                                    cbuf -> bound_length );
                        }
                    }

                    if ( ind_ptr )
                    {
                        memcpy( ind_ptr,
                                &cbuf -> len_ind,
                                sizeof( cbuf -> len_ind ));
                    }
                }

                cbuf = cbuf -> next;
            }

            /*
             * write the file buffer
             */

            if ( fseek( cl_statement -> rowset_file,
                        cl_statement -> buffer_length * row_number,
                        SEEK_SET ))
            {
                cl_statement -> cl_connection -> dh.__post_internal_error( &cl_statement -> dm_statement -> error,
                    ERROR_S1000, 
                    "General error: fseek fails",
                    cl_statement -> dm_statement -> connection -> 
                        environment -> requested_version );
                return SQL_ERROR;
            }

            if ( fwrite( cl_statement -> rowset_buffer,
                    cl_statement -> buffer_length, 
                    1, 
                    cl_statement -> rowset_file ) != 1 )
            {
                cl_statement -> cl_connection -> dh.__post_internal_error( &cl_statement -> dm_statement -> error,
                    ERROR_S1000, 
                    "General error: Unable to write to file buffer",
                    cl_statement -> dm_statement -> connection -> 
                        environment -> requested_version );
                return SQL_ERROR;
            }
            cl_statement -> rowset_count ++;
        }

        return ret;
    }
}