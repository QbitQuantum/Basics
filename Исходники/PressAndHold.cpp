	void PressAndHold::updateFingerPosition(const Point2f &newPosition)
	{
		float dx	= position.getX() - newPosition.getX();
		float dy	= position.getY() - newPosition.getY();
		float d		= sqrt((dx * dx) + (dy * dy));
	
		if(d >= THRESHOLD)
		{
			markedForDelete = true;
		}
	}