void WiimoteTracker::wiimoteEventCallback(Misc::CallbackData* cbData)
	{
	/* Read the current instantaneous acceleration vector: */
	Vector newAcceleration=wiimote->getAcceleration(0);
	
	/* Update the filtered acceleration vector: */
	if(firstEvent)
		acceleration=newAcceleration;
	else
		{
		Vector da=newAcceleration-lastAcceleration;
		Scalar trust=Math::exp(-Geometry::sqr(da)*Scalar(50))*Scalar(0.2);
		acceleration+=(newAcceleration-acceleration)*trust;
		}
	lastAcceleration=newAcceleration;
	
	/* Calculate an intermediate rotation based on the filtered acceleration vector: */
	Vector previousY=wiipos.getDirection(1);
	Scalar yaw=Math::acos(previousY[1]/Math::sqrt(Math::sqr(previousY[0])+Math::sqr(previousY[1])));
	if(previousY[0]>Scalar(0))
		yaw=-yaw;
	Scalar axz=Math::sqrt(Math::sqr(acceleration[0])+Math::sqr(acceleration[2]));
	Scalar roll=Math::acos(acceleration[2]/axz);
	if(acceleration[0]>Scalar(0))
		roll=-roll;
	Scalar pitch=Math::acos(axz/Math::sqrt(Math::sqr(acceleration[1])+Math::sqr(axz)));
	if(acceleration[1]<Scalar(0))
		pitch=-pitch;
	Transform::Rotation wiirot=Transform::Rotation::rotateZ(yaw);
	wiirot*=Transform::Rotation::rotateX(pitch);
	wiirot*=Transform::Rotation::rotateY(roll);
	
	/* Update the wiimote's orientation based on the acceleration vector only: */
	wiipos=Transform(wiipos.getTranslation(),wiirot);
	
	/* Store the IR camera targets: */
	int numValidTargets=0;
	for(int i=0;i<4;++i)
		{
		pixelValids[i]=wiimote->getIRTarget(i).valid;
		if(pixelValids[i])
			{
			for(int j=0;j<2;++j)
				pixels[i][j]=Scalar(wiimote->getIRTarget(i).pos[j]);
			++numValidTargets;
			}
		}
	
	if(numValidTargets>0)
		{
		if(numValidTargets==4)
			{
			/* Project the "up" vector into camera space: */
			typedef Geometry::Vector<CameraFitter::Scalar,2> PVector;
			PVector vy(acceleration[0],acceleration[2]);
			vy.normalize();
			PVector vx=-Geometry::normal(vy);
			vx.normalize();
			
			/* Find the leftmost, rightmost, and topmost points: */
			Scalar minX,maxX,minY,maxY;
			int minXIndex,maxXIndex,minYIndex,maxYIndex;
			minX=minY=Math::Constants<Scalar>::max;
			maxX=maxY=Math::Constants<Scalar>::min;
			minXIndex=maxXIndex=minYIndex=maxYIndex=-1;
			for(int i=0;i<4;++i)
				{
				Scalar x=pixels[i]*vx;
				Scalar y=pixels[i]*vy;
				if(minX>x)
					{
					minX=x;
					minXIndex=i;
					}
				if(maxX<x)
					{
					maxX=x;
					maxXIndex=i;
					}
				if(minY>y)
					{
					minY=y;
					minYIndex=i;
					}
				if(maxY<y)
					{
					maxY=y;
					maxYIndex=i;
					}
				}
			
			/* Create the pixel-target map: */
			pixelMap[minXIndex]=0;
			pixelMap[maxYIndex]=1;
			pixelMap[maxXIndex]=2;
			for(int i=0;i<4;++i)
				if(i!=minXIndex&&i!=maxYIndex&&i!=maxXIndex)
					pixelMap[i]=3;
			}
		else
			{
			/* Project the target points into camera space using the previous camera position/orientation and match closest pairs: */
			wiiCamera.setTransform(wiipos);
			for(int pixelIndex=0;pixelIndex<4;++pixelIndex)
				if(pixelValids[pixelIndex])
					{
					Scalar minDist2=Geometry::sqrDist(pixels[pixelIndex],wiiCamera.project(0));
					int minIndex=0;
					for(int i=1;i<4;++i)
						{
						Scalar dist2=Geometry::sqrDist(pixels[pixelIndex],wiiCamera.project(i));
						if(minDist2>dist2)
							{
							minDist2=dist2;
							minIndex=i;
							}
						}
					pixelMap[pixelIndex]=minIndex;
					}
			}
		
		/* Re-project the new pixel positions: */
		wiiCamera.setTransform(homeTransform);
		for(int i=0;i<4;++i)
			wiiCamera.invalidatePixel(i);
		for(int i=0;i<4;++i)
			if(pixelValids[i])
				wiiCamera.setPixel(pixelMap[i],pixels[i]);
		wiiCamera.setTransform(homeTransform);
		wiiCameraMinimizer.minimize(wiiCamera);
		
		if(firstEvent)
			wiipos=wiiCamera.getTransform();
		else
			{
			/* Filter the reconstructed camera transformation: */
			Transform deltaWP=Geometry::invert(wiipos);
			deltaWP.leftMultiply(wiiCamera.getTransform());
			Vector t=deltaWP.getTranslation();
			t*=Scalar(0.05);
			Vector r=deltaWP.getRotation().getScaledAxis();
			r*=Scalar(0.05);
			deltaWP=Transform(t,Transform::Rotation::rotateScaledAxis(r));
			wiipos.leftMultiply(deltaWP);
			}
		}
	wiipos.renormalize();
	firstEvent=false;
	
	if(wiimote->getButtonState(Wiimote::BUTTON_HOME))
		wiipos=homeTransform;
	
	if(reportEvents)
		{
		/* Update the VR device state: */
		for(int i=0;i<13;++i)
			setButtonState(i,wiimote->getButtonState(i));
		for(int i=0;i<2;++i)
			setValuatorState(i,wiimote->getJoystickValue(i));
		Vrui::VRDeviceState::TrackerState ts;
		ts.positionOrientation=PositionOrientation(wiipos);
		ts.linearVelocity=Vrui::VRDeviceState::TrackerState::LinearVelocity::zero;
		ts.angularVelocity=Vrui::VRDeviceState::TrackerState::AngularVelocity::zero;
		setTrackerState(0,ts);
		}
	}