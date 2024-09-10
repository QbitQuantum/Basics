//=======================================================================
//function : EdgePassKey
//purpose  : 
//=======================================================================
void GEOMAlgo_GlueDetector::EdgePassKey(const TopoDS_Edge& aE, 
					GEOMAlgo_PassKeyShape& aPK)
{
  TopAbs_Orientation aOr;
  TopoDS_Shape aVR;
  TopoDS_Iterator aIt;
  TopTools_ListOfShape aLV;
  //
  aIt.Initialize(aE);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aV=aIt.Value();
    aOr=aV.Orientation();
    if (aOr==TopAbs_FORWARD || aOr==TopAbs_REVERSED) {
      if (myOrigins.IsBound(aV)) {
	aVR=myOrigins.Find(aV);
      }
      else {
	aVR=aV;
      }
      aLV.Append(aVR);
    }
  }
  //
  aPK.SetShapes(aLV);
}