//=======================================================================
// function: FillImagesContainers
// purpose:
//=======================================================================
void GEOMAlgo_Builder::FillImagesContainers(const TopAbs_ShapeEnum theType)
{
    myErrorStatus=0;
    //
    Standard_Boolean bInterferred, bToReverse;
    Standard_Integer i, aNbS;
    TopAbs_ShapeEnum aType;
    BRep_Builder aBB;
    TopoDS_Iterator aIt;
    TopTools_ListIteratorOfListOfShape aItIm;
    TopTools_MapOfShape aMS;
    TopTools_MapIteratorOfMapOfShape aItS;
    //
    const NMTDS_ShapesDataStructure& aDS=*myPaveFiller->DS();
    NMTTools_PaveFiller* pPF=myPaveFiller;
    const Handle(IntTools_Context)& aCtx= pPF->Context();
    //
    aNbS=aDS.NumberOfShapesOfTheObject();
    for (i=1; i<=aNbS; ++i) {
        const TopoDS_Shape& aC=aDS.Shape(i);
        aType=aC.ShapeType();
        if (aType==theType) {
            aMS.Add(aC);
        }
    }
    //
    if (theType==TopAbs_COMPOUND) {
        FillImagesCompounds(aMS, myImages);
        return;
    }
    //
    aItS.Initialize(aMS);
    for (; aItS.More(); aItS.Next()) {
        const TopoDS_Shape& aC=aItS.Key();
        // whether the shape has image
        bInterferred=Standard_False;
        aIt.Initialize(aC);
        for (; aIt.More(); aIt.Next()) {
            const TopoDS_Shape& aF=aIt.Value();
            if (myImages.HasImage(aF)) {
                bInterferred=!bInterferred;
                break;
            }
        }
        if (!bInterferred) {
            continue;
        }
        //
        TopoDS_Shape aCIm;
        GEOMAlgo_Tools3D::MakeContainer(theType, aCIm);
        //
        aIt.Initialize(aC);
        for (; aIt.More(); aIt.Next()) {
            const TopoDS_Shape& aF=aIt.Value();
            if (myImages.HasImage(aF)) {
                const TopTools_ListOfShape& aLFIm=myImages.Image(aF);
                aItIm.Initialize(aLFIm);
                for (; aItIm.More(); aItIm.Next()) {
                    TopoDS_Shape aFIm=aItIm.Value();
                    //
                    bToReverse=GEOMAlgo_Tools3D::IsSplitToReverse(aFIm, aF, aCtx);
                    if (bToReverse) {
                        aFIm.Reverse();
                    }
                    aBB.Add(aCIm, aFIm);
                }
            }
            else {
                aBB.Add(aCIm, aF);
            }
        }
        myImages.Bind(aC, aCIm);
    }// for (; aItS.More(); aItS.Next()) {
}