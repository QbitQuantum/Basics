Datum
cdb_set_oid(PG_FUNCTION_ARGS)
{
	int32 maxoid = PG_GETARG_INT32(0);
	char *tempFileName = tempnam( NULL, "TMPCP" );

/*	elog(NOTICE, "tempFileName = %s", tempFileName ); */

	StringInfoData buffer;
	initStringInfo( &buffer );

	appendStringInfo( &buffer, "%u\t0\n\\.\n", maxoid );

	FILE *fptr = fopen(tempFileName, "w");
	if ( strlen(buffer.data) != fwrite( buffer.data, 1, strlen(buffer.data), fptr) )
	{
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				errmsg("SPI_execute failed in in temp file write in cdb_set_oid" )));

	}

	fclose(fptr);
	pfree(buffer.data);
	buffer.data = NULL;

	if ( SPI_OK_CONNECT != SPI_connect() )
	{
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				errmsg("SPI_connect failed in cdb_set_oid" )));
	}

	if ( SPI_OK_UTILITY != SPI_execute( "CREATE TEMPORARY TABLE pgdump_oid (dummy integer) WITH OIDS", false, 0 ) )
	{
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				errmsg("SPI_execute failed in cdb_set_oid" )));
	}

	
	initStringInfo( &buffer );

	appendStringInfo( &buffer, "COPY pgdump_oid WITH OIDS FROM '%s'", tempFileName );
		
	if ( SPI_OK_UTILITY != SPI_execute( buffer.data, false, 0 ) )
	{
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				errmsg("SPI_execute failed in copy command in cdb_set_oid" )));
	}

	remove( tempFileName );

	pfree(buffer.data);

	if ( SPI_OK_UTILITY != SPI_execute( "DROP TABLE pgdump_oid", false, 0 ) )
	{
		ereport(ERROR,
				(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
				errmsg("SPI_execute failed in cdb_set_oid" )));
	}

	SPI_finish();

	PG_RETURN_BOOL(true);
}