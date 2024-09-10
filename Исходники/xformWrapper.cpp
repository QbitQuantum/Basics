bool GusdXformWrapper::
initUsdPrim(const UsdStagePtr& stage,
            const SdfPath& path,
            bool asOverride)
{
    bool newPrim = true;
    if( asOverride ) {
        UsdPrim existing = stage->GetPrimAtPath( path );
        if( existing ) {
            // Note that we are creating a Xformable rather than a Xform. 
            // If we are writing an overlay and the ROP sees a geometry packed prim,
            // we want to write just the xform. In that case we can use a xform
            // wrapper to write the xform on any prim type.
            m_usdXformForWrite = UsdGeomXformable(stage->OverridePrim( path ));
            newPrim = false;
        }
        else {
            m_usdXformForWrite = UsdGeomXform::Define( stage, path );

            // Make sure our ancestors have proper types.
            UsdPrim p = m_usdXformForWrite.GetPrim().GetParent();
            while( p && p.GetTypeName().IsEmpty() ) {
                UsdGeomXform::Define( stage, p.GetPath() );
                p = p.GetParent();
            } 
        }
    }
    else {
        m_usdXformForWrite = UsdGeomXform::Define( stage, path );
    }
    if( !m_usdXformForWrite || !m_usdXformForWrite.GetPrim().IsValid() ) {
        TF_WARN( "Unable to create %s xform '%s'.", newPrim ? "new" : "override", path.GetText() );
    }
    return bool(m_usdXformForWrite);
}