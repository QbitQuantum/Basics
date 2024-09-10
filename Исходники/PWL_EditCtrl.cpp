FX_BOOL CPWL_EditCtrl::IsWndHorV() {
  CFX_Matrix mt = GetWindowMatrix();
  CFX_FloatPoint point1(0, 1);
  CFX_FloatPoint point2(1, 1);

  mt.Transform(point1.x, point1.y);
  mt.Transform(point2.x, point2.y);

  return point2.y == point1.y;
}