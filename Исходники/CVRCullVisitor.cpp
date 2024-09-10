void CVRCullVisitor::apply(osg::Transform& node)
{
    bool status = _cullingStatus;
    bool firstStatus = _firstCullStatus;

    if(isCulled(node))
    {
        _firstCullStatus = firstStatus;
        _cullingStatus = status;
        return;
    }

    // push the culling mode.
    pushCurrentMask();

    // push the node's state.
    StateSet* node_state = node.getStateSet();
    if(node_state)
        pushStateSet(node_state);

    ref_ptr<RefMatrix> matrix = createOrReuseMatrix(*getModelViewMatrix());
    node.computeLocalToWorldMatrix(*matrix,this);
    pushModelViewMatrix(matrix.get(),node.getReferenceFrame());

    handle_cull_callbacks_and_traverse(node);

    popModelViewMatrix();

    // pop the node's state off the render graph stack.    
    if(node_state)
        popStateSet();

    // pop the culling mode.
    popCurrentMask();

    _firstCullStatus = firstStatus;
    _cullingStatus = status;
}