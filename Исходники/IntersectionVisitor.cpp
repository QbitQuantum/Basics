void IntersectionVisitor::apply(osg::Transform& transform)
{
    if (!enter(transform)) return;

    osg::ref_ptr<osg::RefMatrix> matrix = _modelStack.empty() ? new osg::RefMatrix() : new osg::RefMatrix(*_modelStack.back());
    transform.computeLocalToWorldMatrix(*matrix,this);

    pushModelMatrix(matrix.get());

    // now push an new intersector clone transform to the new local coordinates
    push_clone();

    traverse(transform);
    
    // pop the clone.
    pop_clone();
    
    popModelMatrix();

    // tidy up an cached cull variables in the current intersector.
    leave();
}