CFX_FloatPoint CFFL_FormFiller::FFLtoPWL(const CFX_FloatPoint& point) {
  CFX_Matrix mt;
  mt.SetReverse(GetCurMatrix());

  CFX_FloatPoint pt = point;
  mt.Transform(pt.x, pt.y);

  return pt;
}