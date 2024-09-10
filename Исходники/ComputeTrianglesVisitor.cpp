void ComputeTrianglesVisitor::apply( osg::Transform& node )
{
    osg::Matrix matrix = _matrixStack.back();
    node.computeLocalToWorldMatrix( matrix, this );
    
    _matrixStack.push_back( matrix );
    traverse( node );
    _matrixStack.pop_back();
}