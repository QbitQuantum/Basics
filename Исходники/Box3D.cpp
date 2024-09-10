bool Box3D::intersects(const Triangle3D& t) const
{
  Triangle3D tloc;
  toLocal(t.a,tloc.a);
  toLocal(t.b,tloc.b);
  toLocal(t.c,tloc.c);
  AABB3D bbloc;
  bbloc.bmin.setZero();
  bbloc.bmax=dims;
  return tloc.intersects(bbloc);
}