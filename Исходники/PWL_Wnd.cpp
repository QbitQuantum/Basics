CFX_FloatPoint CPWL_Wnd::ParentToChild(const CFX_FloatPoint& point) const {
  CFX_Matrix mt = GetChildMatrix();
  if (mt.IsIdentity())
    return point;

  mt.SetReverse(mt);
  CFX_FloatPoint pt = point;
  mt.Transform(pt.x, pt.y);
  return pt;
}