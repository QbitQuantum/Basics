bool
PxrUsdMayaShadingModeImportContext::GetCreatedObject(
        const UsdPrim& prim,
        MObject* obj) const
{
    if (not prim) {
        return false;
    }

    MObject node = _context->GetMayaNode(prim.GetPath(), false);
    if (not node.isNull()) {
        *obj = node;
        return true;
    }
    return false;
}