//=======================================================================
// function: BuildSplitFaces
// purpose:
//=======================================================================
void GEOMAlgo_Builder::BuildSplitFaces()
{
  const NMTDS_ShapesDataStructure& aDS=*myPaveFiller->DS();
  NMTTools_PaveFiller* pPF=myPaveFiller;
  NMTDS_InterfPool* pIP=pPF->IP();
  BOPTools_CArray1OfSSInterference& aFFs=pIP->SSInterferences();
  const Handle(IntTools_Context)& aCtx= pPF->Context();
  //
  Standard_Boolean bToReverse, bIsClosed, bIsDegenerated;
  Standard_Integer i, aNb, aNbF, nF;
  TopTools_MapOfShape aMFence;
  TColStd_IndexedMapOfInteger aMFP;
  TopExp_Explorer anExp;
  TopoDS_Face aFF;
  TopoDS_Edge aSp, aEE;
  TopTools_ListIteratorOfListOfShape aIt;
  TopAbs_Orientation anOriF, anOriE;
  //
  mySplitFaces.Clear();
  //
  // 1. Select Faces to process (MFP)
  aNb=aDS.NumberOfShapesOfTheObject();
  for (i=1; i<=aNb; ++i) {
    const TopoDS_Shape& aF=aDS.Shape(i);
    if (aF.ShapeType()!=TopAbs_FACE) {
      continue;
    }
    if (!aMFence.Add(aF)) {
      continue;
    }
    //
    if (myInParts.Contains(aF)) {
      aMFP.Add(i);
      continue;
    }
    //
    anExp.Init(aF, TopAbs_EDGE);
    for (; anExp.More(); anExp.Next()) {
      const TopoDS_Shape& aE=anExp.Current();
      if (myImages.HasImage(aE)) {
        aMFP.Add(i);
        break;
      }
    }
    //
    //===
    {
      Standard_Integer aNbFFs, aNbSE, j, n1, n2;
      //
      aNbFFs=aFFs.Extent();
      for (j=1; j<=aNbFFs; ++j) {
        BOPTools_SSInterference& aFFj=aFFs(j);
        aFFj.Indices(n1, n2);
        if (!(n1==i || n2==i)) {
          continue;
        }
        //
        const TColStd_ListOfInteger& aLSE=aFFj.SharedEdges();
        aNbSE=aLSE.Extent();
        if (aNbSE) {
          aMFP.Add(i);
          break;
        }
      }
    }
    //===
    //
  }// for (i=1; i<=aNb; ++i)
  //
  // 2. ProcessFaces
  aNbF=aMFP.Extent();
  for (i=1; i<=aNbF; ++i) {
    nF=aMFP(i);
    const TopoDS_Face& aF=TopoDS::Face(aDS.Shape(nF));
    anOriF=aF.Orientation();
    aFF=aF;
    aFF.Orientation(TopAbs_FORWARD);
    //
    aMFence.Clear();
    //
    // 2.1. Fill WES
    GEOMAlgo_WireEdgeSet aWES;
    aWES.SetFace(aFF);
    //
    //  2.1.1. Add Split parts
    anExp.Init(aFF, TopAbs_EDGE);
    for (; anExp.More(); anExp.Next()) {
      const TopoDS_Edge& aE=TopoDS::Edge(anExp.Current());
      anOriE=aE.Orientation();
      //
      if (!myImages.HasImage(aE)) {
        if (anOriE==TopAbs_INTERNAL) {
          aEE=aE;
          aEE.Orientation(TopAbs_FORWARD);
          aWES.AddStartElement(aEE);
          aEE.Orientation(TopAbs_REVERSED);
          aWES.AddStartElement(aEE);
        }
        else {
          aWES.AddStartElement(aE);
        }
        continue;
      }
      //
      bIsDegenerated=BRep_Tool::Degenerated(aE);
      //modified by NIZNHY-PKV Wed Mar 07 07:46:09 2012f
      bIsClosed=IsClosed(aE, aF);
      //bIsClosed=BRep_Tool::IsClosed(aE, aF);
      //modified by NIZNHY-PKV Wed Mar 07 07:46:13 2012t
      //
      const TopTools_ListOfShape& aLIE=myImages.Image(aE);
      aIt.Initialize(aLIE);
      for (; aIt.More(); aIt.Next()) {
        aSp=TopoDS::Edge(aIt.Value());
        //
        if (bIsDegenerated) {
          aSp.Orientation(anOriE);
          aWES.AddStartElement(aSp);
          continue;
        }
        //
        if (anOriE==TopAbs_INTERNAL) {
          aSp.Orientation(TopAbs_FORWARD);
          aWES.AddStartElement(aSp);
          aSp.Orientation(TopAbs_REVERSED);
          aWES.AddStartElement(aSp);
          continue;
        }
        //
        if (bIsClosed){
          if (aMFence.Add(aSp)) {
            //
            if (!BRep_Tool::IsClosed(aSp, aF)){
              BOPTools_Tools3D::DoSplitSEAMOnFace(aSp, aF);
            }
            //
            aSp.Orientation(TopAbs_FORWARD);
            aWES.AddStartElement(aSp);
            aSp.Orientation(TopAbs_REVERSED);
            aWES.AddStartElement(aSp);
          }
          continue;
        }// if (aMFence.Add(aSp))
        //
        aSp.Orientation(anOriE);
        bToReverse=BOPTools_Tools3D::IsSplitToReverse1(aSp, aE, aCtx);
        if (bToReverse) {
          aSp.Reverse();
        }
        aWES.AddStartElement(aSp);
      }// for (; aIt.More(); aIt.Next()) {
    }// for (; anExp.More(); anExp.Next()) {
    //
    // 2.1.2. Add In2D Parts
    if (myInParts.Contains(aF)) {
      const TopTools_ListOfShape& aLE=myInParts.FindFromKey(aF);
      aIt.Initialize(aLE);
      for (; aIt.More(); aIt.Next()) {
        aSp=TopoDS::Edge(aIt.Value());
        //
        aSp.Orientation(TopAbs_FORWARD);
        aWES.AddStartElement(aSp);
        //
        aSp.Orientation(TopAbs_REVERSED);
        aWES.AddStartElement(aSp);
      }
    }
    //
    // 2.2. Build images Faces
    TopTools_ListOfShape aLFR;
    GEOMAlgo_ShapeSet aS1, aS2;
    //
    const TopTools_ListOfShape& aSE=aWES.StartElements();
    aS1.Add(aSE);
    aS2.Add(aFF, TopAbs_EDGE);
    if (aS1.IsEqual(aS2)) {
      aLFR.Append(aF);
    }
    else {
      GEOMAlgo_BuilderFace aBF;
      //
      aBF.SetFace(aFF);
      aBF.SetContext(aCtx);
      aBF.SetShapes(aSE);
      // <-DEB
      aBF.Perform();
      //
      const TopTools_ListOfShape& aLF=aBF.Areas();
      aIt.Initialize(aLF);
      for (; aIt.More(); aIt.Next()) {
        TopoDS_Shape& aFR=aIt.Value();
        if (anOriF==TopAbs_REVERSED) {
          aFR.Orientation(TopAbs_REVERSED);
        }
        aLFR.Append(aFR);
      }
    }
    //
    // 2.3. Collect draft images Faces
    mySplitFaces.Bind(aF, aLFR);
  }//for (i=1; i<=aNbF; ++i)
}