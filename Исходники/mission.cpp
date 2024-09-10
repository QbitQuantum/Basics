void Mission::ThirdPersonCamera::onUpdateActivity(float dt)
{
    assert( _scene );

	dt /= _scene->getTimeSpeed();

    _positionModeTimeout -= dt;
    _positionModeTimeout = _positionModeTimeout < 0 ? 0 : _positionModeTimeout;

    // retrieve action channels
    ActionChannel* headLeft  = Gameplay::iGameplay->getActionChannel( iaHeadLeft );
    ActionChannel* headRight = Gameplay::iGameplay->getActionChannel( iaHeadRight );
    ActionChannel* headUp    = Gameplay::iGameplay->getActionChannel( iaHeadUp );
    ActionChannel* headDown  = Gameplay::iGameplay->getActionChannel( iaHeadDown );
    ActionChannel* zoomIn    = Gameplay::iGameplay->getActionChannel( iaZoomIn );
    ActionChannel* zoomOut   = Gameplay::iGameplay->getActionChannel( iaZoomOut );    
    ActionChannel* changeTarget   = Gameplay::iGameplay->getActionChannel( iaWLO );  



	// aircraft camera
	//if (false && changeTarget->getTrigger()) {
 //       if( dynamic_cast<Jumper*>( _target ) )
 //       {
 //           Jumper* j = dynamic_cast<Jumper*>( _target );

	//		if (j->getAirplane()) {
	//			_target = j->getAirplane();
	//		} else if (j->getParent()) {
	//			_target = j->getParent();
	//		}
	//	}
	//}

    if( _positionMode )
    {
        // field of view
        _cameraFOV = ( 60.0f - 55.0f * ( zoomIn->getAmplitude() ) ) * CAMERA_FOV_MULTIPLIER;

        // target position
        Matrix4f targetPose( 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 );
        if( _target ) targetPose = _target->getPose();    
        Vector3f targetPos( targetPose[3][0], targetPose[3][1], targetPose[3][2] );

        if( dynamic_cast<Jumper*>( _target ) )
        {
            Jumper* j = dynamic_cast<Jumper*>( _target );
            j->getClump()->getFrame()->getLTM();
            engine::IFrame* backBone = Jumper::getBackBone( j->getClump() );
            targetPos = backBone->getPos();
        }

        // camera direction
        Vector3f cameraAt = _cameraPos - targetPos;
        cameraAt.normalize();        

        // camera right
        Vector3f cameraRight; 
        cameraRight.cross( Vector3f(0,1,0), cameraAt );
        cameraRight.normalize();

        // camera up
        Vector3f cameraUp;
        cameraUp.cross( cameraAt, cameraRight );
        cameraUp.normalize();

        // camera matrix
        _cameraMatrix.set( 
            cameraRight[0], cameraRight[1], cameraRight[2], 0.0f,
            cameraUp[0], cameraUp[1], cameraUp[2], 0.0f,
            cameraAt[0], cameraAt[1], cameraAt[2], 0.0f,
            _cameraPos[0], _cameraPos[1], _cameraPos[2], 1.0f
        );
    }
    else
    {
        // camera offset 
        _cameraDistance -= dt * 500.0f * zoomIn->getAmplitude();
        _cameraDistance += dt * 500.0f * zoomOut->getAmplitude();
        if( _cameraDistance < TPSM_MINIMAL_DISTANCE ) _cameraDistance = TPSM_MINIMAL_DISTANCE;

        // rotate camera    
        _cameraTurn += 180 * dt * headLeft->getAmplitude();
        _cameraTurn -= 180 * dt * headRight->getAmplitude();
        _cameraTilt += 180 * dt * headUp->getAmplitude();
        _cameraTilt -= 180 * dt * headDown->getAmplitude();
        if( _cameraTilt < -89 ) _cameraTilt = -89;
        if( _cameraTilt > 89 ) _cameraTilt = 89;

        Matrix4f targetPose( 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 );
        if( _target ) targetPose = _target->getPose();
    
        Vector3f targetPos( targetPose[3][0], targetPose[3][1], targetPose[3][2] );
        Vector3f targetOffset( 0,150,0 );
    
        if( dynamic_cast<Jumper*>( _target ) )
        {
            Jumper* j = dynamic_cast<Jumper*>( _target );
            j->getClump()->getFrame()->getLTM();
            engine::IFrame* backBone = Jumper::getBackBone( j->getClump() );
            targetPos = backBone->getPos();
            targetOffset.set( 0,75, 0 );
        }

        // calculate camera matrix        
        _cameraMatrix.set( 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 );
        _cameraMatrix = Gameplay::iEngine->rotateMatrix( _cameraMatrix, Vector3f( 1,0,0 ), _cameraTilt );
        _cameraMatrix = Gameplay::iEngine->rotateMatrix( _cameraMatrix, Vector3f( 0,1,0 ), _cameraTurn );
        Vector3f at( _cameraMatrix[2][0], _cameraMatrix[2][1], _cameraMatrix[2][2] );

        // possible camera position
        Vector3f cameraPos = targetPos + targetOffset + at * _cameraDistance;

        // clip camera distance
        float clipDistance = _cameraDistance;
        if( _scene->clipCameraRay( targetPos, cameraPos, clipDistance ) )
        {
            _cameraDistance = clipDistance;
            cameraPos = targetPos + targetOffset + at * _cameraDistance;
        }        
        
        // finalize camera matrix (translation component)
        _cameraMatrix = Gameplay::iEngine->translateMatrix( _cameraMatrix, cameraPos );
    }

    // camera is actual now
    Gameplay::iEngine->getDefaultCamera()->setFOV( _cameraFOV );
    Gameplay::iEngine->getDefaultCamera()->getFrame()->setMatrix( _cameraMatrix );
    _scene->getScenery()->happen( this, EVENT_CAMERA_IS_ACTUAL );
    if( _scene->getTopMode() ) _scene->getTopMode()->happen( this, EVENT_CAMERA_IS_ACTUAL );

    // RT-RS pass
    bool flares = ( _scene->getLocation()->getWeather() == ::wtSunny ) || ( _scene->getLocation()->getWeather() == ::wtVariable );
    Gameplay::iGameplay->getRenderTarget()->render( _scene, _cameraMatrix, _cameraFOV, flares, false );
    // GUI
    Gameplay::iEngine->getDefaultCamera()->beginScene( 0, Vector4f( 0,0,0,0 ) );    
    if( _scene->isHUDEnabled() ) Gameplay::iGui->render();
    Gameplay::iEngine->getDefaultCamera()->endScene();
    // present result
    Gameplay::iEngine->present();
}