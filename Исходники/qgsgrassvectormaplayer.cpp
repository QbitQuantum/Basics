void QgsGrassVectorMapLayer::load()
{
  clear();

  if ( !mMap )
  {
    return;
  }

  // Attributes are not loaded for topo layers in which case field == 0
  if ( mField == 0 )
  {
    return;
  }

  QgsDebugMsg( QString( "cidxFieldIndex() = %1 cidxFieldNumCats() = %2" ).arg( cidxFieldIndex() ).arg( cidxFieldNumCats() ) );

  mFieldInfo = Vect_get_field( mMap->map(), mField ); // should work also with field = 0

  if ( !mFieldInfo )
  {
    QgsDebugMsg( "No field info -> no attribute table" );
  }
  else
  {
    QgsDebugMsg( "Field info found -> open database" );

    QFileInfo di( mMap->grassObject().mapsetPath() + "/vector/" + mMap->grassObject().name() + "/dbln" );
    mLastLoaded = di.lastModified();

    QString error;
    dbDriver *databaseDriver = openDriver( error );

    if ( !databaseDriver || !error.isEmpty() )
    {
      QgsDebugMsg( error );
    }
    else
    {
      QgsDebugMsg( "Database opened -> open select cursor" );
      QgsGrass::lock(); // not sure if lock is necessary
      dbString dbstr;
      db_init_string( &dbstr );
      db_set_string( &dbstr, ( char * )"select * from " );
      db_append_string( &dbstr, mFieldInfo->table );

      QgsDebugMsg( QString( "SQL: %1" ).arg( db_get_string( &dbstr ) ) );
      dbCursor databaseCursor;
      if ( db_open_select_cursor( databaseDriver, &dbstr, &databaseCursor, DB_SCROLL ) != DB_OK )
      {
        db_close_database_shutdown_driver( databaseDriver );
        QgsGrass::warning( "Cannot select attributes from table '" + QString( mFieldInfo->table ) + "'" );
      }
      else
      {
#ifdef QGISDEBUG
        int nRecords = db_get_num_rows( &databaseCursor );
        QgsDebugMsg( QString( "Number of records: %1" ).arg( nRecords ) );
#endif

        dbTable  *databaseTable = db_get_cursor_table( &databaseCursor );
        int nColumns = db_get_table_number_of_columns( databaseTable );

        // Read columns' description
        for ( int i = 0; i < nColumns; i++ )
        {
          QPair<double, double> minMax( DBL_MAX, -DBL_MAX );

          dbColumn *column = db_get_table_column( databaseTable, i );

          int ctype = db_sqltype_to_Ctype( db_get_column_sqltype( column ) );
          QVariant::Type qtype = QVariant::String; //default to string
          QgsDebugMsg( QString( "column = %1 ctype = %2" ).arg( db_get_column_name( column ) ).arg( ctype ) );

          QString ctypeStr;
          switch ( ctype )
          {
            case DB_C_TYPE_INT:
              ctypeStr = QStringLiteral( "integer" );
              qtype = QVariant::Int;
              break;
            case DB_C_TYPE_DOUBLE:
              ctypeStr = QStringLiteral( "double" );
              qtype = QVariant::Double;
              break;
            case DB_C_TYPE_STRING:
              ctypeStr = QStringLiteral( "string" );
              qtype = QVariant::String;
              break;
            case DB_C_TYPE_DATETIME:
              ctypeStr = QStringLiteral( "datetime" );
              qtype = QVariant::String;
              break;
          }
          mTableFields.append( QgsField( db_get_column_name( column ), qtype, ctypeStr,
                                         db_get_column_length( column ), db_get_column_precision( column ) ) );
          mMinMax << minMax;
          if ( G_strcasecmp( db_get_column_name( column ), mFieldInfo->key ) == 0 )
          {
            mKeyColumn = i;
          }
        }

        if ( mKeyColumn < 0 )
        {
          mTableFields.clear();
          QgsGrass::warning( QObject::tr( "Key column '%1' not found in the table '%2'" ).arg( mFieldInfo->key, mFieldInfo->table ) );
        }
        else
        {
          mHasTable = true;
          // Read attributes to the memory
          for ( ;; )
          {
            int more;

            if ( db_fetch( &databaseCursor, DB_NEXT, &more ) != DB_OK )
            {
              QgsDebugMsg( "Cannot fetch DB record" );
              break;
            }
            if ( !more )
            {
              break; // no more records
            }

            // Check cat value
            dbColumn *column = db_get_table_column( databaseTable, mKeyColumn );
            dbValue *value = db_get_column_value( column );

            if ( db_test_value_isnull( value ) )
            {
              continue;
            }
            int cat = db_get_value_int( value );
            if ( cat < 0 )
            {
              continue;
            }

            QList<QVariant> values;
            for ( int i = 0; i < nColumns; i++ )
            {
              column = db_get_table_column( databaseTable, i );
              int sqltype = db_get_column_sqltype( column );
              int ctype = db_sqltype_to_Ctype( sqltype );
              value = db_get_column_value( column );
              db_convert_value_to_string( value, sqltype, &dbstr );

              QgsDebugMsgLevel( QString( "column = %1 value = %2" ).arg( db_get_column_name( column ), db_get_string( &dbstr ) ), 3 );

              QVariant variant;
              if ( !db_test_value_isnull( value ) )
              {
                int iv;
                double dv;
                //layer.mAttributes[layer.nAttributes].values[i] = strdup( db_get_string( &dbstr ) );
                switch ( ctype )
                {
                  case DB_C_TYPE_INT:
                    iv = db_get_value_int( value );
                    variant = QVariant( iv );
                    mMinMax[i].first = std::min( mMinMax[i].first, ( double )iv );
                    mMinMax[i].second = std::min( mMinMax[i].second, ( double )iv );
                    break;
                  case DB_C_TYPE_DOUBLE:
                    dv = db_get_value_double( value );
                    variant = QVariant( dv );
                    mMinMax[i].first = std::min( mMinMax[i].first, dv );
                    mMinMax[i].second = std::min( mMinMax[i].second, dv );
                    break;
                  case DB_C_TYPE_STRING:
                    // Store as byte array so that codec may be used later
                    variant = QVariant( QByteArray( db_get_value_string( value ) ) );
                    break;
                  case DB_C_TYPE_DATETIME:
                    variant = QVariant( QByteArray( db_get_string( &dbstr ) ) );
                    break;
                  default:
                    variant = QVariant( QByteArray( db_get_string( &dbstr ) ) );
                }
              }
              QgsDebugMsgLevel( QString( "column = %1 variant = %2" ).arg( db_get_column_name( column ), variant.toString() ), 3 );
              values << variant;
            }
            mAttributes.insert( cat, values );
          }
        }
        mValid = true;
        db_close_cursor( &databaseCursor );
        db_close_database_shutdown_driver( databaseDriver );
        db_free_string( &dbstr );

        QgsDebugMsg( QString( "mTableFields.size = %1" ).arg( mTableFields.size() ) );
        QgsDebugMsg( QString( "number of attributes = %1" ).arg( mAttributes.size() ) );
      }
      QgsGrass::unlock();
    }
  }

  // Add cat if no attribute fields exist (otherwise qgis crashes)
  if ( mTableFields.size() == 0 )
  {
    mKeyColumn = 0;
    mTableFields.append( QgsField( QStringLiteral( "cat" ), QVariant::Int, QStringLiteral( "integer" ) ) );
    QPair<double, double> minMax( 0, 0 );

    if ( cidxFieldIndex() >= 0 )
    {
      int ncats, cat, type, id;

      ncats = Vect_cidx_get_num_cats_by_index( mMap->map(), cidxFieldIndex() );

      if ( ncats > 0 )
      {
        Vect_cidx_get_cat_by_index( mMap->map(), cidxFieldIndex(), 0, &cat, &type, &id );
        minMax.first = cat;

        Vect_cidx_get_cat_by_index( mMap->map(), cidxFieldIndex(), ncats - 1, &cat, &type, &id );
        minMax.second = cat;
      }
    }
    mMinMax << minMax;
  }
  mFields = mTableFields;
  mAttributeFields = mTableFields;

  QgsDebugMsg( QString( "layer loaded mTableFields.size() = %1 mAttributes.size() = %2" ).arg( mTableFields.size() ).arg( mAttributes.size() ) );
  mValid = true;
}