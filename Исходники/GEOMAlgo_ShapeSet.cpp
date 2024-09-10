//modified by NIZNHY-PKV Wed Oct 28 13:51:36 2010f
//=======================================================================
//function : IsEqual
//purpose  : 
//=======================================================================
  Standard_Boolean GEOMAlgo_ShapeSet::IsEqual(const GEOMAlgo_ShapeSet& theOther)const
{
  Standard_Boolean bRet;
  Standard_Integer aNb1, aNb2;
  TopTools_ListIteratorOfListOfShape aIt;
  //
  bRet=Standard_True;
  aNb1=myList.Extent();
  const TopTools_ListOfShape& aLS2=theOther.GetSet();
  aNb2=aLS2.Extent();
  if (aNb1!=aNb2) {
    return !bRet;
  }
  //
  aIt.Initialize(myList);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    if(!theOther.myMap.Contains(aS)) {
      bRet=!bRet;
      break;
    }
  }
  return bRet;
}