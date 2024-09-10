void FmodExMultiple3DSoundPlayerApp::update()
{
	
	
	//Update camera
	Vec3f camDirection = camCenter;
	camDirection.normalize();
	camEye = camInitialEye + camDistance * camDirection;
	cam.setViewDirection(camCenter);
	cam.setEyePoint(camEye);
	gl::setMatrices( cam );
	gl::rotate( sceneRotation );
	
	//Update 3D Sounds
	
	Vec3f up = cam.getWorldUp();
	up.invert();
	
	listenerUp.x = up.x;
	listenerUp.y = up.y; 
	listenerUp.z = up.z;
	listenerPos.x = camEye.x; 
	listenerPos.y = camEye.y;  
	listenerPos.z = camEye.z;
	//forward = camCenter - camEye;
	//forward.normalize();
	listenerForward.x = camCenter.x; 
	listenerForward.y = camCenter.y; 
	listenerForward.z = camCenter.z;
	sys->set3DListenerAttributes( 0, &listenerPos, &listenerVelocity, &listenerForward, &listenerUp);
	
	if(!player1.getIsPlaying())
		player1.play();
	
	if(!player2.getIsPlaying())
		player2.play();	
	
	player1.channel->set3DAttributes( &sound3DPosition1, &sound3DVelocity1);
	player2.channel->set3DAttributes( &sound3DPosition2, &sound3DVelocity2);
	
	//we update the fmod sound system
	sys->update();
	//FmodexUpdate();
	
}