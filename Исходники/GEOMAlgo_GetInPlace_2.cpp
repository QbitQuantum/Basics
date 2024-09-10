//=======================================================================
//function : CheckGProps
//purpose  :
//=======================================================================
void GEOMAlgo_GetInPlace::CheckGProps(const TopoDS_Shape& aS1)
{
  Standard_Boolean bOnlyClosed;
  Standard_Integer iDim, aNbS2;
  Standard_Real aMass1, aMass2, aD2, aTolCG2, dM;
  TopAbs_ShapeEnum  aType1;
  gp_Pnt aCG1, aCG2;
  TopoDS_Iterator aIt;
  TopoDS_Compound aC2;
  BRep_Builder aBB;
  TopTools_ListIteratorOfListOfShape aItLS;
  //
  myErrorStatus=0;
  //
  aType1=aS1.ShapeType();
  if (aType1==TopAbs_COMPOUND) {
    aIt.Initialize(aS1);
    for(; aIt.More(); aIt.Next()) {
      const TopoDS_Shape& aS1x=aIt.Value();
      CheckGProps(aS1x);
      if (!myFound) {
	return;
      }
    }
  }
  //
  iDim=Dimension(aType1);
  //
  if (!myImages.IsBound(aS1)) {
    // it should not be.
    return;
  }
  const TopTools_ListOfShape& aLS2=myImages.Find(aS1);
  aNbS2=aLS2.Extent();
  if (!aNbS2) {
    // it should not be.
    return;
  }
  //
  aBB.MakeCompound(aC2);
  aItLS.Initialize(aLS2);
  for (; aItLS.More(); aItLS.Next()) {
    const TopoDS_Shape& aS2x=aItLS.Value();
    aBB.Add(aC2, aS2x);
  }
  //-------------------------
  GProp_GProps aG1, aG2;
  //
  aTolCG2=myTolCG*myTolCG;
  bOnlyClosed=Standard_False;
  //
  if (iDim==0) {
    PointProperties(aS1, aG1);
    PointProperties(aC2, aG2);
  }
  else if (iDim==1) {
    BRepGProp::LinearProperties(aS1, aG1);
    BRepGProp::LinearProperties(aC2, aG2);
  }
  else if (iDim==2) {
    BRepGProp::SurfaceProperties(aS1, aG1);
    BRepGProp::SurfaceProperties(aC2, aG2);
  }
  else if (iDim==3) {
    BRepGProp::VolumeProperties(aS1, aG1, bOnlyClosed);
    BRepGProp::VolumeProperties(aC2, aG2, bOnlyClosed);
  }
  //
  aMass1=aG1.Mass();
  aMass2=aG2.Mass();
  aCG1=aG1.CentreOfMass();
  aCG2=aG2.CentreOfMass();
  //
  dM=fabs(aMass1-aMass2);
  if (aMass1 > myTolMass) {
    dM=dM/aMass1;
  }
  //
  aD2=aCG1.SquareDistance(aCG2);
  //
  if ((dM > myTolMass) || (aD2 > aTolCG2)) {
    myFound=Standard_False;
    return;
  }
  myFound=Standard_True;
}