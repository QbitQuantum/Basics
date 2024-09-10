bool OgreNewtonFrameListener::frameStarted(const FrameEvent &evt)
{
	mKeyboard->capture();
	mMouse->capture();

	// ----------------------------------------
	// CAMERA CONTROLS
	// ----------------------------------------
	if ((mKeyboard->isKeyDown(OIS::KC_LSHIFT)) || (mKeyboard->isKeyDown(OIS::KC_RSHIFT)))
	{
		Vector3 trans, strafe, vec;
		Quaternion quat;

		quat = mCamera->getOrientation();

		vec = Vector3(0.0,0.0,-0.5);
		trans = quat * vec;

		vec = Vector3(0.5,0.0,0.0);
		strafe = quat * vec;

		mCamera->pitch( Degree(mMouse->getMouseState().Y.rel * -0.5) );
        mCamera->setFixedYawAxis(true);
		mCamera->yaw( Degree(mMouse->getMouseState().X.rel * -0.5) );

		if (mKeyboard->isKeyDown(OIS::KC_UP))
			mCamera->moveRelative(trans);

		if (mKeyboard->isKeyDown(OIS::KC_DOWN))
			mCamera->moveRelative(trans * -1.0);

		if (mKeyboard->isKeyDown(OIS::KC_LEFT))
			mCamera->moveRelative(strafe * -1.0);

		if (mKeyboard->isKeyDown(OIS::KC_RIGHT))
			mCamera->moveRelative(strafe);
	}


	// ----------------------------------------
	// DRAGGING!
	// ----------------------------------------

	if (!dragging)
	{

		//user pressing the left mouse button?
		if (mMouse->getMouseState().buttonDown(OIS::MB_Left))
		{
			// perform a raycast!
			// start at the camera, and go for 100 units in the Z direction.
			Ogre::Vector3 start, end;

			CEGUI::Point mouse = CEGUI::MouseCursor::getSingleton().getPosition();
			CEGUI::Renderer* rend = CEGUI::System::getSingleton().getRenderer();
	
			Ogre::Real mx,my;
			mx = mouse.d_x / rend->getWidth();
			my = mouse.d_y / rend->getHeight();
			Ogre::Ray camray = mCamera->getCameraToViewportRay(mx,my);

			start = camray.getOrigin();
			end = camray.getPoint( 100.0 );

			OgreNewt::BasicRaycast* ray = new OgreNewt::BasicRaycast( m_World, start, end, true );
			OgreNewt::BasicRaycast::BasicRaycastInfo info = ray->getFirstHit();

			if (info.mBody)
			{
				// a body was found.  first let's find the point we clicked, in local coordinates of the body.
				

				// while dragging, make sure the body can't fall asleep.
				info.mBody->unFreeze();
				//info.mBody->setAutoFreeze(0);

				Ogre::Vector3 bodpos;
				Ogre::Quaternion bodorient;

				info.mBody->getPositionOrientation( bodpos, bodorient );

				// info.mDistance is in the range [0,1].
				Ogre::Vector3 globalpt = camray.getPoint( 100.0 * info.mDistance );
				Ogre::Vector3 localpt = bodorient.Inverse() * (globalpt - bodpos);

				// now we need to save this point to apply the spring force, I'm using the userData of the bodies in this example.
                // (where is it used? probably not needed here...)
#ifndef OGRENEWT_NO_OGRE_ANY
                info.mBody->setUserData( Ogre::Any(this) );
#else
				info.mBody->setUserData( this );
#endif

				// now change the force callback from the standard one to the one that applies the spring (drag) force.
				// this is an example of binding a callback to a member of a specific class.  in previous versions of OgreNewt you were
				// required to use a static member function fr all callbacks... but now through the fantastic FastDelegate library, you can
				// now use callbacks that are members of specific classes.  to do this, use the syntax shown below.  the "this" is a pointer
				// to the specific class, and the 2nd parameter is a pointer to the function you want to use.  you can do this for all
				// body callbacks (ForceAndTorque, Transform, addBuoyancyPlane).
				info.mBody->setCustomForceAndTorqueCallback<OgreNewtonFrameListener>( &OgreNewtonFrameListener::dragCallback, this );

				// save the relevant drag information.
				dragBody = info.mBody;
				dragDist = (100.0 * info.mDistance);
				dragPoint = localpt;

				dragging = true;
			}

			delete ray;

		}

		if (mDragLine)
			remove3DLine();
	}
	else
	{
		// currently dragging!
		if (!mMouse->getMouseState().buttonDown(OIS::MB_Left))
		{
			// no longer holding mouse button, so stop dragging!
			// remove the special callback, and put it back to standard gravity.
			dragBody->setStandardForceCallback();
			//dragBody->setAutoFreeze(1);

			dragBody = NULL;
			dragPoint = Ogre::Vector3::ZERO;
			dragDist = 0.0;

			dragging = false;
		}
	}



    OgreNewt::Debugger& debug(m_World->getDebugger());
    if (mKeyboard->isKeyDown(OIS::KC_F3))
    {
        debug.showDebugInformation();
        debug.startRaycastRecording();
        debug.clearRaycastsRecorded();
    }
    else
    {
        debug.hideDebugInformation();
        debug.clearRaycastsRecorded();
        debug.stopRaycastRecording();
    }



    if (mKeyboard->isKeyDown(OIS::KC_T))
        m_World->setThreadCount( m_World->getThreadCount() % 2 + 1);


	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

	return true;
}