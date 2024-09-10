bool
SpatialReference::createWorldToLocal(const osg::Vec3d& xyz, osg::Matrixd& out_world2local ) const
{
    osg::Matrixd local2world;
    if ( !createLocalToWorld(xyz, local2world) )
        return false;
    out_world2local.invert(local2world);
    return true;
}