/* static */
GfMatrix4d
GusdPrimWrapper::computeTransform( 
        const UsdPrim&              prim,
        UsdTimeCode                 time,
        const UT_Matrix4D&          houXform,
        const GusdSimpleXformCache& xformCache ) {

    // We need the transform into the prims space.
    // If the prim is in a hierarchy that we have written on this frame, 
    // its transform will be in the xformCache. Otherwise, we can read it 
    // from the global cache. 
    //
    // The transform cache is necessary because the gobal cache 
    // will only contain transform that we read from the stage and 
    // not anything that we have modified.

    UT_Matrix4D primXform;
    auto it = xformCache.find( prim.GetPath() );
    if( it != xformCache.end() ) {
        primXform = it->second;
    }
    else if( !GusdUSD_XformCache::GetInstance().GetLocalToWorldTransform( 
                        prim,
                        time,
                        primXform )) {
        TF_WARN( "Failed to get transform for %s.", prim.GetPath().GetText() );
        primXform.identity();
    }
    return GusdUT_Gf::Cast( houXform ) / GusdUT_Gf::Cast( primXform );
}