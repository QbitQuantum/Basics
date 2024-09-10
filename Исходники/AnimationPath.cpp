void AnimationPathCallback::update(osg::Node& node)
{
    AnimationPath::ControlPoint cp;
    if (_animationPath->getInterpolatedControlPoint(getAnimationTime(),cp))
    {
        AnimationPathCallbackVisitor apcv(cp,_pivotPoint,_useInverseMatrix);
        node.accept(apcv);
    }
}