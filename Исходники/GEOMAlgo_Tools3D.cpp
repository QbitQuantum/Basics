//=======================================================================
// function: CopyFace
// purpose: 
//=======================================================================
  void GEOMAlgo_Tools3D::CopyFace (const TopoDS_Face& theF1,
                                  TopoDS_Face& theF2)
{
  Standard_Real aTol;
  TopLoc_Location aLoc;
  TopAbs_Orientation aOr;
  TopoDS_Iterator aIt;
  BRep_Builder aBB;
  //
  Handle(Geom_Surface) aSurface=BRep_Tool::Surface(theF1, aLoc);
  aTol=BRep_Tool::Tolerance(theF1);
  aOr=theF1.Orientation();
  //
  aBB.MakeFace (theF2, aSurface, aLoc, aTol);
  theF2.Orientation(aOr);
  //
  aIt.Initialize(theF1);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aW=aIt.Value();
    aBB.Add(theF2, aW);
  }
}