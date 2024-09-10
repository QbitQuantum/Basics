//=======================================================================
//function : PerformLoops
//purpose  : 
//=======================================================================
  void GEOMAlgo_BuilderFace::PerformLoops()
{
  myErrorStatus=0;
  //
  Standard_Boolean bFlag;
  Standard_Integer aNbEA;
  TopTools_ListIteratorOfListOfShape aIt;
  TopTools_MapIteratorOfMapOfOrientedShape aItM;
  TopTools_IndexedDataMapOfShapeListOfShape aVEMap;
  TopTools_MapOfOrientedShape aMAdded;
  TopoDS_Iterator aItW;
  BRep_Builder aBB; 
  GEOMAlgo_WireEdgeSet aWES;
  GEOMAlgo_WESCorrector aWESCor;
  //
  // 1. Usual Wires 
  myLoops.Clear();
  aWES.SetFace(myFace);
  //
  aIt.Initialize (myShapes);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aE=aIt.Value();
    if (!myShapesToAvoid.Contains(aE)) {
      aWES.AddStartElement(aE);
    }
  }
  //
  aWESCor.SetWES(aWES);
  aWESCor.Perform();
  //
  GEOMAlgo_WireEdgeSet& aWESN=aWESCor.NewWES();
  const TopTools_ListOfShape& aLW=aWESN.Shapes();
  //
  aIt.Initialize (aLW);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aW=aIt.Value();
    myLoops.Append(aW);
  }
  //modified by NIZNHY-PKV Tue Aug  5 15:09:29 2008f
  // Post Treatment
  TopTools_MapOfOrientedShape aMEP;
  // 
  // a. collect all edges that are in loops
  aIt.Initialize (myLoops);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aW=aIt.Value();
    aItW.Initialize(aW);
    for (; aItW.More(); aItW.Next()) {
      const TopoDS_Shape& aE=aItW.Value();
      aMEP.Add(aE);
    }
  }
  // 
  // b. collect all edges that are to avoid
  aItM.Initialize(myShapesToAvoid);
  for (; aItM.More(); aItM.Next()) {
    const TopoDS_Shape& aE=aItM.Key();
    aMEP.Add(aE);
  }
  //
  // c. add all edges that are not processed to myShapesToAvoid
  aIt.Initialize (myShapes);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aE=aIt.Value();
    if (!aMEP.Contains(aE)) {
      myShapesToAvoid.Add(aE);
    }
  }
  //modified by NIZNHY-PKV Tue Aug  5 15:09:35 2008t
  //
  // 2. Internal Wires
  myLoopsInternal.Clear();
  //
  aNbEA=myShapesToAvoid.Extent();
  aItM.Initialize(myShapesToAvoid);
  for (; aItM.More(); aItM.Next()) {
    const TopoDS_Shape& aEE=aItM.Key();
    TopExp::MapShapesAndAncestors(aEE, TopAbs_VERTEX, TopAbs_EDGE, aVEMap);
  }
  //
  bFlag=Standard_True;
  aItM.Initialize(myShapesToAvoid);
  for (; aItM.More()&&bFlag; aItM.Next()) {
    const TopoDS_Shape& aEE=aItM.Key();
    if (!aMAdded.Add(aEE)) {
      continue;
    }
    //
    // make new wire
    TopoDS_Wire aW;
    aBB.MakeWire(aW);
    aBB.Add(aW, aEE);
    //
    aItW.Initialize(aW);
    for (; aItW.More()&&bFlag; aItW.Next()) {
      const TopoDS_Edge& aE=TopoDS::Edge(aItW.Value());
      //
      TopoDS_Iterator aItE(aE);
      for (; aItE.More()&&bFlag; aItE.Next()) {
	const TopoDS_Vertex& aV = TopoDS::Vertex(aItE.Value());
	const TopTools_ListOfShape& aLE=aVEMap.FindFromKey(aV);
	aIt.Initialize(aLE);
	for (; aIt.More()&&bFlag; aIt.Next()) { 
	  const TopoDS_Shape& aEx=aIt.Value();
	  if (aMAdded.Add(aEx)) {
	    aBB.Add(aW, aEx);
	    if(aMAdded.Extent()==aNbEA) {
	      bFlag=!bFlag;
	    }
	  }
	}//for (; aIt.More(); aIt.Next()) { 
      }//for (; aItE.More(); aItE.Next()) {
    }//for (; aItW.More(); aItW.Next()) {
    myLoopsInternal.Append(aW);
  }//for (; aItM.More(); aItM.Next()) {
}