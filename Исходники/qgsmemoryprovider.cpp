QgsMemoryProvider::QgsMemoryProvider( const QString& uri )
    : QgsVectorDataProvider( uri )
    , mSpatialIndex( nullptr )
{
  // Initialize the geometry with the uri to support old style uri's
  // (ie, just 'point', 'line', 'polygon')
  QUrl url = QUrl::fromEncoded( uri.toUtf8() );
  QString geometry;
  if ( url.hasQueryItem( "geometry" ) )
  {
    geometry = url.queryItemValue( "geometry" );
  }
  else
  {
    geometry = url.path();
  }

  geometry = geometry.toLower();
  if ( geometry == "point" )
    mWkbType = QGis::WKBPoint;
  else if ( geometry == "linestring" )
    mWkbType = QGis::WKBLineString;
  else if ( geometry == "polygon" )
    mWkbType = QGis::WKBPolygon;
  else if ( geometry == "multipoint" )
    mWkbType = QGis::WKBMultiPoint;
  else if ( geometry == "multilinestring" )
    mWkbType = QGis::WKBMultiLineString;
  else if ( geometry == "multipolygon" )
    mWkbType = QGis::WKBMultiPolygon;
  else
    mWkbType = QGis::WKBUnknown;

  if ( url.hasQueryItem( "crs" ) )
  {
    QString crsDef = url.queryItemValue( "crs" );
    mCrs.createFromString( crsDef );
  }

  mNextFeatureId = 1;

  mNativeTypes
  << QgsVectorDataProvider::NativeType( tr( "Whole number (integer)" ), "integer", QVariant::Int, 0, 10 )
  // Decimal number from OGR/Shapefile/dbf may come with length up to 32 and
  // precision up to length-2 = 30 (default, if width is not specified in dbf is length = 24 precision = 15)
  // We know that double (QVariant::Double) has only 15-16 significant numbers,
  // but setting that correct limits would disable the use of memory provider with
  // data from Shapefiles. In any case, the data are handled as doubles.
  // So the limits set here are not correct but enable use of data from Shapefiles.
  << QgsVectorDataProvider::NativeType( tr( "Decimal number (real)" ), "double", QVariant::Double, 0, 32, 0, 30 )
  << QgsVectorDataProvider::NativeType( tr( "Text (string)" ), "string", QVariant::String, 0, 255 )

  // date type
  << QgsVectorDataProvider::NativeType( tr( "Date" ), "date", QVariant::Date, -1, -1, -1, -1 )

  // integer types
  << QgsVectorDataProvider::NativeType( tr( "Whole number (smallint - 16bit)" ), "int2", QVariant::Int, -1, -1, 0, 0 )
  << QgsVectorDataProvider::NativeType( tr( "Whole number (integer - 32bit)" ), "int4", QVariant::Int, -1, -1, 0, 0 )
  << QgsVectorDataProvider::NativeType( tr( "Whole number (integer - 64bit)" ), "int8", QVariant::LongLong, -1, -1, 0, 0 )
  << QgsVectorDataProvider::NativeType( tr( "Decimal number (numeric)" ), "numeric", QVariant::Double, 1, 20, 0, 20 )
  << QgsVectorDataProvider::NativeType( tr( "Decimal number (decimal)" ), "decimal", QVariant::Double, 1, 20, 0, 20 )

  // floating point
  << QgsVectorDataProvider::NativeType( tr( "Decimal number (real)" ), "real", QVariant::Double, -1, -1, -1, -1 )
  << QgsVectorDataProvider::NativeType( tr( "Decimal number (double)" ), "double precision", QVariant::Double, -1, -1, -1, -1 )

  // string types
  << QgsVectorDataProvider::NativeType( tr( "Text, unlimited length (text)" ), "text", QVariant::String, -1, -1, -1, -1 )
  ;

  if ( url.hasQueryItem( "field" ) )
  {
    QList<QgsField> attributes;
    QRegExp reFieldDef( "\\:"
                        "(int|integer|real|double|string|date)" // type
                        "(?:\\((\\d+)"                // length
                        "(?:\\,(\\d+))?"                // precision
                        "\\))?"
                        "$", Qt::CaseInsensitive );
    QStringList fields = url.allQueryItemValues( "field" );
    for ( int i = 0; i < fields.size(); i++ )
    {
      QString name = fields.at( i );
      QVariant::Type type = QVariant::String;
      QString typeName( "string" );
      int length = 255;
      int precision = 0;

      int pos = reFieldDef.indexIn( name );
      if ( pos >= 0 )
      {
        name = name.mid( 0, pos );
        typeName = reFieldDef.cap( 1 ).toLower();
        if ( typeName == "int" || typeName == "integer" )
        {
          type = QVariant::Int;
          typeName = "integer";
          length = 10;
        }
        else if ( typeName == "real" || typeName == "double" )
        {
          type = QVariant::Double;
          typeName = "double";
          length = 20;
          precision = 5;
        }
        else if ( typeName == "date" )
        {
          type = QVariant::Date;
          typeName = "date";
          length = 10;
        }

        if ( reFieldDef.cap( 2 ) != "" )
        {
          length = reFieldDef.cap( 2 ).toInt();
        }
        if ( reFieldDef.cap( 3 ) != "" )
        {
          precision = reFieldDef.cap( 3 ).toInt();
        }
      }
      if ( name != "" )
        attributes.append( QgsField( name, type, typeName, length, precision ) );
    }
    addAttributes( attributes );
  }

  if ( url.hasQueryItem( "index" ) && url.queryItemValue( "index" ) == "yes" )
  {
    createSpatialIndex();
  }

}