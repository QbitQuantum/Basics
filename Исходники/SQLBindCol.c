SQLRETURN CLBindCol( SQLHSTMT statement_handle,
		   SQLUSMALLINT column_number,
           SQLSMALLINT target_type,
		   SQLPOINTER target_value,
           SQLLEN buffer_length,
	   	   SQLLEN *strlen_or_ind )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
    CLBCOL *bcol;
    int b_len;
    SQLRETURN ret;

	if ( cl_statement -> not_from_select )
	{
		return  SQLBINDCOL( cl_statement -> cl_connection,
			cl_statement -> driver_stmt,
			column_number,
			target_type,
			target_value,
			buffer_length,
			strlen_or_ind );
	}

    /*
     * check in the list of bound columns for a entry
     */

    bcol = cl_statement -> bound_columns;

    while ( bcol )
    {
        if ( bcol -> column_number == column_number )
            break;

        bcol = bcol -> next;
    }

    if ( !bcol )
    {
        /*
         * do we want to bind anything
         */

        bcol = malloc( sizeof( CLBCOL ));
        if ( !bcol )
        {
            cl_statement -> cl_connection -> dh.__post_internal_error( &cl_statement -> dm_statement -> error,
                    ERROR_HY001, NULL,
                    cl_statement -> dm_statement -> connection -> 
                        environment -> requested_version );

            return SQL_ERROR;
        }

        memset( bcol, 0, sizeof( CLBCOL ));
        bcol -> column_number = column_number;

        /*
         * insert into to list
         */

        if ( cl_statement -> bound_columns )
        {
            CLBCOL *ptr, *prev;

            ptr = cl_statement -> bound_columns;
            prev = NULL;

            while( ptr && ptr -> column_number < column_number )
            {
                prev = ptr;
                ptr = ptr -> next;
            }

            if ( prev )
            {
                bcol -> next = ptr;
                prev -> next = bcol;
            }
            else
            {
                bcol -> next = cl_statement -> bound_columns;
                cl_statement -> bound_columns = bcol;
            }
        }
        else
        {
            bcol -> next = NULL;
            cl_statement -> bound_columns = bcol;
        }
    }

    /*
     * setup bound info
     */

    /*
     * find length
     */

    b_len = get_bound_length( target_type, buffer_length );

    if ( bcol -> local_buffer )
    {
        free( bcol -> local_buffer );
    }
    bcol -> local_buffer = NULL;

    if ( target_value && b_len > 0 )
    {
        bcol -> local_buffer = malloc( b_len );
        if ( !bcol -> local_buffer )
        {
            cl_statement -> cl_connection -> dh.__post_internal_error( &cl_statement -> dm_statement -> error,
                    ERROR_HY001, NULL,
                    cl_statement -> dm_statement -> connection -> 
                        environment -> requested_version );

            return SQL_ERROR;
        }
    }

    bcol -> bound_buffer = target_value;
    bcol -> bound_length = b_len;
    bcol -> bound_type = target_type;

    if ( strlen_or_ind )
    {
        bcol -> bound_ind = strlen_or_ind;
    }
    else
    {
        bcol -> bound_ind = NULL;
    }

    /*
     * call the driver to bind a column, but not bookmarks
     */

    if ( column_number > 0 )
    {
        ret = SQLBINDCOL( cl_statement -> cl_connection,
               cl_statement -> driver_stmt,
               column_number,
               target_type,
               bcol -> local_buffer,
               bcol -> bound_length,
               &bcol -> len_ind );
    }
    else
    {
        ret = SQL_SUCCESS;
    }

    /*
     * are we unbinding ?
     */

    if ( !target_value && !strlen_or_ind )
    {
        CLBCOL *ptr, *prev;
        /*
         * remove from the list
         */

        ptr = cl_statement -> bound_columns;
        prev = NULL;

        while( ptr && ptr != bcol )
        {
            prev = ptr;
            ptr = ptr -> next;
        }

        if ( prev )
        {
            prev -> next = bcol -> next;
        }
        else
        {
            cl_statement -> bound_columns = bcol -> next;
        }

        free( bcol );
    }

    return ret;
}