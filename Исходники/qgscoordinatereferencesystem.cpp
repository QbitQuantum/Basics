bool QgsCoordinateReferenceSystem::createFromOgcWmsCrs( QString theCrs )
{
  if ( loadFromDb( QgsApplication::srsDbFilePath(), "lower(auth_name||':'||auth_id)", theCrs.toLower() ) )
    return true;

  if ( theCrs.compare( "CRS:84", Qt::CaseInsensitive ) == 0 )
  {
    createFromSrsId( GEOCRS_ID );
    return true;
  }

  return false;
}