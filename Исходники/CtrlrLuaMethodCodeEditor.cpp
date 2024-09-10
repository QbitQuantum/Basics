	void paint (Graphics& g) override
	{
		Path outline;
		outline.addRoundedRectangle (1.0f, 1.0f, getWidth() - 2.0f, getHeight() - 2.0f, 8.0f);

		g.setColour (Colours::black.withAlpha (0.6f));
		g.fillPath (outline);
		g.setColour (Colours::white.withAlpha (0.8f));
		g.strokePath (outline, PathStrokeType (1.0f));
	}