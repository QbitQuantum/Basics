bool
GusdGU_PackedUSD::unpackGeometry(
    GU_Detail &destgdp,
    const char* primvarPattern
#if SYS_VERSION_FULL_INT >= 0x11000000
    , const UT_Matrix4D *transform
#endif
) const
{
    UsdPrim usdPrim = getUsdPrim();

    if( !usdPrim )
    {
        TF_WARN( "Invalid prim found" );
        return false;
    }

#if SYS_VERSION_FULL_INT < 0x11000000
    UT_Matrix4D xform(1);
    const GU_PrimPacked *prim = getPrim();
    if( prim ) {
        prim->getFullTransform4(xform);
    }
#endif

    GT_RefineParms      rparms;
    // Need to manually force polysoup to be turned off.
    rparms.setAllowPolySoup( false );

    if (primvarPattern) {
        rparms.set("usd:primvarPattern", primvarPattern);
    }

    GT_PrimitiveHandle gtPrim;

    DBG( cerr << "GusdGU_PackedUSD::unpackGeometry: " << usdPrim.GetTypeName() << ", " << usdPrim.GetPath() << endl; )