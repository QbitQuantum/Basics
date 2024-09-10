UsdSkelSkeletonQuery
UsdSkel_CacheImpl::ReadScope::GetInheritedSkelQuery(const UsdPrim& prim) const
{
    _PrimToSkelQueryMap::const_accessor a;
    for(UsdPrim p = prim; p; p = p.GetParent()) {
        if(_cache->_skelQueryCache.find(a, p)) {
            return a->second;
        }
        if(prim.IsA<UsdSkelRoot>()) {
            break;
        }
    }
    return UsdSkelSkeletonQuery();
}