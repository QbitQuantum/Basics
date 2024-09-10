void
BuildTopologyVisitor::apply(osg::Transform& xform)
{
    osg::Matrix matrix;
    if (!_matrixStack.empty()) matrix = _matrixStack.back();
    xform.computeLocalToWorldMatrix(matrix, this);
    _matrixStack.push_back(matrix);
    traverse(xform);
    _matrixStack.pop_back();
}