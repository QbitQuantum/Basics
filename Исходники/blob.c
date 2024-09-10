int odbcdr_blob_convertBlobsToByteArray(odbcdr_context_def *context, odbcdr_cursor_def *cursor, int num_rows)
{
    odbcdr_blob_col_list_def* columnList = cursor->defined_blobs;
    int rdbi_status = RDBI_GENERIC_ERROR;

    if (num_rows < 1 || columnList == NULL)
        goto the_exit;

    for (long i = 0;  i < columnList->size;  i++ )
    {
        long                 j;
        odbcdr_blob_def     **sqlserverBlob;
        odbcdr_blobNI_def   **sqlserverBlobNI;
        pByteArray_def      *visionBlob;
		pByteArray_def      *l_visionBlob;   
        odbcdr_blob_col_def  *column;

        column = col_list_getColumnByIndex_blob_S( columnList, i );
        if ( column == NULL || column->blob_list.size < num_rows )
            goto the_exit;

        sqlserverBlob = (odbcdr_blob_def **)ut_da_get( &column->blob_list, 0L );
        sqlserverBlobNI = (odbcdr_blobNI_def **)ut_da_get( &column->blobNI_list, 0L );
        visionBlob = column->address;
        l_visionBlob = column->l_address;

        if ( sqlserverBlob == NULL || sqlserverBlobNI == NULL || visionBlob == NULL ) goto the_exit;

        // Process each blob in the dataset. The blob are bound.
        // In case a large blob is hit (data truncation), the blobs are unbound and 
        // the current blob is fetched again as a blob.
        // After the entire batch is processed the blobs are bound again.
        int  unbound = false; 
        int wantedDim = -1;

        for ( j = 0;  j < num_rows;  j++ )
        {
            debug2( "converting blob column pos '%d', row %d",
                    column->position, j );

            IByteArray_Release(visionBlob[j]);
            visionBlob[j] = NULL;
            l_visionBlob[j] = NULL;

            // Check the status of this blob.
            int blobValid = blob_checkFetchStatusRow_S( cursor, i, j );

            // Unbind if not already unbound.
            if ( !blobValid && !unbound)
            {
                ODBCDR_ODBC_ERR( SQLBindCol( cursor->hStmt,
	                        (SQLUSMALLINT) column->position,
	                        (SQLSMALLINT) SQL_C_BINARY,
                            (SQLPOINTER) (char*)NULL,
                            (SQLINTEGER) 0,
	                        (SQLLEN *) NULL),
                    SQL_HANDLE_STMT, cursor->hStmt,
                    "SQLBindCol", "unbind" );  

                debug0("UNBOUND!\n");
                unbound = true;
            }

            if ( unbound )
            {
                // Advance 
		        ODBCDR_ODBC_ERR( SQLSetPos(	cursor->hStmt,
									        (SQLUSMALLINT) j+1, // Row # is 1 based
									        SQL_POSITION,
									        SQL_LOCK_NO_CHANGE),
								         SQL_HANDLE_STMT,cursor->hStmt,
						                 "SQLSetPos", "set position");
            }

		    /* Remember the last blob fetched in order to be released when the cursor is freed*/
            ODBCDR_RDBI_ERR( get_blobSqlServer( context, 
                                                      cursor,
                                                      column->position,
                                                      i,
                                                      j,
                                                      blobValid,
                                                      &visionBlob[j],
												      &l_visionBlob[j] ));
        }

        // Rebind back if the case.            
        if (unbound)
        {
            int offset = i * ODBCDR_MAX_ARRAY_SIZE;
            ODBCDR_ODBC_ERR( SQLBindCol( cursor->hStmt,
			            (SQLUSMALLINT) column->position,
			            (SQLSMALLINT) SQL_C_BINARY,
                        (SQLPOINTER) (char *)&cursor->odbcdr_blob[offset * ODBCDR_UBLOB_CHUNK_SIZE],
                        (SQLINTEGER) ODBCDR_UBLOB_CHUNK_SIZE,
			            (SQLLEN *) (char *)&cursor->odbcdr_blobNI[offset]),
	            SQL_HANDLE_STMT, cursor->hStmt,
	            "SQLBindCol", "rebind" );   
        }   
    }
	
    rdbi_status = RDBI_SUCCESS;

  the_exit:
    debug_return( NULL, rdbi_status );
}