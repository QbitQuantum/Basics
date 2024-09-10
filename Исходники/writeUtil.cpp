// This method inspects the JSON blob stored in the 'USD_UserExportedAttributesJson'
// attribute on the Maya node at dagPath and exports any attributes specified
// there onto usdPrim at time usdTime. The JSON should contain an object that
// maps Maya attribute names to other JSON objects that contain metadata about
// how to export the attribute into USD. For example:
//
//    {
//        "myMayaAttributeOne": {
//        },
//        "myMayaAttributeTwo": {
//            "usdAttrName": "my:namespace:attributeTwo"
//        },
//        "attributeAsPrimvar": {
//            "usdAttrType": "primvar"
//        },
//        "attributeAsVertexInterpPrimvar": {
//            "usdAttrType": "primvar",
//            "interpolation": "vertex"
//        },
//        "attributeAsRibAttribute": {
//            "usdAttrType": "usdRi"
//        },
//        "doubleAttributeAsFloatAttribute": {
//            "translateMayaDoubleToUsdSinglePrecision": true
//        }
//    }
//
// If the attribute metadata contains a value for "usdAttrName", the attribute
// will be given that name in USD. Otherwise, the Maya attribute name will be
// used for primvars and UsdRi attributes, or the Maya attribute name prepended
// with the "userProperties" namespace will be used for regular USD attributes.
// Maya attributes in the JSON will be processed in sorted order, and any
// USD attribute name collisions will be resolved by using the first attribute
// visited and warning about subsequent attribute tags.
//
bool
PxrUsdMayaWriteUtil::WriteUserExportedAttributes(
        const MDagPath& dagPath,
        const UsdPrim& usdPrim,
        const UsdTimeCode& usdTime)
{
    std::vector<PxrUsdMayaUserTaggedAttribute> exportedAttributes =
        PxrUsdMayaUserTaggedAttribute::GetUserTaggedAttributesForNode(dagPath);
    for (const PxrUsdMayaUserTaggedAttribute& attr : exportedAttributes) {
        const std::string& usdAttrName = attr.GetUsdName();
        const TfToken& usdAttrType = attr.GetUsdType();
        const TfToken& interpolation = attr.GetUsdInterpolation();
        const bool translateMayaDoubleToUsdSinglePrecision =
            attr.GetTranslateMayaDoubleToUsdSinglePrecision();
        const MPlug& attrPlug = attr.GetMayaPlug();
        UsdAttribute usdAttr;

        if (usdAttrType ==
                    PxrUsdMayaUserTaggedAttributeTokens->USDAttrTypePrimvar) {
            UsdGeomImageable imageable(usdPrim);
            if (!imageable) {
                MGlobal::displayError(
                    TfStringPrintf(
                        "Cannot create primvar for non-UsdGeomImageable USD prim: '%s'",
                        usdPrim.GetPath().GetText()).c_str());
                continue;
            }
            UsdGeomPrimvar primvar =
                PxrUsdMayaWriteUtil::GetOrCreatePrimvar(attrPlug,
                                                        imageable,
                                                        usdAttrName,
                                                        interpolation,
                                                        -1,
                                                        true,
                                                        translateMayaDoubleToUsdSinglePrecision);
            if (primvar) {
                usdAttr = primvar.GetAttr();
            }
        } else if (usdAttrType ==
                    PxrUsdMayaUserTaggedAttributeTokens->USDAttrTypeUsdRi) {
            usdAttr =
                PxrUsdMayaWriteUtil::GetOrCreateUsdRiAttribute(attrPlug,
                                                               usdPrim,
                                                               usdAttrName,
                                                               "user",
                                                               translateMayaDoubleToUsdSinglePrecision);
        } else {
            usdAttr = PxrUsdMayaWriteUtil::GetOrCreateUsdAttr(attrPlug,
                                                              usdPrim,
                                                              usdAttrName,
                                                              true,
                                                              translateMayaDoubleToUsdSinglePrecision);
        }

        if (usdAttr) {
            if (!PxrUsdMayaWriteUtil::SetUsdAttr(attrPlug,
                                                    usdAttr,
                                                    usdTime,
                                                    translateMayaDoubleToUsdSinglePrecision)) {
                MGlobal::displayError(
                    TfStringPrintf("Could not set value for attribute: '%s'",
                                   usdAttr.GetPath().GetText()).c_str());
                continue;
            }
        } else {
            MGlobal::displayError(
                TfStringPrintf("Could not create attribute '%s' for USD prim: '%s'",
                               usdAttrName.c_str(),
                               usdPrim.GetPath().GetText()).c_str());
                continue;
        }
    }

    return true;
}