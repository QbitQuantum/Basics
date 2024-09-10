bool
GusdUSD_XformCache::GetLocalToWorldTransform(const UsdPrim& prim,
                                             UsdTimeCode time,
                                             UT_Matrix4D& xform)
{
    const auto info = GetXformInfo(prim);
    if(BOOST_UNLIKELY(!info))
        return false;

    // See if we can remap the time to for unvarying xforms.
    if(!time.IsDefault() && !info->WorldXformIsMaybeTimeVarying()) {
        /* XXX: we know we're not time varying, but that doesn't
           mean that we can key default, since there might still
           be a single varying value that we'd miss.
           Key off of time=0 instead.*/
        time = UsdTimeCode(0.0);
    }
    _VaryingKey key(GusdUSD_VaryingPropertyKey(prim, time));

    if(auto item = _worldXforms.findItem(key)) {
        xform = UTverify_cast<const _CappedXformItem*>(item.get())->xform;
        return true;
    }
    /* XXX: Race is possible when setting computed value,
       but it's preferable to have multiple threads compute the
       same thing than to cause lock contention.*/
    if(_GetLocalTransformation(prim, time, xform, info)) {
        if(BOOST_UNLIKELY(!info->HasParentXform())) {
            _worldXforms.addItem(key, UT_CappedItemHandle(
                                     new _CappedXformItem(xform)));
            return true;
        }
        UsdPrim parent = prim.GetParent();
        UT_ASSERT_P(parent);

        UT_Matrix4D parentXf;
        if(GetLocalToWorldTransform(parent, time, parentXf)) {
            xform *= parentXf;
            _worldXforms.addItem(
                key, UT_CappedItemHandle(new _CappedXformItem(xform)));
            return true;
        }
    }
    return false;
}