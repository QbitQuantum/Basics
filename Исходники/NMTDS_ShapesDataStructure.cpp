//===========================================================================
//function : Init
//purpose  : 
//===========================================================================
void NMTDS_ShapesDataStructure::Init()
{
  Standard_Integer i, j, aNbSx, aNbS, aShift, aNbRanges;
  Standard_Integer iFirst, iLast;
  NMTDS_ListOfIndexedDataMapOfShapeAncestorsSuccessors aLx;
  NMTDS_ListIteratorOfListOfIndexedDataMapOfShapeAncestorsSuccessors aLit;
  TopoDS_Iterator anIt;
  BooleanOperations_IndexedDataMapOfShapeAncestorsSuccessors aMSA;
  //
  anIt.Initialize(myCompositeShape);
  for (; anIt.More(); anIt.Next()) {
    const TopoDS_Shape& aSx=anIt.Value(); 
    BooleanOperations_IndexedDataMapOfShapeAncestorsSuccessors aMS;
    //
    if (!aMSA.Contains(aSx)) {
      FillMap(aSx, aMSA, aMS);
      aLx.Append(aMS);
    }
  }
  aNbS=aMSA.Extent(); 
  //
  // Fill myRanges
  i=aLx.Extent();
  myRanges.Resize(i);
  aLit.Initialize(aLx);
  for (i=1; aLit.More(); aLit.Next(), ++i) {
    const BooleanOperations_IndexedDataMapOfShapeAncestorsSuccessors& aMSx=aLit.Value();
    aNbSx=aMSx.Extent();
    if (i==1) {
      iFirst=1;
      iLast=aNbSx;
      myRanges(i).SetFirst(iFirst);
      myRanges(i).SetLast(iLast);
      continue;
    }
    iFirst=myRanges(i-1).Last()+1;
    iLast=iFirst+aNbSx-1;
    myRanges(i).SetFirst(iFirst);
    myRanges(i).SetLast(iLast);
  }
  //
  myNumberOfShapesOfTheObject=aNbS;
  myNumberOfShapesOfTheTool=0;
  myLength=2*aNbS;
  //
  // Allocate the whole Table
  myListOfShapeAndInterferences = (BooleanOperations_PShapeAndInterferences)
    Standard::Allocate(myLength*sizeof(BooleanOperations_ShapeAndInterferences));
  //
  // Fill the table
  
  aShift=0;
  for (j=1; j<=aNbS; ++j) {
    const TopoDS_Shape& aSx=aMSA.FindKey(j);
    const BooleanOperations_AncestorsSeqAndSuccessorsSeq& aASx=aMSA.FindFromIndex(j);
    InsertShapeAndAncestorsSuccessors(aSx, aASx, aShift);
  }
  // myShapeIndexMap
  myShapeIndexMap.Clear();
  //
  //modified by NIZNHY-PKV Mon Dec 12 09:01:53 2011f
  aNbRanges=myRanges.Extent();
  for (i=1; i<=aNbRanges; ++i){
    const NMTDS_IndexRange& aR=myRanges(i);
    iFirst=aR.First();
    iLast =aR.Last();
    for (j=iFirst; j<=iLast; ++j) { 
      const TopoDS_Shape& aS=Shape(j);
      myShapeIndexMap.Bind(aS, j);
    }
  }
  //modified by NIZNHY-PKV Mon Dec 12 09:02:00 2011t
  //
  // myRefEdges
  iLast=myNumberOfShapesOfTheObject+myNumberOfShapesOfTheTool;
  myRefEdges.Resize(iLast);

  for (i=1; i<=iLast; ++i) {
    const TopoDS_Shape& aS=Shape(i);
    myRefEdges(i)=0;
    if (aS.ShapeType()==TopAbs_EDGE) {
      myNbEdges++;
      myRefEdges(i)=myNbEdges;
    }
  }
}