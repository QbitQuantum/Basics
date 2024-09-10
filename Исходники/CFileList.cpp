void CFileList::Edit()
{
	// odbc.ini INFO
	QString				qsDataSourceName		= "";
	QString				qsDataSourceDescription		= "";
	QString				qsDataSourceDriver		= "";
	// odbcinst.ini INFO
	QString				qsDriverFile			= "";
	QString				qsSetupFile				= "";
	QString				qsError					= "";

	CPropertiesFrame		*pProperties;
	HODBCINSTPROPERTY	hFirstProperty	= NULL;
	HODBCINSTPROPERTY	hCurProperty	= NULL;
#ifdef QT_V4LAYOUT
	Q3ListViewItem		*pListViewItem;
#else
	QListViewItem		*pListViewItem;
#endif

	char				szEntryNames[4096];
	char				szProperty[INI_MAX_PROPERTY_NAME+1];
	char				szValue[INI_MAX_PROPERTY_VALUE+1];
	
	DWORD				nErrorCode;
	char				szErrorMsg[101];
	char				szINI[FILENAME_MAX+1];
	int					nElement;	

    char dir[ 256 ];
    char szDriver[ 256 ];
    QString qsFileName;

	// HAS THE USER SELECTED SOMETHING
    pListViewItem = currentItem();
	if ( pListViewItem )
	{
		qsFileName		= pListViewItem->text( 0 );

        /*
		qsDataSourceDescription	= pListViewItem->text( 1 );
		qsDataSourceDriver		= pListViewItem->text( 2 );
        */
	}
	else
	{
		QMessageBox::information( this, "ODBC Config",  "Please select a Data Source from the list first" );
		return;
	}

    sprintf( dir, "%s/%s", cwd.ascii(), qsFileName.ascii());
    szDriver[ 0 ] = '\0';
    if ( !SQLReadFileDSN( dir, "ODBC", "DRIVER", szDriver, sizeof( szDriver ), NULL ) ||
            strlen( szDriver ) < 1 )
    {
        char szDsn[ 256 ];

        szDsn[ 0 ] = '\0';
        if ( SQLReadFileDSN( dir, "ODBC", "DSN", szDsn, sizeof( szDsn ), NULL ) &&
                strlen( szDsn ) >= 1 )
        {
            SQLSetConfigMode( ODBC_BOTH_DSN );
			SQLGetPrivateProfileString( szDsn, "Driver", "", szDriver, sizeof( szDriver ), "odbc.ini" );

            if ( strlen( szDriver ) < 1 )
            {
                QMessageBox::information( this, "ODBC Config",  "Unable to extract driver from FILE DSN" );
                return;
            }
        }
        else
        {
            QMessageBox::information( this, "ODBC Config",  "Unable to extract driver from FILE DSN" );
            return;
        }
    }

    //
    // can we call SQLDriverConnect
    //

	// GET PROPERTY LIST FROM DRIVER
	if ( ODBCINSTConstructProperties( szDriver, &hFirstProperty ) != ODBCINST_SUCCESS )
	{
		qsError.sprintf( "Could not construct a property list for (%s)", szDriver );
		QMessageBox::information( this, "ODBC Config",  qsError );

        int i = 1;
		while ( SQLInstallerError( i ++, &nErrorCode, szErrorMsg, 100, NULL ) == SQL_SUCCESS )
			QMessageBox::information( this, "ODBC Config",  szErrorMsg );

		return;
	}

	ODBCINSTSetProperty( hFirstProperty, "Name", (char*)qsFileName.ascii());

    for ( hCurProperty = hFirstProperty->pNext; hCurProperty != NULL; hCurProperty = hCurProperty->pNext )
    {
        char szAttr[ 256 ];

        szAttr[ 0 ] = '\0';
        if ( SQLReadFileDSN( dir, "ODBC", hCurProperty->szName, szAttr, sizeof( szAttr ), NULL ))
        {
		    ODBCINSTSetProperty( hFirstProperty, hCurProperty->szName, szAttr );
        }
    }

	// ALLOW USER TO EDIT
	pProperties = new CPropertiesFrame( this, "Properties", hFirstProperty );
	pProperties->setCaption( "Data Source Properties (edit)" );
	if ( pProperties->exec() )
	{
        int ret;

        ret = SQLWriteFileDSN( dir, "ODBC", NULL, NULL );
        if ( !ret )
        {
            qsError.sprintf( "Could not write to (%s)", dir );
            QMessageBox::information( this, "ODBC Config",  qsError );

            int i = 1;
            while ( SQLInstallerError( i++, &nErrorCode, szErrorMsg, 100, NULL ) == SQL_SUCCESS )
                QMessageBox::information( this, "ODBC Config",  szErrorMsg );

            return;
        }

        for ( hCurProperty = hFirstProperty->pNext; hCurProperty != NULL; hCurProperty = hCurProperty->pNext )
        {
            if ( !SQLWriteFileDSN( dir, "ODBC", hCurProperty->szName, hCurProperty->szValue ))
            {
                qsError.sprintf( "Could not write to file dsn (%s)", dir );
                QMessageBox::information( this, "ODBC Config",  qsError );

                int i = 1;
                while ( SQLInstallerError( i ++, &nErrorCode, szErrorMsg, 100, NULL ) == SQL_SUCCESS )
                    QMessageBox::information( this, "ODBC Config",  szErrorMsg );

                return;
            }
        }
	}
	delete pProperties;
	ODBCINSTDestructProperties( &hFirstProperty );

	// RELOAD (slow but safe)
	Load();
}