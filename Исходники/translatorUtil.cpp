/* static */
bool
PxrUsdMayaTranslatorUtil::CreateNode(
        const UsdPrim& usdPrim,
        const MString& nodeTypeName,
        MObject& parentNode,
        PxrUsdMayaPrimReaderContext* context,
        MStatus* status,
        MObject* mayaNodeObj)
{
    if (not CreateNode(MString(usdPrim.GetName().GetText()),
                       nodeTypeName,
                       parentNode,
                       status,
                       mayaNodeObj)) {
        return false;
    }

    if (context) {
        context->RegisterNewMayaNode(usdPrim.GetPath().GetString(), *mayaNodeObj);
    }

    return true;
}