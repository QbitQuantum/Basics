// Modified  Thu Sep 14 14:35:18 2006
// Contribution of Samtech www.samcef.com BEGIN
//=======================================================================
//function : Contains
//purpose  :
//=======================================================================
Standard_Boolean Contains(const TopoDS_Edge& aE,
                          const TopoDS_Vertex& aV)
{
  Standard_Boolean bRet;
  TopoDS_Iterator aIt;
  //
  bRet=Standard_False;
  aIt.Initialize(aE);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aVE=aIt.Value();
    if (aVE.IsSame(aV)) {
      bRet=!bRet;
      break;
    }
  }
  return bRet;
}