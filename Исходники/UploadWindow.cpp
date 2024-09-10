void UploadWindow::paint(Graphics& g)
{
	g.fillAll(Colours::black);

	Colour border = Colours::wheat;
	juce::Rectangle<int> rc(0, 0, getWidth(), getHeight());
	for (int i = 0; i < 4; i++)
	{
		g.setColour(i == 0 ? Colours::black : border);
		g.drawRect(rc.getX(), rc.getY(), rc.getWidth(), rc.getHeight());
		rc.reduce(1, 1);
		border = border.brighter(0.4f);
	}
	
	ColourGradient gf(Colours::red, 0, getHeight()/2.0f, Colours::darkred, float(getWidth()), getHeight()/2.0f, false);
	FillType ft(gf);

	int cx = getWidth() / 2;
	int cy = getHeight() / 2;
	const float r = 12.0f;
	for (int i = 3; i >= 0; i--)
	{
		if (i % 2 != 0)
			g.setFillType(ft);
		else
			g.setColour(Colours::white);
		
		g.fillEllipse(cx - (r * i), cy - (r * i), (r * i) * 2, (r * i) * 2);
	}
	g.setFillType(Colours::transparentWhite);

	if (smugMug.isUploading())
	{
		int64 n = smugMug.getTotalbytesUploaded();
		int64 d = smugMug.getTotalBytesToUpload();
		double percent = (d == 0) ? 0 : (double(n)/double(d)*100);
		

		GlyphArrangement glyphs;
		glyphs.addLineOfText(Font(25.0f, Font::bold), String(percent, 1) + ("%"), 0, 0);

		Path p;
		glyphs.createPath(p);

		juce::Rectangle<float> bounds = p.getBounds();
		float cx = getWidth() / 2.0f - bounds.getWidth() / 2.0f - bounds.getX();
		float cy = getHeight() / 2.0f - bounds.getHeight() / 2.0f - bounds.getY();

		AffineTransform trans = AffineTransform::translation(cx, cy);
		g.setColour(Colours::black);
		g.fillPath(p, trans);
		g.setColour(Colours::white);
		g.strokePath(p, PathStrokeType(1), trans);
	}
}