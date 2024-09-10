PXR_NAMESPACE_OPEN_SCOPE


// TODO: We should centralize this logic in a UsdImaging ShaderAdapter.

/*static*/
UsdPrim
UsdImaging_MaterialStrategy::GetTargetedShader(UsdPrim const& materialPrim,
                                        UsdRelationship const& materialRel)
{
    SdfPathVector targets;
    if (!materialRel.GetForwardedTargets(&targets))
        return UsdPrim();

    if (targets.size() != 1) {
        // XXX: This should really be a validation error once USD gets that
        // feature.
        TF_WARN("We expect only one target on relationship %s of prim <%s>, "
                "but got %zu.",
                materialRel.GetName().GetText(),
                materialPrim.GetPath().GetText(),
                targets.size());
        return UsdPrim();
    }

    if (!targets[0].IsPrimPath()) {
        // XXX: This should really be a validation error once USD gets that
        // feature.
        TF_WARN("We expect the target of the relationship %s of prim <%s> "
                "to be a prim, instead it is <%s>.",
                materialRel.GetName().GetText(),
                materialPrim.GetPath().GetText(),
                targets[0].GetText());
        return UsdPrim();
    }

    return materialPrim.GetStage()->GetPrimAtPath(targets[0]);
}