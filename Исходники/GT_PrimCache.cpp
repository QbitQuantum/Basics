UT_IntrusivePtr<UT_CappedItem> 
CreateEntryFn::operator()( 
    const UsdPrim &prim, 
    UsdTimeCode time, 
    GusdPurposeSet purposes,
    bool skipRoot ) const 
{ 

    // Build a cache entry for a USD Prim. A cache entry contains a GT_Primitive
    // that can be used to draw the usd prim. 
    //
    // Handle 3 different cases differently. 
    //
    // USD gprims (leaves in the hierarchy) are just converted to GT_Primitives. 
    //
    // For USD native instances, find the instance's master or the prim in
    // master corresponding to an instance proxy, and recurse on that. This way
    // each instance should share a cache with its master.
    //
    // Any other USD primitive represents a branch of the USD hierarchy. Find 
    // all the instances and leaves in this branch and build a GT_PrimCollect 
    // that represent the branch.
    //
    // The viewport doesn't seem to like nested collections very much. So we 
    // use a refiner to flatten the collections.
    
    Refiner refiner;

    // Tell the wrapper classes that we are refining for the viewport. In this case we just load the geometry and color. No
    // other primvars. Also load curves as polylines.
    GT_RefineParms refineParms;
    refineParms.setPackedViewportLOD( true );

    bool isInstance = prim.IsInstance();
    bool isInstanceProxy = prim.IsInstanceProxy();
    if( isInstance || isInstanceProxy)
    {
        DBG( cerr << "Create prim cache for instance " << prim.GetPath() << " at " << time << endl; )