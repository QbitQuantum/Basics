static FnKat::Attribute
_GetMaterialAssignAttr(
        const UsdPrim& prim,
        const PxrUsdKatanaUsdInPrivateData& data)
{
    if (not prim or prim.GetPath() == SdfPath::AbsoluteRootPath()) {
        // Special-case to pre-empt coding errors.
        return FnKat::Attribute();
    }

    UsdRelationship usdRel = UsdShadeLook::GetBindingRel(prim);
    if (usdRel) {
        // USD shading binding
        SdfPathVector targetPaths;
        usdRel.GetForwardedTargets(&targetPaths);
        if (targetPaths.size() > 0) {
            if (not targetPaths[0].IsPrimPath()) {
                FnLogWarn("Target path " << prim.GetPath().GetString() <<
                          " is not a prim");
                return FnKat::Attribute();
            }

            // This is a copy as it could be modified below.
            SdfPath targetPath = targetPaths[0];
            UsdPrim targetPrim = data.GetUsdInArgs()->GetStage()->GetPrimAtPath(targetPath);
            // If the target is inside a master, then it needs to be re-targeted 
            // to the instance.
            // 
            // XXX remove this special awareness once GetMasterWithContext is
            //     is available as the provided prim will automatically
            //     retarget (or provide enough context to retarget without
            //     tracking manually).
            if (targetPrim and targetPrim.IsInMaster()) {
                if (not data.GetInstancePath().IsEmpty() and 
                        not data.GetMasterPath().IsEmpty()) {

                    // Check if the source and the target of the relationship 
                    // belong to the same master.
                    // If they do, we have the context necessary to do the 
                    // re-mapping.
                    if (data.GetMasterPath().GetCommonPrefix(targetPath).
                            GetPathElementCount() > 0) {
                        targetPath = data.GetInstancePath().AppendPath(
                            targetPath.ReplacePrefix(targetPath.GetPrefixes()[0],
                                SdfPath::ReflexiveRelativePath()));
                    } else {
                        // Warn saying the target of relationship isn't within 
                        // the same master as the source.
                        FnLogWarn("Target path " << prim.GetPath().GetString() 
                            << " isn't within the master " << data.GetMasterPath());
                        return FnKat::Attribute();
                    }
                } else {
                    // XXX
                    // When loading beneath a master via an isolatePath
                    // opArg, we can encounter targets which are within masters
                    // but not within the context of a material.
                    // While that would be an error according to the below
                    // warning, it produces the expected results.
                    // This case can occur when expanding pointinstancers as
                    // the sources are made via execution of PxrUsdIn again
                    // at the sub-trees.
                    
                    
                    // Warn saying target of relationship is in a master, 
                    // but the associated instance path is unknown!
                    // FnLogWarn("Target path " << prim.GetPath().GetString() 
                    //         << " is within a master, but the associated "
                    //         "instancePath is unknown.");
                    // return FnKat::Attribute();
                }
            }

            // Convert the target path to the equivalent katana location.
            // XXX: Looks may have an atypical USD->Katana 
            // path mapping
            std::string location =
                PxrUsdKatanaUtils::ConvertUsdLookPathToKatLocation(targetPath, data);
                
            // XXX Looks containing only display terminals are causing issues
            //     with katana material manipulation workflows.
            //     For now: exclude any material assign which doesn't include
            //     /Looks/ in the path
            if (location.find(UsdKatanaTokens->katanaLooksScopePathSubstring)
                    == std::string::npos)
            {
                return FnKat::Attribute();
            }
                
                
            // location = TfStringReplace(location, "/Looks/", "/Materials/");
            // XXX handle multiple assignments
            return FnKat::StringAttribute(location);
        }
    }

    return FnKat::Attribute();
}