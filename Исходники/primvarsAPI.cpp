static
void
_RecurseForInheritablePrimvars(const UsdPrim &prim, const TfToken &pvPrefix,
                               std::vector<UsdGeomPrimvar> *primvars,
                               bool acceptAll = false) 
{
    if (prim.IsPseudoRoot())
        return;

    // The `acceptAll` override is only useful for the prim we are actually
    // querying, i.e. the *first* prim on which this function is called
    _RecurseForInheritablePrimvars(prim.GetParent(), pvPrefix, primvars);
    _AddPrimToInheritedPrimvars(prim, pvPrefix, primvars, primvars, acceptAll);
}