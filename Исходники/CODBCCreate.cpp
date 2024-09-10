bool CODBCCreate::createDsn()
{
	BOOL ret;
	QString fname = file_edit->text();

	// Make sure it ends with .dsn
	
	if ( fname.right( 4 ).lower().compare( ".dsn" ))
	{
		fname.append( ".dsn" );
	}

	if ( access( fname, F_OK ) == 0 )
	{
		int replace = QMessageBox::information( NULL, "Save File DSN", "Data source file exists. Overwrite?", QMessageBox::Yes, QMessageBox::No );
		if ( replace == QMessageBox::No )
		{
			inst_logPushMsg( __FILE__, __FILE__, __LINE__, LOG_CRITICAL, ODBC_ERROR_CREATE_DSN_FAILED, "" );
			return false;
		}
	}

	if ( unlink( fname ))
	{
		inst_logPushMsg( __FILE__, __FILE__, __LINE__, LOG_CRITICAL, ODBC_ERROR_CREATE_DSN_FAILED, "" );
		return false;
	}

	ret = SQLWriteFileDSN((const char*) fname,
			"ODBC",
			"DRIVER",
			(const char *)current_driver );

	if ( !ret )
	{
		return false;
	}

	if ( extra_keywords.length() > 0 )
	{
		int start = 0;
		int end = 0;
		int eq;
		QString str;

		while( start < extra_keywords.length() )
		{
			end = extra_keywords.find( '\n', start );

			if ( end == -1 )
			{
				end = extra_keywords.length();
			}

			str = extra_keywords.mid( start, end-start ) + ";";
			eq = str.find( '=', 0 );
			if ( eq > 0 )
			{
				ret = SQLWriteFileDSN((const char*) fname,
							"ODBC",
							(const char *) str.left( eq ),
							(const char *) str.right( str.length() - eq - 1 ));
				if ( !ret )
				{
					return false;
				}
			}
			start = end + 1;
		}
	}

	return true;
}