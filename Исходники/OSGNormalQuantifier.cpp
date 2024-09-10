// ----------------------------------------------
// RayTriangle Intersection Function
// by RealTime Rendering:
// http://www.acm.org/jgt/papers/MollerTrumbore97/
// date: December 12th, 2000
// ----------------------------------------------
bool NormalQuantifier::rayTriangle ( const Vec3f & dir, 
                                     const Vec3f & vert0, 
                                     const Vec3f & vert1, 
                                     const Vec3f & vert2 ) const
{
  Vec3f edge1, edge2, tvec, pvec, qvec;
  float det,inv_det;
  float u,v;
  Vec3f orig(0,0,0);
 
  /* find vectors for two edges sharing vert0 */
  edge1 = vert1 - vert0;
  edge2 = vert2 - vert0;

  /* begin calculating determinant - also used to calculate U parameter */
  pvec = dir.cross(edge2);

  /* if determinant is near zero, ray lies in plane of triangle */
  det = edge1.dot(pvec);
 
  /* the non-culling branch */
  if (det > -EPSILON && det < EPSILON)
    return false;

  inv_det = 1.0f / det;

  /* calculate distance from vert0 to ray origin */
  tvec = orig - vert0;

  /* calculate U parameter and test bounds */
  u = tvec.dot(pvec) *inv_det;
 
  if (u < 0.0 || u > 1.0)
    return false;

  /* prepare to test V parameter */
  qvec = tvec.cross(edge1);

  /* calculate V parameter and test bounds */
  v = dir.dot(qvec) * inv_det;

  if (v < 0.0 || u + v > 1.0)
    return false;

  /* calculate t, ray intersects triangle */
  //t = edge2.dot(qvec) * inv_det;

  return true;
};