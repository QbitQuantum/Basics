void
CountsVisitor::apply(osg::Transform& node)
{
    pushStateSet(node.getStateSet());

    if (dynamic_cast<osgSim::DOFTransform*>(&node) != NULL)
    {
        _dofTransforms++;
        osg::ref_ptr<osg::Object> rp = (osg::Object*)&node;
        _uDofTransforms.insert(rp);
    }
    else
    {
        _transforms++;
        osg::ref_ptr<osg::Object> rp = (osg::Object*)&node;
        _uTransforms.insert(rp);
    }
    _totalChildren += node.getNumChildren();
    apply(node.getStateSet());

    if (++_depth > _maxDepth)
        _maxDepth = _depth;
    traverse((osg::Node&)node);
    _depth--;

    popStateSet();
}