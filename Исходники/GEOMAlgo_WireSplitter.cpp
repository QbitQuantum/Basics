//=======================================================================
// function:  Coord2dVf
// purpose:
//=======================================================================
 gp_Pnt2d Coord2dVf (const TopoDS_Edge& aE,
		     const TopoDS_Face& aF)
{
  Standard_Real aCoord=99.;
  gp_Pnt2d aP2D1(aCoord, aCoord);
  TopoDS_Iterator aIt;
  //
  aIt.Initialize(aE);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aVx=aIt.Value();
    if (aVx.Orientation()==TopAbs_FORWARD) {
      const TopoDS_Vertex& aVxx=TopoDS::Vertex(aVx);
      aP2D1=Coord2d(aVxx, aE, aF);
      return aP2D1;
    }
  }
  return aP2D1;
}