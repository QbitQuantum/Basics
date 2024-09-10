//=======================================================================
//function : MapShapes
//purpose  :
//=======================================================================
void MapShapes(const TopoDS_Shape& theS,
               TopTools_MapOfShape& theM)
{
    theM.Add(theS);
    TopoDS_Iterator anIt;
    anIt.Initialize(theS);
    for (; anIt.More(); anIt.Next()) {
        const TopoDS_Shape& aSx=anIt.Value();
        MapShapes(aSx, theM);
    }
}