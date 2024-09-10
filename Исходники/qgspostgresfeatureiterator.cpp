bool QgsPostgresFeatureIterator::declareCursor( const QString& whereClause )
{
  mFetchGeometry = !( mRequest.flags() & QgsFeatureRequest::NoGeometry ) && !mSource->mGeometryColumn.isNull();

#if 0
  // TODO: check that all field indexes exist
  if ( !hasAllFields )
  {
    rewind();
    return false;
  }
#endif

  QString query( "SELECT " ), delim( "" );

  if ( mFetchGeometry )
  {
    QString geom = QgsPostgresConn::quotedIdentifier( mSource->mGeometryColumn );

    if ( mSource->mSpatialColType == sctGeography ||
         mSource->mSpatialColType == sctPcPatch )
      geom += "::geometry";

    if ( mSource->mForce2d )
    {
      geom = QString( "%1(%2)" )
             // Force_2D before 2.0
             .arg( mConn->majorVersion() < 2 ? "force_2d"
                   // ST_Force2D since 2.1.0
                   : mConn->majorVersion() > 2 || mConn->minorVersion() > 0 ? "st_force2d"
                   // ST_Force_2D in 2.0.x
                   : "st_force_2d",
                   geom );
    }

    if ( !mRequest.simplifyMethod().forceLocalOptimization() &&
         mRequest.simplifyMethod().methodType() != QgsSimplifyMethod::NoSimplification &&
         QGis::flatType( QGis::singleType( mSource->mRequestedGeomType != QGis::WKBUnknown
                                           ? mSource->mRequestedGeomType
                                           : mSource->mDetectedGeomType ) ) != QGis::WKBPoint )
    {
      geom = QString( "%1(%2,%3)" )
             .arg( mRequest.simplifyMethod().methodType() == QgsSimplifyMethod::OptimizeForRendering
                   ? ( mConn->majorVersion() < 2 ? "snaptogrid" : "st_snaptogrid" )
                       : ( mConn->majorVersion() < 2 ? "simplifypreservetopology" : "st_simplifypreservetopology" ),
                       geom )
                 .arg( mRequest.simplifyMethod().tolerance() * 0.8 ); //-> Default factor for the maximum displacement distance for simplification, similar as GeoServer does
    }

    geom = QString( "%1(%2,'%3')" )
           .arg( mConn->majorVersion() < 2 ? "asbinary" : "st_asbinary",
                 geom,
                 QgsPostgresProvider::endianString() );

    query += delim + geom;
    delim = ",";
  }

  switch ( mSource->mPrimaryKeyType )
{
    case pktOid:
      query += delim + "oid";
      delim = ",";
      break;

    case pktTid:
      query += delim + "ctid";
      delim = ",";
      break;

    case pktInt:
      query += delim + QgsPostgresConn::quotedIdentifier( mSource->mFields[ mSource->mPrimaryKeyAttrs[0] ].name() );
      delim = ",";
      break;

    case pktFidMap:
      Q_FOREACH ( int idx, mSource->mPrimaryKeyAttrs )
      {
        query += delim + mConn->fieldExpression( mSource->mFields[idx] );
        delim = ",";
      }
      break;

    case pktUnknown:
      QgsDebugMsg( "Cannot declare cursor without primary key." );
      return false;
      break;
  }

  bool subsetOfAttributes = mRequest.flags() & QgsFeatureRequest::SubsetOfAttributes;
  Q_FOREACH ( int idx, subsetOfAttributes ? mRequest.subsetOfAttributes() : mSource->mFields.allAttributesList() )
  {
    if ( mSource->mPrimaryKeyAttrs.contains( idx ) )
      continue;

    query += delim + mConn->fieldExpression( mSource->mFields[idx] );
  }

  query += " FROM " + mSource->mQuery;

  if ( !whereClause.isEmpty() )
    query += QString( " WHERE %1" ).arg( whereClause );

  if ( !mConn->openCursor( mCursorName, query ) )
  {

    // reloading the fields might help next time around
    // TODO how to cleanly force reload of fields?  P->loadFields();
    close();
    return false;
  }

  return true;
}