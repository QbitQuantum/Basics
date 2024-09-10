//=======================================================================
//function :FillInternalShapes
//purpose  :
//=======================================================================
  void GEOMAlgo_Builder::FillInternalShapes()
{
  myErrorStatus=0;
  //
  const NMTDS_ShapesDataStructure& aDS=*myPaveFiller->DS();
  NMTTools_PaveFiller* pPF=myPaveFiller;
  const Handle(IntTools_Context)& aCtx= pPF->Context();
  //
  //Standard_Boolean bHasImage;
  Standard_Integer i, j, jT, aNbS, aNbSI, aNbSx, aNbSd;
  TopAbs_ShapeEnum aType, aT[]={ TopAbs_VERTEX, TopAbs_EDGE };
  TopAbs_State aState;
  TopTools_ListIteratorOfListOfShape aIt, aIt1;
  TopTools_IndexedDataMapOfShapeListOfShape aMSx;
  TopTools_IndexedMapOfShape aMx;
  TopTools_MapOfShape aMSI, aMFence, aMSOr;
  TopTools_MapIteratorOfMapOfShape aItM;
  TopTools_ListOfShape aLSI, aLSd;
  TopoDS_Iterator aItS;
  BRep_Builder aBB;
  //
  // 1. Shapes to process
  //
  // 1.1 Shapes from pure arguments aMSI
  // 1.1.1 vertex, edge
  for (i=0; i<2; ++i) {
    jT=(Standard_Integer)aT[i];
    const TopTools_ListOfShape &aLS=myShapes1[jT];
    aIt.Initialize(aLS);
    for (; aIt.More(); aIt.Next()) {
      const TopoDS_Shape& aS=aIt.Value();
      if (aMFence.Add(aS)) {
        aLSI.Append(aS);
      }
    }
  }
  // 1.1.2 wire
  {
    jT=(Standard_Integer)TopAbs_WIRE;
    const TopTools_ListOfShape &aLW=myShapes1[jT];
    aIt.Initialize(aLW);
    for (; aIt.More(); aIt.Next()) {
      const TopoDS_Shape& aW=aIt.Value();
      aItS.Initialize(aW);
      for (; aItS.More(); aItS.Next()) {
        const TopoDS_Shape& aE=aItS.Value();
        if (aMFence.Add(aE)) {
          aLSI.Append(aE);
        }
      }
    }
  }
  // 1.1.3 theirs images/sources
  aIt1.Initialize(aLSI);
  for (; aIt1.More(); aIt1.Next()) {
    const TopoDS_Shape& aS=aIt1.Value();
    if (myImages.HasImage(aS)) {
      const TopTools_ListOfShape &aLSp=myImages.Image(aS);
      aIt.Initialize(aLSp);
      for (; aIt.More(); aIt.Next()) {
        const TopoDS_Shape& aSI=aIt.Value();
        aMSI.Add(aSI);
      }
    }
    else {
      aMSI.Add(aS);
    }
  }
  aLSI.Clear();
  aNbSI=aMSI.Extent();
  //
  // 2. Internal vertices, edges from source solids
  aMFence.Clear();
  aLSd.Clear();
  //
  aNbS=aDS.NumberOfShapesOfTheObject();
  for (i=1; i<=aNbS; ++i) {
    const TopoDS_Shape& aS=aDS.Shape(i);
    aType=aS.ShapeType();
    if (aType==TopAbs_SOLID) {
      //
      aMx.Clear();
      OwnInternalShapes(aS, aMx);
      //
      aNbSx=aMx.Extent();
      for (j=1; j<=aNbSx; ++j) {
        const TopoDS_Shape& aSI=aMx(j);
        if (myImages.HasImage(aSI)) {
          const TopTools_ListOfShape &aLSp=myImages.Image(aSI);
          aIt.Initialize(aLSp);
          for (; aIt.More(); aIt.Next()) {
            const TopoDS_Shape& aSp=aIt.Value();
            aMSI.Add(aSp);
          }
        }
        else {
          aMSI.Add(aSI);
        }
      }
      //
      // build aux map from splits of solids
      if (myImages.HasImage(aS)) {
        const TopTools_ListOfShape &aLSp=myImages.Image(aS);
        aIt.Initialize(aLSp);
        for (; aIt.More(); aIt.Next()) {
          const TopoDS_Shape& aSp=aIt.Value();
          if (aMFence.Add(aSp)) {
            TopExp::MapShapesAndAncestors(aSp, TopAbs_VERTEX, TopAbs_EDGE, aMSx);
            TopExp::MapShapesAndAncestors(aSp, TopAbs_VERTEX, TopAbs_FACE, aMSx);
            TopExp::MapShapesAndAncestors(aSp, TopAbs_EDGE  , TopAbs_FACE, aMSx);
            aLSd.Append(aSp);
          }
        }
      }
      else {
        if (aMFence.Add(aS)) {
          TopExp::MapShapesAndAncestors(aS, TopAbs_VERTEX, TopAbs_EDGE, aMSx);
          TopExp::MapShapesAndAncestors(aS, TopAbs_VERTEX, TopAbs_FACE, aMSx);
          TopExp::MapShapesAndAncestors(aS, TopAbs_EDGE  , TopAbs_FACE, aMSx);
          aLSd.Append(aS);
          aMSOr.Add(aS);
        }
      }
    }//if (aType==TopAbs_SOLID)
  }
  //
  aNbSd=aLSd.Extent();
  //
  // 3. Some shapes of aMSI can be already tied with faces of
  //    split solids
  aItM.Initialize(aMSI);
  for (; aItM.More(); aItM.Next()) {
    const TopoDS_Shape& aSI=aItM.Key();
    if (aMSx.Contains(aSI)) {
      const TopTools_ListOfShape &aLSx=aMSx.FindFromKey(aSI);
      aNbSx=aLSx.Extent();
      if (aNbSx) {
        aMSI.Remove(aSI);
      }
    }
  }
  //
  // 4. Just check it
  aNbSI=aMSI.Extent();
  if (!aNbSI) {
    return;
  }
  //
  // 5 Settle internal vertices and edges into solids
  aMx.Clear();
  aIt.Initialize(aLSd);
  for (; aIt.More(); aIt.Next()) {
    TopoDS_Solid aSd=TopoDS::Solid(aIt.Value());
    //
    aItM.Initialize(aMSI);
    for (; aItM.More(); aItM.Next()) {
      TopoDS_Shape aSI=aItM.Key();
      aSI.Orientation(TopAbs_INTERNAL);
      //
      aState=GEOMAlgo_Tools3D::ComputeStateByOnePoint(aSI, aSd, 1.e-11, aCtx);
      if (aState==TopAbs_IN) {
        //
        if(aMSOr.Contains(aSd)) {
          //
          TopoDS_Solid aSdx;
          //
          aBB.MakeSolid(aSdx);
          aItS.Initialize(aSd);
          for (; aItS.More(); aItS.Next()) {
            const TopoDS_Shape& aSh=aItS.Value();
            aBB.Add(aSdx, aSh);
          }
          //
          aBB.Add(aSdx, aSI);
          //
          myImages.Bind(aSd, aSdx);
          aMSOr.Remove(aSd);
          aSd=aSdx;
        }
        else {
          aBB.Add(aSd, aSI);
        }
        //
        aMSI.Remove(aSI);
      } //if (aState==TopAbs_IN) {
    }// for (; aItM.More(); aItM.Next()) {
  }//for (; aIt1.More(); aIt1.Next()) {
}