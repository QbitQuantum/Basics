size_t
UsdMayaGLBatchRenderer::_ShapeHash(
    const UsdPrim& usdPrim, 
    const SdfPathVector& excludePrimPaths,
    const MDagPath& objPath )
{
    size_t hash( MObjectHandle(objPath.transform()).hashCode() );
    boost::hash_combine( hash, usdPrim );
    boost::hash_combine( hash, excludePrimPaths );

    return hash;
}