bool QgsSpatialFilter::evaluate( const QgsFeature& f ) const
{
  if ( !mGeom )
  {
    return true;
  }

  QgsGeometry* geom = ( new QgsFeature( f ) )->geometry();
  switch ( mSpatialType )
  {
    case BBOX:
      return geom->intersects( mGeom->boundingBox() );
      break;
    case CONTAINS:
      return geom->contains( mGeom );
      break;
    case CROSSES:
      return geom->crosses( mGeom );
      break;
    case DISJOINT:
      return geom->disjoint( mGeom );
      break;
    case EQUALS:
      return geom->equals( mGeom );
      break;
    case INTERSECTS:
      return geom->intersects( mGeom );
      break;
    case OVERLAPS:
      return geom->overlaps( mGeom );
      break;
    case TOUCHES:
      return geom->touches( mGeom );
      break;
    case WITHIN:
      return geom->within( mGeom );
      break;
    case UNKNOWN:
    default:
      break;
  }
  return false;
}