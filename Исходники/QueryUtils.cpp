void AddQueries::apply( osg::Geode& node )
{
    traverse( node );

    osgwTools::CountsVisitor cv;
    node.accept( cv );
    const unsigned int numVertices = cv.getVertices();
    const osg::BoundingBox& bb = node.getBoundingBox();
    addDataToNodePath( getNodePath(), numVertices, bb );
}