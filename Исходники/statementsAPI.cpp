void
UsdRiStatementsAPI::SetScopedCoordinateSystem(const std::string &coordSysName)
{
    UsdAttribute attr = GetPrim().CreateAttribute(_tokens->scopedCoordsys, 
                                                  SdfValueTypeNames->String,
                                                  /* custom = */ false);
    if (TF_VERIFY(attr)) {
        attr.Set(coordSysName);

        UsdPrim currPrim = GetPrim();
        while (currPrim) {
            if (currPrim.IsModel() && !currPrim.IsGroup() &&
                currPrim.GetPath() != SdfPath::AbsoluteRootPath()) {
                UsdRelationship rel =
                    currPrim.CreateRelationship(_tokens->modelScopedCoordsys,
                                                /* custom = */ false);
                if (TF_VERIFY(rel)) {
                    rel.AddTarget(GetPrim().GetPath());
                }
                break;
            }

            currPrim = currPrim.GetParent();
        }
    }
}