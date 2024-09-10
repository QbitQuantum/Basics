//=======================================================================
//function : CorrectWires
//purpose  :
//=======================================================================
  Standard_Boolean GEOMAlgo_Tools::CorrectWires(const TopoDS_Shape& aShape)
{
  Standard_Boolean bRet;
  TopoDS_Iterator aItF;
  TopExp_Explorer aExp;
  TopTools_MapOfShape aMF;
  GeomAdaptor_Surface aGAS;
  GeomAbs_SurfaceType aTS;
  TopLoc_Location aLoc;
  //
  bRet=Standard_False;
  //
  aExp.Init(aShape, TopAbs_FACE);
  for (; aExp.More(); aExp.Next()) {
    const TopoDS_Face& aF=*((TopoDS_Face*)&aExp.Current());
    if (aMF.Add(aF)) {
      const Handle(Geom_Surface)& aS=BRep_Tool::Surface(aF, aLoc);
      aGAS.Load(aS);
      aTS=aGAS.GetType();
      if (aTS==GeomAbs_Cylinder || aTS==GeomAbs_Plane) {
	aItF.Initialize(aF);
	for (; aItF.More(); aItF.Next()) {
	  const TopoDS_Wire& aW=*((TopoDS_Wire*)&aItF.Value());
	  if (CorrectWire(aW, aF)) {
	   bRet=Standard_True;
	  }
	}
      }
    }
  }
  return bRet;
}