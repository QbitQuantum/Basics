void PUParticleSystem3D::calulateRotationOffset( void )
{
    if (_isMarkedForEmission)
    {
        // Use the uber particle system as centre of rotation and not the particle systems' own position.
        _rotationCentre = _parentParticleSystem->getDerivedPosition();
    }
    else
    {
        // Use its own position
        _rotationCentre = getDerivedPosition();
    }

    /** Use the derived orientation, which is the particle systems' own scenenode orientation,
        or the orientation of the uber particle system, if this particle system is emitted itself.
    */
    Quaternion latestOrientationInverse = _latestOrientation;
    latestOrientationInverse.inverse();
    _rotationOffset = getDerivedOrientation() * latestOrientationInverse;
}