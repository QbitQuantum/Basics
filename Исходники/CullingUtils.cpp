void 
ProxyCullVisitor::apply(osg::Transform& node)
{
    //OE_INFO << "Transform!" << std::endl;

    if ( isCulledByProxyFrustum(node) )
        return;

    _cv->pushOntoNodePath( &node);

    _cv->pushCurrentMask();
    osg::StateSet* node_state = node.getStateSet();
    if (node_state) _cv->pushStateSet(node_state);

    // push the current proxy data:
    osg::Polytope savedF  = _proxyFrustum;
    osg::Matrix   savedMV = _proxyModelViewMatrix;

    // calculate the new proxy frustum:
    node.computeLocalToWorldMatrix(_proxyModelViewMatrix, this);
    _proxyFrustum.setAndTransformProvidingInverse( _proxyProjFrustum, _proxyModelViewMatrix );

    osg::ref_ptr<osg::RefMatrix> matrix = createOrReuseMatrix(*_cv->getModelViewMatrix());
    node.computeLocalToWorldMatrix(*matrix,this);
    _cv->pushModelViewMatrix(matrix.get(), node.getReferenceFrame());

    // traverse children:
    handle_cull_callbacks_and_traverse(node);

    // restore the previous proxy frustum and MVM
    _proxyFrustum         = savedF;
    _proxyModelViewMatrix = savedMV;

    _cv->popModelViewMatrix();
    if (node_state) _cv->popStateSet();
    _cv->popCurrentMask();

    _cv->popFromNodePath();
}