void MLGraph::paint (Graphics& g)
{
	MLLookAndFeel* myLookAndFeel = MLLookAndFeel::getInstance();
	int m = myLookAndFeel->getSmallMargin();
	int w = getWidth();
	int h = getHeight();
	
	Rectangle<float> br (m + 0.5, m + 0.5, w - 2*m + 0.5, h - 2*m + 0.5);
	
	float outlineThickness = 0.5;
	Path envPath;
	
	float fx, fy, viewX, viewY;
	envPath.startNewSubPath(mViewDomain(0), mViewRange(0));
	for(int i=0; i<=mResolution; ++i)
	{
		fx = mDomain((float)i/(float)mResolution);
		
		// evaluate function at fx;
		fy = 0.;
		int s = mPolyCoeffs.size();
		for(int j=0; j<s; ++j)
		{
			float k = mPolyCoeffs[j];
			fy += k*powf(fx, j);
		}		
		
		viewX = mViewDomain(fx);
		viewY = mViewRange(fy);
		envPath.lineTo(viewX, viewY);
	}
	envPath.lineTo(mViewDomain(1), mViewRange(0));

	g.setColour(findColour(MLLookAndFeel::outlineColor));
	g.strokePath(envPath, PathStrokeType (outlineThickness));	
	g.setColour(findColour(MLLookAndFeel::outlineColor).withAlpha(0.125f));
	g.fillPath(envPath);
	
}