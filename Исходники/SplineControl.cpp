	bool SplineControl::controlPointContains(const FingerEventArgs &e) const
	{
		assert(modelview != NULL);

		Point2f p =	e.getPosition();
		modelview->unTranslatePoint(p);

		// use legend dim on left and right as a buffer to prevent deletion near edge
		float legendDim = (height * LEGEND_DIM) * modelview->getYScale();

		return p.getX() >= -legendDim &&
			p.getX() <= (width * modelview->getXScale()) + legendDim &&
			p.getY() >= 0.0f &&
			p.getY() <= height * modelview->getYScale();
	}