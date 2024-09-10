//=======================================================================
//function : FindDelta
//purpose  : 
//=======================================================================
static Standard_Real FindDelta(TopTools_ListOfShape& LE,
			       const TopoDS_Face& F)
{
  Standard_Real dist, f, l;
  Standard_Real d = Precision::Infinite();
  TopTools_ListIteratorOfListOfShape itl;

  for ( itl.Initialize(LE); itl.More(); itl.Next()) {
    const TopoDS_Edge& E = TopoDS::Edge(itl.Value());
    Handle(Geom2d_Curve) C = BRep_Tool::CurveOnSurface(E,F,f,l);
    gp_Pnt2d p = C->Value(f);
    gp_Pnt2d pp = C->Value(l);
    Standard_Real d1 = p.Distance(pp);
    if (d1<d) { d=d1;}
  }
  dist = d ;
  return dist;
}