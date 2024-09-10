void
ShaderGenerator::duplicateSharedNode(osg::Node& node)
{
    if ( node.getNumParents() > 1 )
    {
        for(int i=1; i<(int)node.getNumParents(); ++i)
        {
            osg::Group* parent = node.getParent(i);
            osg::Node* replicant = osg::clone(
                &node, 
                osg::CopyOp::DEEP_COPY_NODES | osg::CopyOp::DEEP_COPY_DRAWABLES | osg::CopyOp::DEEP_COPY_ARRAYS);
            parent->replaceChild(&node, replicant);
        }
    }
}