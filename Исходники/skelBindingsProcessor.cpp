/// Finds the rootmost ancestor of the prim at \p path that is an Xform
/// or SkelRoot type prim. The result may be the prim itself.
static UsdPrim
_FindRootmostXformOrSkelRoot(const UsdStagePtr& stage, const SdfPath& path)
{
    UsdPrim currentPrim = stage->GetPrimAtPath(path);
    UsdPrim rootmost;
    while (currentPrim) {
        if (currentPrim.IsA<UsdGeomXform>()) {
            rootmost = currentPrim;
        } else if (currentPrim.IsA<UsdSkelRoot>()) {
            rootmost = currentPrim;
        }
        currentPrim = currentPrim.GetParent();
    }

    return rootmost;
}