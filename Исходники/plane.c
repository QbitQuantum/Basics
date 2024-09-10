MLIB_INLINE
mlib::Plane<PLANE,P,V,L>::Plane(const P &p,  const V&v1, const V&v2)
    : _d(0)
{
   *this = Plane<PLANE,P,V,L>(p, cross(v1, v2));
}