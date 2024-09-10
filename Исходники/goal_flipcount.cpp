void GoalFlipCount::onUpdateActivity(float dt)
{
    // base behaviour
    Goal::onUpdateActivity( dt );

    // accumulate tracking data
    if( !_player->getFreefallActor()->isSleeping() )
    {
        if( _captureIsActive )
        {
            Vector3f currAt    = _player->getClump()->getFrame()->getAt();
            Vector3f currRight = _player->getClump()->getFrame()->getRight();
            currAt.normalize();
            currRight.normalize();;
            _angleAccumulator += fabs( ::calcAngle( _prevAt, currAt, currRight ) );
            _prevAt    = currAt;
            _prevRight = currRight;
        }
        else
        {
            _captureIsActive  = true;
            _prevAt           = _player->getClump()->getFrame()->getAt();
            _prevRight        = _player->getClump()->getFrame()->getRight();
            _prevAt.normalize();
            _prevRight.normalize();
        }
    }
}