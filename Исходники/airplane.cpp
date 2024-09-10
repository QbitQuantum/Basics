void Airplane::onUpdateActivity(float dt)
{
    if( _roughMode )
    {
        _clump->getAnimationController()->advance( dt * _desc.animationSpeed );
        _clump->getFrame()->getLTM();

        // landing mode
        if( _landingMode && _clump->getFrame()->getPos()[1] > _desc.lastAltitude )
        {
            // damp landing
            float damp = 1.0f;
            float dampAltitude = 1000.0f;
            if( _restAltitude < dampAltitude )
            {
                damp = _restAltitude / dampAltitude;
                if( damp < 0 ) damp = 0;
            }

            _restAltitude -= _desc.loweringSpeed * dt * damp;
            _clump->getFrame()->translate( Vector3f( 0.0f, -_desc.loweringSpeed * dt * damp, 0.0f ) );
        }

        // calculate velocity
        Vector3f currPoint = _propellerFrame->getPos();
        _velocity = ( currPoint - _prevPoint ) / ( dt );
        _prevPoint = currPoint;
    }

    // place plane on to waypoint
    if( _desc.waypoints.size() )
    {
        //getCore()->logMessage( "%3.3f", _waypointFactor );

        while( _waypointFactor > 1 )
        {
            _waypointFactor -= 1;
        }

        if( _waypointId < _desc.waypoints.size() - 1 )
        {
            // setup airplane between waypoints
            Vector3f p;
            p = _desc.waypoints[_waypointId].pos * ( 1 - _waypointFactor ) +
                _desc.waypoints[_waypointId+1].pos * _waypointFactor;
            Vector3f z;
            z = _desc.waypoints[_waypointId].dir * ( 1 - _waypointFactor ) +
                _desc.waypoints[_waypointId+1].dir * _waypointFactor;
            z.normalize();
            Vector3f x;
            x.cross( Vector3f(0,1,0), z );
            x.normalize();
            Vector3f y;
            y.cross( z, x );
            y.normalize();
            _clump->getFrame()->setMatrix( Matrix4f(
                                               x[0], x[1], x[2], 0.0f,
                                               y[0], y[1], y[2], 0.0f,
                                               z[0], z[1], z[2], 0.0f,
                                               p[0], p[1], p[2], 1.0f
                                           ) );
            _clump->getFrame()->getLTM();
        }
        else
        {
            // setup airplane on to last waypoint
            Vector3f p;
            p = _desc.waypoints[_waypointId].pos;
            Vector3f z;
            z = _desc.waypoints[_waypointId].dir;
            Vector3f x;
            x.cross( Vector3f(0,1,0), z );
            x.normalize();
            Vector3f y;
            y.cross( z, x );
            y.normalize();
            _clump->getFrame()->setMatrix( Matrix4f(
                                               x[0], x[1], x[2], 0.0f,
                                               y[0], y[1], y[2], 0.0f,
                                               z[0], z[1], z[2], 0.0f,
                                               p[0], p[1], p[2], 1.0f
                                           ) );
            _clump->getFrame()->getLTM();
        }

        // calculate velocity
        Vector3f currPoint = _propellerFrame->getPos();
        _velocity = ( currPoint - _prevPoint ) / ( dt );
        _prevPoint = currPoint;
    }

    // update sound
    if( !_propellerSound->isPlaying() )
    {
        _propellerSound->play();
        _propellerSound->setGainLimits( 0.0f, 1.0f );
    }
    _propellerSound->place( _propellerFrame->getPos(), _velocity );
    if( Gameplay::iGameplay->pitchShiftIsEnabled() )
    {
        _propellerSound->setPitchShift( _scene->getTimeSpeed() );
    }
}