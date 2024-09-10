void FrameData::setModelRotation(  const eq::Vector3f& rotation )
{
    _modelRotation = eq::Matrix4f();
    _modelRotation.rotate_x( rotation.x( ));
    _modelRotation.rotate_y( rotation.y( ));
    _modelRotation.rotate_z( rotation.z( ));
    setDirty( DIRTY_CAMERA );
}