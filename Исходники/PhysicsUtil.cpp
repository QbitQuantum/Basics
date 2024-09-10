void GeometryDataCollector::apply( osg::Transform& transform )
{
    osg::Matrix matrix;
    if ( !matrixStack.empty() ) matrix = matrixStack.back();
    transform.computeLocalToWorldMatrix( matrix, this );

    pushMatrix( matrix );
    traverse( transform );
    popMatrix();
}