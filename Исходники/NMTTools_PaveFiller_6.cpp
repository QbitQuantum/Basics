//=======================================================================
// function: IsExistingPaveBlock
// purpose:
//=======================================================================
Standard_Boolean NMTTools_PaveFiller::IsExistingPaveBlock(const BOPTools_PaveBlock& aPBNew,
                                                          const TopTools_ListOfShape& aLSE,
                                                          const Standard_Real aTolR3D)
{
  Standard_Boolean bFlag;
  Standard_Integer aNbSE, iC;
  Standard_Real aTolE, aTol;
  TopTools_ListIteratorOfListOfShape anIt;
  //
  bFlag=Standard_False;
  //
  aNbSE=aLSE.Extent();
  if (!aNbSE) {
    return bFlag;
  }
  //
  anIt.Initialize(aLSE);
  for (; anIt.More(); anIt.Next()) {
    const TopoDS_Edge& aE=TopoDS::Edge(anIt.Value());
    aTolE=BRep_Tool::Tolerance(aE);
    aTol=aTolR3D;
    if (aTolE>aTol) {
      aTol=aTolE;
    }
    iC=CheckIntermediatePoint(aPBNew, aE, aTol);
    if (!iC) {
      return !bFlag;
    }
  }
  return bFlag;
}