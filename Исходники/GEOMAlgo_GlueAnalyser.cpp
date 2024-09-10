//=======================================================================
//function : DetectVertices
//purpose  :
//=======================================================================
  void GEOMAlgo_GlueAnalyser::DetectVertices()
{
  myErrorStatus=0;
  //
  Standard_Integer j, i, aNbV, aIndex, aNbVSD;
  TColStd_ListIteratorOfListOfInteger aIt;
  Handle(Bnd_HArray1OfBox) aHAB;
  Bnd_BoundSortBox aBSB;
  TopoDS_Shape aSTmp, aVF;
  TopoDS_Vertex aVnew;
  TopTools_IndexedMapOfShape aMV, aMVProcessed;
  TopTools_ListIteratorOfListOfShape aItS;
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape aItIm;
  GEOMAlgo_IndexedDataMapOfIntegerShape aMIS;
  GEOMAlgo_IndexedDataMapOfShapeBox aMSB;
  //
  TopExp::MapShapes(myShape, TopAbs_VERTEX, aMV);
  aNbV=aMV.Extent();
  if (!aNbV) {
    myErrorStatus=2; // no vertices in source shape
    return;
  }
  //
  aHAB=new Bnd_HArray1OfBox(1, aNbV);
  //
  for (i=1; i<=aNbV; ++i) {
    const TopoDS_Shape& aV=aMV(i);
    Bnd_Box aBox;
    //
    aBox.SetGap(myTol);
    BRepBndLib::Add(aV, aBox);
    aHAB->SetValue(i, aBox);
    aMIS.Add(i, aV);
    aMSB.Add(aV, aBox);
  }
  //
  aBSB.Initialize(aHAB);
  //
  for (i=1; i<=aNbV; ++i) {
    const TopoDS_Shape& aV=aMV(i);
    //
    if (aMVProcessed.Contains(aV)) {
      continue;
    }
    //
    const Bnd_Box& aBoxV=aMSB.FindFromKey(aV);
    const TColStd_ListOfInteger& aLI=aBSB.Compare(aBoxV);
    aNbVSD=aLI.Extent();
    if (!aNbVSD) {
      myErrorStatus=3; // it must not be
      return;
    }
    //
    // Images
    TopTools_ListOfShape aLVSD;
    //
    aIt.Initialize(aLI);
    for (j=0; aIt.More(); aIt.Next(), ++j) {
      aIndex=aIt.Value();
      const TopoDS_Shape& aVx=aMIS.FindFromKey(aIndex);
      if(!j) {
        aVF=aVx;
      }
      aLVSD.Append(aVx);
      aMVProcessed.Add(aVx);
    }
    myImages.Bind(aVF, aLVSD);
  }
  // Origins
  aItIm.Initialize(myImages);
  for (; aItIm.More(); aItIm.Next()) {
    const TopoDS_Shape& aV=aItIm.Key();
    const TopTools_ListOfShape& aLVSD=aItIm.Value();
    //
    aItS.Initialize(aLVSD);
    for (; aItS.More(); aItS.Next()) {
      const TopoDS_Shape& aVSD=aItS.Value();
      if (!myOrigins.IsBound(aVSD)) {
        myOrigins.Bind(aVSD, aV);
      }
    }
  }
}