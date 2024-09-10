bool ON_Plane::Translate(
      const ON_3dVector& delta
      )
{
  ON_Xform tr;
  tr.Translation( delta );
  return Transform( tr );
}