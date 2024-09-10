void EnvelopeComponent::paint(Graphics& g)
{
	paintBackground(g);
	
	if(handles.size() > 0)
	{
		Path path;
		Env env = getEnv();
		
		EnvelopeHandleComponent* handle = handles.getUnchecked(0);
		path.startNewSubPath((handle->getX() + handle->getRight()) * 0.5f,
							 (handle->getY() + handle->getBottom()) * 0.5f);
		
		const float firstTime = handle->getTime();
		float time = firstTime;
		
		for(int i = 1; i < handles.size(); i++) 
		{
			handle = handles.getUnchecked(i);
			float halfWidth = handle->getWidth()*0.5f;
			float halfHeight = handle->getHeight()*0.5f;
			
			float nextTime = handle->getTime();
			float handleTime = nextTime - time;
			float timeInc = handleTime / curvePoints;
			
			for(int j = 0; j < curvePoints; j++)
			{
				float value = env.lookup(time - firstTime);
				path.lineTo(convertDomainToPixels(time) + halfWidth, 
							convertValueToPixels(value) + halfHeight);
				time += timeInc;
			}
			
			path.lineTo((handle->getX() + handle->getRight()) * 0.5f,
						(handle->getY() + handle->getBottom()) * 0.5f);
			
			time = nextTime;
		}
		
		g.setColour(colours[Line]);
		g.strokePath (path, PathStrokeType(1.0f));
		
		if((loopNode >= 0) && (releaseNode >= 0) && (releaseNode > loopNode))
		{			
			EnvelopeHandleComponent* releaseHandle = handles[releaseNode];
			EnvelopeHandleComponent* loopHandle = handles[loopNode];
			
			if((releaseHandle != 0) && (loopHandle != 0))
			{
				// draw a horizontal line from release
				g.setColour(colours[LoopLine]);
				
				const float loopY = (loopHandle->getY() + loopHandle->getBottom()) * 0.5f;
				const float releaseY = (releaseHandle->getY() + releaseHandle->getBottom()) * 0.5f;
				const float loopX = (loopHandle->getX() + loopHandle->getRight()) * 0.5f;
				const float releaseX = (releaseHandle->getX() + releaseHandle->getRight()) * 0.5f;
				
				float dashes[] = { 5, 3 };
				juce::Line<float> line(loopX, releaseY, loopX, loopY);
				g.drawDashedLine(line, dashes, numElementsInArray(dashes), 0.5f);
				
				const int arrowLength = HANDLESIZE*2;
				
				g.drawLine(releaseX, releaseY, 
						   loopX + arrowLength, releaseY, 
						   0.5f);
				
				if(loopY == releaseY)
					g.setColour(colours[LoopNode]);
				
//				g.drawArrow(loopX + arrowLength, releaseY, 
//							loopX, releaseY, 
//							0.5f, HANDLESIZE, arrowLength);
				g.drawArrow(juce::Line<float>((float)(loopX + arrowLength), releaseY, loopX, releaseY), 
							0.5f, HANDLESIZE, arrowLength);
				
			}
		}
	}
}