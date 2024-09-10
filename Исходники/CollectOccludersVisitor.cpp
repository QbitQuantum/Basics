void CollectOccludersVisitor::apply(osg::Transform &node)
{
    if (isCulled(node))
        return;

    // push the culling mode.
    pushCurrentMask();

    ref_ptr<osg::RefMatrix> matrix = createOrReuseMatrix(*getModelViewMatrix());
    node.computeLocalToWorldMatrix(*matrix, this);
    pushModelViewMatrix(matrix.get(), node.getReferenceFrame());

    handle_cull_callbacks_and_traverse(node);

    popModelViewMatrix();

    // pop the culling mode.
    popCurrentMask();
}