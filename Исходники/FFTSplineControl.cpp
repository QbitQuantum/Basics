	/* PRIVATE MEMBER FUNCTIONS */
	void FFTSplineControl::expandButton_Dragged(const Vector2f &v)
	{
		assert(modelview != NULL);
		assert(expandButton != NULL);
		assert(exitButton != NULL);

		Point2f p(v.getX(), 0.0f);
		modelview->unScalePoint(p);

		float newWidth = width + p.getX();
		float beatWidth = InterfaceManager::getBeatLength();

		if(newWidth >= (beatWidth * MIN_BEAT_WIDTH) && newWidth <= (beatWidth * MAX_BEAT_WIDTH))
		{
			// expand/shrink the control
			float factor = newWidth / width;
			stretchControlPoints(factor);

			setWidth(newWidth);

			// move the handles
			expandButton->getPosition().setX(width + BORDER_DIM);
			exitButton->getPosition().setX(width + BORDER_DIM);

			dirty = true;
			fftDirty = true;
		}
	}