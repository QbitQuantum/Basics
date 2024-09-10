Point3F& m_mul( const Point3F &p, const TQuatF &q, Point3F *r )
{
   //rotate a point by a Quaternion
   QuatF a;
   QuatF i = q;
   QuatF v( p.x, p.y, p.z, 0.0f);
   i.inverse();   
   m_mul(i, v, &a );
   m_mul(a, q, &v );
   v.normalize();
   r->set(v.x, v.y, v.z);

   *r += q.p;
   return ( *r );
}