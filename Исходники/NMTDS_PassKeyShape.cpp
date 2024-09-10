//=======================================================================
//function :SetShapes
//purpose  : 
//=======================================================================
  void NMTDS_PassKeyShape::SetShapes(const TopTools_ListOfShape& aLS)
{
  Standard_Integer i, aId, aIdN;
  TopTools_ListIteratorOfListOfShape aIt;
  //
  Clear();
  aIt.Initialize(aLS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    myMap.Add(aS);
  }
  myNbIds=myMap.Extent();
  for(i=1; i<=myNbIds; ++i) {
    const TopoDS_Shape& aS=myMap(i);
    aId=aS.HashCode(myUpper);
    aIdN=NormalizedId(aId, myNbIds);
    mySum+=aIdN;
  }
}