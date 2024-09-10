void Jumper::RunningJump::update(float dt)
{
    updateAnimation( dt );
    _clump->getFrame()->getLTM();

    if( _actionTime < _blendTime ) 
    {
        Vector3f dir = _clump->getFrame()->getAt();
        dir.normalize();
        _clump->getFrame()->setPos( _clump->getFrame()->getPos() + dir * dt * _vel );            
        return;
    }

    if( _phActor->isSleeping() )
    {
        // setup physics
        Matrix4f sampleLTM = Jumper::getCollisionFF( _clump )->getFrame()->getLTM();
        _phActor->setGlobalPose(PxTransform(wrap( sampleLTM )));
        _phActor->wakeUp();
        PxVec3 velH = wrap( _clump->getFrame()->getAt() );
        velH.normalize();
        velH *= _vel * 0.01f;
        PxVec3 velV = wrap( _clump->getFrame()->getUp() );
        velV.normalize();
        velV *= 1.5f;
        _phActor->setLinearVelocity( velH + velV + wrap(_clump->getFrame()->getAt() * 600.0f * dt)) ;
        _jumper->initOverburdenCalculator( velH + velV );


    }
    else
    {
        _clump->getFrame()->setMatrix( _matrixConversion->convert( wrap( _phActor->getGlobalPose() ) ) );
    }

    if( _clump->getAnimationController()->isEndOfAnimation( 0 ) )
    {
        _endOfAction = true;
    }
}