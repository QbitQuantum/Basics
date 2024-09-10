/* ging methods */
void CinderOpenNISkeleton::debugDrawLabels( Font font, ci::Rectf depthArea )
{

	// Apply scale based on window size, vs dimensions of depth image ( will be 320 or 640 )
	ci::Vec2i inputSize = CinderOpenNISkeleton::getDimensions();
	ci::Vec3f depthMapScale = ci::Vec3f( depthArea.getWidth() / inputSize.x, depthArea.getHeight() / inputSize.y, 0.5f );

	for (int i = 0; i < maxUsers; ++i)
	{
		// Do the labels first
		XnPoint3D userCenterOfMass;
		mUserGenerator.GetCoM(currentUsers[i], userCenterOfMass);
		mDepthGenerator.ConvertRealWorldToProjective(1, &userCenterOfMass, &userCenterOfMass);

		// Scale and place based on center of 'depthArea' rectangle
		ci::Vec2i labelPosition = ci::Vec2i(depthArea.getX1() + depthMapScale.x*userCenterOfMass.X, depthArea.getY1() + depthMapScale.y*userCenterOfMass.Y);

		glColor4f(1.0f-Colors[i%nColors][0],
				  1.0f-Colors[i%nColors][1],
				  1.0f-Colors[i%nColors][2], 1);


		if ( mUserGenerator.GetSkeletonCap().IsTracking(currentUsers[i]) ) { // Is being tracked
			gl::drawString("Tracking", labelPosition, Color::white(), font );
		} else if ( mUserGenerator.GetSkeletonCap().IsCalibrating(currentUsers[i]) ) { // Is calibrating
			gl::drawString("Calibrating", labelPosition, Color::white(), font );
		} else { // Still waiting for intial pose
			gl::drawString("Waiting for Pose", labelPosition, Color::white(), font );
		}
	}
}