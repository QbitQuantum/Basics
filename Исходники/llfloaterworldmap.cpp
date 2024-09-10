// virtual
void LLFloaterWorldMap::draw()
{
	// Hide/Show Mature Events controls
	childSetVisible("events_mature_icon", gAgent.canAccessMature());
	childSetVisible("events_mature_label", gAgent.canAccessMature());
	childSetVisible("event_mature_chk", gAgent.canAccessMature());

	childSetVisible("events_adult_icon", gAgent.canAccessMature());
	childSetVisible("events_adult_label", gAgent.canAccessMature());
	childSetVisible("event_adult_chk", gAgent.canAccessMature());
	bool adult_enabled = gAgent.canAccessAdult();
	if (!adult_enabled)
	{
		childSetValue("event_adult_chk", FALSE);
	}
	childSetEnabled("event_adult_chk", adult_enabled);

	// On orientation island, users don't have a home location yet, so don't
	// let them teleport "home".  It dumps them in an often-crowed welcome
	// area (infohub) and they get confused. JC
	LLViewerRegion* regionp = gAgent.getRegion();
	bool agent_on_prelude = (regionp && regionp->isPrelude());
	bool enable_go_home = gAgent.isGodlike() || !agent_on_prelude;
	childSetEnabled("Go Home", enable_go_home);

	updateLocation();
	
	LLTracker::ETrackingStatus tracking_status = LLTracker::getTrackingStatus(); 
	if (LLTracker::TRACKING_AVATAR == tracking_status)
	{
		childSetColor("avatar_icon", gTrackColor);
	}
	else
	{
		childSetColor("avatar_icon", gDisabledTrackColor);
	}

	if (LLTracker::TRACKING_LANDMARK == tracking_status)
	{
		childSetColor("landmark_icon", gTrackColor);
	}
	else
	{
		childSetColor("landmark_icon", gDisabledTrackColor);
	}

	if (LLTracker::TRACKING_LOCATION == tracking_status)
	{
		childSetColor("location_icon", gTrackColor);
	}
	else
	{
		if (mCompletingRegionName != "")
		{
			F64 seconds = LLTimer::getElapsedSeconds();
			double value = fmod(seconds, 2);
			value = 0.5 + 0.5*cos(value * 3.14159f);
			LLColor4 loading_color(0.0, F32(value/2), F32(value), 1.0);
			childSetColor("location_icon", loading_color);
		}
		else
		{
			childSetColor("location_icon", gDisabledTrackColor);
		}
	}

	// check for completion of tracking data
	if (mWaitingForTracker)
	{
		centerOnTarget(TRUE);
	}

	childSetEnabled("Teleport", (BOOL)tracking_status);
//	childSetEnabled("Clear", (BOOL)tracking_status);
	childSetEnabled("Show Destination", (BOOL)tracking_status || LLWorldMap::getInstance()->mIsTrackingUnknownLocation);
	childSetEnabled("copy_slurl", (mSLURL.size() > 0) );

	setMouseOpaque(TRUE);
	getDragHandle()->setMouseOpaque(TRUE);

	//RN: snaps to zoom value because interpolation caused jitter in the text rendering
	if (!mZoomTimer.getStarted() && mCurZoomVal != (F32)childGetValue("zoom slider").asReal())
	{
		mZoomTimer.start();
	}
	F32 interp = mZoomTimer.getElapsedTimeF32() / MAP_ZOOM_TIME;
	if (interp > 1.f)
	{
		interp = 1.f;
		mZoomTimer.stop();
	}
	mCurZoomVal = lerp(mCurZoomVal, (F32)childGetValue("zoom slider").asReal(), interp);
	F32 map_scale = 256.f*pow(2.f, mCurZoomVal);
	LLWorldMapView::setScale( map_scale );
	
	LLFloater::draw();
}