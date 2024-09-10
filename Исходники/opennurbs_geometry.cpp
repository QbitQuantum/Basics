ON_BOOL32 ON_Geometry::Translate( const ON_3dVector& delta )
{
  if ( delta.IsZero() )
    return true;
  ON_Xform tr;
  tr.Translation( delta );
  return Transform( tr );
}