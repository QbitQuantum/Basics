bool
UsdRelationship::GetTargets(SdfPathVector* targets) const
{
    TRACE_FUNCTION();

    UsdStage *stage = _GetStage();
    PcpErrorVector pcpErrors;
    std::vector<std::string> otherErrors;
    PcpTargetIndex targetIndex;
    {
        // Our intention is that the following code requires read-only
        // access to the PcpCache, so use a const-ref.
        const PcpCache& pcpCache(*stage->_GetPcpCache());
        // In USD mode, Pcp does not cache property indexes, so we
        // compute one here ourselves and use that.  First, we need
        // to get the prim index of the owning prim.
        const PcpPrimIndex &primIndex = _Prim()->GetPrimIndex();
        // PERFORMANCE: Here we can't avoid constructing the full property path
        // without changing the Pcp API.  We're about to do serious
        // composition/indexing, though, so the added expense may be neglible.
        const PcpSite propSite(pcpCache.GetLayerStackIdentifier(), GetPath());
        PcpPropertyIndex propIndex;
        PcpBuildPrimPropertyIndex(propSite.path, pcpCache, primIndex,
                                  &propIndex, &pcpErrors);
        PcpBuildTargetIndex(propSite, propIndex, SdfSpecTypeRelationship,
                            &targetIndex, &pcpErrors);
    }

    targets->swap(targetIndex.paths);
    if (!targets->empty() && _Prim()->IsInMaster()) {
        Usd_PrimDataConstPtr master = get_pointer(_Prim());
        while (!master->IsMaster()) { 
            master = master->GetParent();  
        }
        
        // Paths that point to an object under the master's source prim index
        // are internal to the master and need to be translated to either
        // the master or instance we're currently looking at.
        const SdfPath& masterSourcePrimIndexPath = 
            master->GetSourcePrimIndex().GetPath();

        if (GetPrim().IsInMaster()) {
            // Translate any paths that point to an object at or under the
            // source prim index to our master.
            for (SdfPath& target : *targets) {
                target = target.ReplacePrefix(
                    masterSourcePrimIndexPath, master->GetPath());
            }
        }
        else if (GetPrim().IsInstanceProxy()) {
            // Translate any paths that point to an object at or under the
            // source prim index to our instance.
            UsdPrim instance = GetPrim();
            while (!instance.IsInstance()) { 
                instance = instance.GetParent(); 
            }

            for (SdfPath& target : *targets) {
                target = target.ReplacePrefix(
                    masterSourcePrimIndexPath, instance.GetPath());
            }
        }
    }

    // TODO: handle errors
    const bool hasErrors = !(pcpErrors.empty() && otherErrors.empty());
    if (hasErrors) {
        stage->_ReportErrors(
            pcpErrors, otherErrors,
            TfStringPrintf("Getting targets for relationship <%s>",
                           GetPath().GetText()));
    }

    return !hasErrors;
}