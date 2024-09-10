void Jumper::StandingJump::update(float dt)
{
    updateAnimation( dt );
    _clump->getFrame()->getLTM();

    if( _actionTime < _blendTime ) return;

    if( _actionTime > _blendTime + ( FRAMETIME(245) - FRAMETIME(225) ) )
    {
        if( _phActor->isSleeping() )
        {
            Matrix4f sampleLTM = Jumper::getCollisionFF( _clump )->getFrame()->getLTM();
            _phActor->setGlobalPose( wrap( sampleLTM ) );
            _phActor->wakeUp();
            NxVec3 velH = wrap( _clump->getFrame()->getAt() );
            velH.normalize();
            velH *= 3.0f;
            NxVec3 velV = wrap( _clump->getFrame()->getUp() );
            velV.normalize();
            velV *= 1.5f;
            _phActor->setLinearVelocity( velH + velV );
            _jumper->initOverburdenCalculator( velH + velV );
        }
        else
        {
            _clump->getFrame()->setMatrix( _matrixConversion->convert( wrap( _phActor->getGlobalPose() ) ) );
        }
		if( _jumper->getSpinalCord()->modifier) _endOfAction = true;
    }

    if( _clump->getAnimationController()->isEndOfAnimation( 0 ) )
    {
        _endOfAction = true;
    }
}