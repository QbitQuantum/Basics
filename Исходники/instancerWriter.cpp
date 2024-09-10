bool
PxrUsdTranslators_InstancerWriter::writeInstancerAttrs(
        const UsdTimeCode& usdTime,
        const UsdGeomPointInstancer& instancer)
{
    MStatus status = MS::kSuccess;
    MFnDagNode dagNode(GetDagPath(), &status);
    CHECK_MSTATUS_AND_RETURN(status, false);

    // Note: In this function, we don't read instances using the provided
    // MFnInstancer API. One reason is that it breaks up prototypes into their
    // constituent shapes, and there's no way to figure out which hierarchy
    // they came from. Another reason is that it only provides computed matrices
    // and not separate position, rotation, scale attrs.

    const SdfPath prototypesGroupPath =
            instancer.GetPrim().GetPath().AppendChild(_tokens->Prototypes);

    // At the default time, setup all the prototype instances.
    if (usdTime.IsDefault()) {
        const MPlug inputHierarchy = dagNode.findPlug("inputHierarchy", true,
                &status);
        CHECK_MSTATUS_AND_RETURN(status, false);

        // Note that the "Prototypes" prim needs to be a model group to ensure
        // contiguous model hierarchy.
        const UsdPrim prototypesGroupPrim = GetUsdStage()->DefinePrim(
                prototypesGroupPath);
        UsdModelAPI(prototypesGroupPrim).SetKind(KindTokens->group);
        _modelPaths.push_back(prototypesGroupPath);

        UsdRelationship prototypesRel = instancer.CreatePrototypesRel();

        const unsigned int numElements = inputHierarchy.numElements();
        for (unsigned int i = 0; i < numElements; ++i) {
            const MPlug plug = inputHierarchy[i];
            const MPlug source(UsdMayaUtil::GetConnected(plug));
            if (source.isNull()) {
                TF_WARN("Cannot read prototype: the source plug %s was null",
                        plug.name().asChar());
                return false;
            }

            MFnDagNode sourceNode(source.node(), &status);
            CHECK_MSTATUS_AND_RETURN(status, false);

            MDagPath prototypeDagPath;
            sourceNode.getPath(prototypeDagPath);

            // Prototype names are guaranteed unique by virtue of having a
            // unique numerical suffix _# indicating the prototype index.
            const TfToken prototypeName(
                    TfStringPrintf("%s_%d", sourceNode.name().asChar(), i));
            const SdfPath prototypeUsdPath = prototypesGroupPrim.GetPath()
                    .AppendChild(prototypeName);
            UsdPrim prototypePrim = GetUsdStage()->DefinePrim(
                    prototypeUsdPath);
            _modelPaths.push_back(prototypeUsdPath);

            // Try to be conservative and only create an intermediary xformOp
            // with the instancerTranslate if we can ensure that we don't need
            // to compensate for the translation on the prototype root.
            //
            // XXX: instancerTranslate does not behave well when added to a
            // reference that has an existing transform on the far side of the
            // reference. However, its behavior at least matches the
            // behavior in UsdMayaTranslatorModelAssembly. If we fix the
            // behavior there, we need to make sure that this is also
            // fixed to match.
            bool instancerTranslateAnimated = false;
            if (_NeedsExtraInstancerTranslate(
                    prototypeDagPath, &instancerTranslateAnimated)) {
                UsdGeomXformable xformable(prototypePrim);
                UsdGeomXformOp newOp = xformable.AddTranslateOp(
                        UsdGeomXformOp::PrecisionDouble,
                        _tokens->instancerTranslate);
                _instancerTranslateOps.push_back(
                        {prototypeDagPath, newOp, instancerTranslateAnimated});
            }

            // Two notes:
            // (1) We don't un-instance here, because it's OK for the prototype
            // to just be a reference to an instance master if the prototype
            // participates in Maya native instancing.
            // (2) The prototype root must be visible to match Maya's behavior,
            // which always vis'es the prototype root, even if it is marked
            // hidden.
            _writeJobCtx.CreatePrimWriterHierarchy(
                    prototypeDagPath,
                    prototypeUsdPath,
                    /*forceUninstance*/ false,
                    /*exportRootVisibility*/ false,
                    &_prototypeWriters);
            prototypesRel.AddTarget(prototypeUsdPath);
        }

        _numPrototypes = numElements;
    }

    // If there aren't any prototypes, fail and don't export on subsequent
    // time-sampled exports.
    if (_numPrototypes == 0) {
        return false;
    }

    // Actual write of prototypes (@ both default time and animated time).
    for (UsdMayaPrimWriterSharedPtr& writer : _prototypeWriters) {
        writer->Write(usdTime);

        if (usdTime.IsDefault()) {
            // Prototype roots should have kind component or derived.
            // Calling Write() above may have populated kinds, so don't stomp
            // over existing component-derived kinds.
            // (Note that ModelKindWriter's fix-up stage might change this.)
            if (writer->GetUsdPath().GetParentPath() == prototypesGroupPath) {
                if (const UsdPrim writerPrim = writer->GetUsdPrim()) {
                    UsdModelAPI primModelAPI(writerPrim);
                    TfToken kind;
                    primModelAPI.GetKind(&kind);
                    if (!KindRegistry::IsA(kind, KindTokens->component)) {
                        primModelAPI.SetKind(KindTokens->component);
                    }
                }
            }
        }
    }

    // Write the instancerTranslate xformOp for all prims that need it.
    // (This should happen @ default time or animated time depending on whether
    // the xform is animated.)
    for (const _TranslateOpData& opData : _instancerTranslateOps) {
        if (opData.isAnimated != usdTime.IsDefault()) {
            GfVec3d origin;
            if (_GetTransformedOriginInLocalSpace(opData.mayaPath, &origin)) {
                UsdGeomXformOp translateOp = opData.op;
                _SetAttribute(translateOp.GetAttr(), -origin, usdTime);
            }
        }
    }

    // Grab the inputPoints data from the source plug.
    // (This attribute's value must come from a source plug; it isn't
    // directly writeable. Thus reading it directly may not give the right
    // value depending on Maya's execution behavior.)
    MPlug inputPointsDest = dagNode.findPlug("inputPoints", true, &status);
    CHECK_MSTATUS_AND_RETURN(status, false);

    MPlug inputPointsSrc = UsdMayaUtil::GetConnected(inputPointsDest);
    if (inputPointsSrc.isNull()) {
        TF_WARN("inputPoints not connected on instancer '%s'",
                GetDagPath().fullPathName().asChar());
        return false;
    }

    auto holder = UsdMayaUtil::GetPlugDataHandle(inputPointsSrc);
    if (!holder) {
        TF_WARN("Unable to read inputPoints data handle for instancer '%s'",
                GetDagPath().fullPathName().asChar());
        return false;
    }

    MFnArrayAttrsData inputPointsData(holder->GetDataHandle().data(),
            &status);
    CHECK_MSTATUS_AND_RETURN(status, false);

    if (!UsdMayaWriteUtil::WriteArrayAttrsToInstancer(
            inputPointsData, instancer, _numPrototypes, usdTime,
            _GetSparseValueWriter())) {
        return false;
    }

    // Load the completed point instancer to compute and set its extent.
    instancer.GetPrim().GetStage()->Load(instancer.GetPath());
    VtArray<GfVec3f> extent(2);
    if (instancer.ComputeExtentAtTime(&extent, usdTime, usdTime)) {
        _SetAttribute(instancer.CreateExtentAttr(), &extent, usdTime);
    }

    return true;
}