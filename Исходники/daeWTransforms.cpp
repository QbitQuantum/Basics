void daeWriter::apply( osg::Transform &node ) 
{
    osg::notify( osg::WARN ) << "some other transform type. Missing " << node.getNumChildren() << " children\n";
}