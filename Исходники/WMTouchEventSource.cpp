	void WMTouchEventSource::touchUp(TOUCHINPUT *ti)
	{
		assert(ti);

		if(eventCallback != NULL) 
		{
			Point2f p = convert(ti);
			eventCallback(ti->dwID, p.getX(),p.getY(), FingerEventArgs::EventType::FINGER_REMOVED);
		}
	}