//=======================================================================
//function : FillCompound
//purpose  :
//=======================================================================
void GEOMAlgo_Gluer2::FillCompound(const TopoDS_Shape& aC)
{
  Standard_Boolean bHasImage;
  TopAbs_ShapeEnum aType;
  TopoDS_Shape aCnew, aCXnew;
  TopoDS_Iterator aItC;
  BRep_Builder aBB;
  //
  bHasImage=HasImage(aC);
  if (!bHasImage) {
    return;
  }
  //
  GEOMAlgo_Tools3D::MakeContainer(TopAbs_COMPOUND, aCnew);
  //
  aItC.Initialize(aC);
  for (; aItC.More(); aItC.Next()) {
    const TopoDS_Shape& aCX=aItC.Value();
    aType=aCX.ShapeType();
    //
    if (aType==TopAbs_COMPOUND) {
      FillCompound(aCX);
    }
    //
    if (myOrigins.IsBound(aCX)) {
      aCXnew=myOrigins.Find(aCX);
      aCXnew.Orientation(aCX.Orientation());
      aBB.Add(aCnew, aCXnew);
    }
    else {
      aBB.Add(aCnew, aCX);
    }
  }
  //
  //myImages / myOrigins
  TopTools_ListOfShape aLSD;
  //
  aLSD.Append(aC);
  myImages.Bind(aCnew, aLSD);
  myOrigins.Bind(aC, aCnew);
}