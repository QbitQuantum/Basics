	/* PUBLIC MEMBER FUNCTIONS */
	bool ControlPoint::contains(const FingerEventArgs &e) const
	{
		Point2f p = e.getPosition();

		assert(modelview != NULL);
		modelview->unTranslatePoint(p);
		modelview->unScalePoint(p);

		float distance = sqrt((p.getX() * p.getX()) + (p.getY() * p.getY()));

		return distance <= (width * BOUNDING_SPHERE);
	}