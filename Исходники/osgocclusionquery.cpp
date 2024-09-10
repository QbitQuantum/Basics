void
OcclusionQueryVisitor::addOQN( osg::Node& node )
{
    VertexCounter vc( _occluderThreshold );
    node.accept( vc );
    if (vc.exceeded())
    {
        // Insert OQN(s) above this node.
        unsigned int np = node.getNumParents();
        while (np--)
        {
            osg::Group* parent = dynamic_cast<osg::Group*>( node.getParent( np ) );
            if (parent != NULL)
            {
                osg::ref_ptr<osg::OcclusionQueryNode> oqn = new osg::OcclusionQueryNode();
                oqn->addChild( &node );
                parent->replaceChild( &node, oqn.get() );

                oqn->setName( getNextOQNName() );
                // Set all OQNs to use the same query StateSets (instead of multiple copies
                //   of the same StateSet) for efficiency.
                oqn->setQueryStateSet( _state.get() );
                oqn->setDebugStateSet( _debugState.get() );
            }
        }
    }
}