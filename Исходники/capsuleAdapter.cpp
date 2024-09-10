SdfPath
UsdImagingCapsuleAdapter::Populate(UsdPrim const& prim, 
                            UsdImagingIndexProxy* index,
                            UsdImagingInstancerContext const* instancerContext)

{
    index->InsertRprim(HdPrimTypeTokens->mesh,
                       prim,
                       GetShaderBinding(prim),
                       instancerContext);
    HD_PERF_COUNTER_INCR(UsdImagingTokens->usdPopulatedPrimCount);

    return prim.GetPath();
}