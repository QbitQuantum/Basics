void ChargesApp::update()
{
	mFps = getAverageFps();

	// Update device
	if ( mLeap && mLeap->isConnected() )
	{
		mLeap->update();
	}

	vector< int32_t > currentFingersIds;

	for ( const std::pair< int32_t, LeapSdk::Hand > hand : mHands )
	{
		const LeapSdk::FingerMap &fingers = hand.second.getFingers();
		for ( const auto &fkv : fingers )
		{
			int32_t id = fkv.first;
			const LeapSdk::Finger &finger = fkv.second;

			currentFingersIds.push_back( id );

			// new finger?
			if ( mActiveFingers.find( id ) == mActiveFingers.end() )
			{
				mActiveFingers[ id ] = mTimestamp;
				mEffectCharge.addCursor( id, 0.f, 0.f, 1.f ); // init with (0, 0), will be updated below
			}

			// update finger
			const LeapSdk::ScreenMap &screens = mLeap->getScreens();
			if ( screens.begin() != screens.end() )
			{
				mActiveFingers[ id ] = mTimestamp;

				const LeapSdk::Screen &screen = screens.begin()->second;
				Vec3f normPos;
				screen.intersects( finger, normPos, true, 1.5f ); // normalized screen coordinates with 1.5 clamp ratio
				Vec2f fingertip = normPos.xy() * Vec2f( mFbo.getSize() );

				Vec3f screenPos;
				screen.intersects( finger, screenPos, false, 1.5f ); // screen coordinates with 1.5 clamp ratio
				float d = screenPos.distance( finger.getPosition() );
				const float dMin = 50.f;
				const float dMax = 500.f;
				const float sMin = 1.f;
				const float sMax = 100.f;
				d = math< float >::clamp( d, dMin, dMax );
				float strength = lmap( d, dMin, dMax, sMax, sMin );

				mEffectCharge.updateCursor( id, fingertip.x, fingertip.y, strength );
			}
		}
	}

	// erase disappeared fingers
	int64_t disappearThr = mFingerDisapperanceThreshold * 1000000;
	for ( auto it = mActiveFingers.begin(); it != mActiveFingers.end(); )
	{
		int32_t id = it->first;
		if ( find( currentFingersIds.begin(), currentFingersIds.end(), id ) == currentFingersIds.end() )
		{
			// seen earlier than the threshold?
			if ( mTimestamp - it->second > disappearThr )
			{
				mEffectCharge.removeCursor( id );
				it = mActiveFingers.erase( it );
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}
}