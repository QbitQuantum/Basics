void ComputeCylinderVisitor::apply( osg::Transform & transform )
{
    osg::Matrix matrix;

    if( !stack.empty() )
    {
        matrix = stack.back();
    }

    transform.computeLocalToWorldMatrix( matrix, this );

    pushMatrix( matrix );

    traverse( transform );

    popMatrix();
}