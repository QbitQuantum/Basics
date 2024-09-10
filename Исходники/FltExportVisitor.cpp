void
FltExportVisitor::apply( osg::Transform& node )
{
    _firstNode = false;
    ScopedStatePushPop guard( this, node.getStateSet() );

    osgSim::DOFTransform* dof = dynamic_cast<osgSim::DOFTransform*>( &node );

    if (dof)
    {
        writeDegreeOfFreedom( dof);
    }

    writeMatrix( node.getUserData() );
    writeComment( node );
    writePushTraverseWritePop( node );
}