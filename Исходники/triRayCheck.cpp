bool intersect_triangle(Point3F orig, Point3F dir,
                   Point3F vert0, Point3F vert1, Point3F vert2,
                   F32& t, F32& u, F32& v)
{
   Point3F edge1, edge2, tvec, pvec, qvec;
   F32 det,inv_det;

   /* find vectors for two edges sharing vert0 */
   edge1.x = vert1.x - vert0.x;
   edge1.y = vert1.y - vert0.y;
   edge1.z = vert1.z - vert0.z;
   edge2.x = vert2.x - vert0.x;
   edge2.y = vert2.y - vert0.y;
   edge2.z = vert2.z - vert0.z;

   /* begin calculating determinant - also used to calculate U parameter */
   //CROSS(pvec, dir, edge2);
   mCross(dir, edge2, &pvec);

   /* if determinant is near zero, ray lies in plane of triangle */
   //det = DOT(edge1, pvec);
   det = mDot(edge1, pvec);

#ifdef TEST_CULL           /* define TEST_CULL if culling is desired */
   if (det < EPSILON)
      return 0;

   /* calculate distance from vert0 to ray origin */
   SUB(tvec, orig, vert0);

   /* calculate U parameter and test bounds */
   *u = DOT(tvec, pvec);
   if (*u < 0.0 || *u > det)
      return 0;

   /* prepare to test V parameter */
   CROSS(qvec, tvec, edge1);

    /* calculate V parameter and test bounds */
   *v = DOT(dir, qvec);
   if (*v < 0.0 || *u + *v > det)
      return 0;

   /* calculate t, scale parameters, ray intersects triangle */
   *t = DOT(edge2, qvec);
   inv_det = 1.0 / det;
   *t *= inv_det;
   *u *= inv_det;
   *v *= inv_det;
#else                    /* the non-culling branch */
   if (det > -EPSILON && det < EPSILON)
     return false;
   inv_det = 1.0 / det;

   /* calculate distance from vert0 to ray origin */
   //SUB(tvec, orig, vert0);
   tvec.x = orig.x - vert0.x;
   tvec.y = orig.y - vert0.y;
   tvec.z = orig.z - vert0.z;

   /* calculate U parameter and test bounds */
//   *u = DOT(tvec, pvec) * inv_det;
   u = mDot(tvec, pvec) * inv_det;
   if (u < 0.0 || u > 1.0)
     return false;

   /* prepare to test V parameter */
   //CROSS(qvec, tvec, edge1);
   mCross(tvec, edge1, &qvec);

   /* calculate V parameter and test bounds */
//   *v = DOT(dir, qvec) * inv_det;
   v = mDot(dir, qvec) * inv_det;
   if (v < 0.0 || u + v > 1.0)
     return false;

   /* calculate t, ray intersects triangle */
//   *t = DOT(edge2, qvec) * inv_det;
   t = mDot(edge2, qvec) * inv_det;
#endif
   return true;
}