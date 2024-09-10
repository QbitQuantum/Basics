void Table::paint (Graphics& g)
{
	//Image bg = ImageCache::getFromHashCode(15);
	//g.drawImage (bg, viewX, 0, origWidth, getHeight(), 
	//	0, 0, bg.getWidth(), bg.getHeight(), false);
	
	if (isCurrentlyOnTop)
		currColour = activeColour.withMultipliedSaturation(3);
	else
		currColour = activeColour;
	int startIndx, endIndx;

	// If using overview...
	if (useOverview == true) {
		startIndx = (viewX/getWidth()) * overview.maxY.size();
		endIndx = startIndx + viewWidth;
		float bottomYPixelValue, topYPixelValue;
		bottomYPixelValue = topYPixelValue = 0;

		// For loop which will draw a vertical line between the min and max value 
		//for each x pixel 
		int xPixelValue = 0; 
		for (int i=startIndx; i<endIndx; i++) {
			//We need to make sure that the current min value is not greater than the 
			//next max value. Otherwise there would be a gap in the wave form...
			if (overview.minY[i] < overview.maxY[i+1])
				bottomYPixelValue = overview.maxY[i+1];
			else
				bottomYPixelValue = overview.minY[i];
			if (overview.maxY[i] > overview.minY[i+1])
				topYPixelValue = overview.minY[i+1];
			else
				topYPixelValue = overview.maxY[i];
			 
			float minGap = 0.4;
			float diff = bottomYPixelValue - topYPixelValue;
			if (diff < minGap) {
				bottomYPixelValue += (minGap-diff)/2;
				topYPixelValue -= (minGap-diff)/2;
			}

			if (CabbageUtils::isNumber(topYPixelValue) && CabbageUtils::isNumber(bottomYPixelValue)) {
				g.setColour(currColour);
				topYPixelValue -= minWaveHeight/2;
				bottomYPixelValue += minWaveHeight/2;
				g.drawVerticalLine (xPixelValue+viewX, topYPixelValue, bottomYPixelValue);
				xPixelValue += 1;

				// Fill
				if (tblSize <= 4096) {
					g.setColour(currColour.withAlpha(0.1f));
					if (bottomYPixelValue < zeroAmpPosition)
						g.drawVerticalLine (xPixelValue+viewX, bottomYPixelValue, zeroAmpPosition);
					else if (bottomYPixelValue > zeroAmpPosition)
						g.drawVerticalLine (xPixelValue+viewX, zeroAmpPosition, bottomYPixelValue);

					if (isCurrentlyOnTop)
						currColour = activeColour.withMultipliedSaturation(3);
					else
						currColour = activeColour;
				}
			}
		}
	}
	
	//Else if using original array values for painting...
	else if (useOverview == false) {
		g.setColour(currColour);
		startIndx = ((viewX/getWidth()) * tableData.amps.size()) + 0.5; //0.5 for rounding
		endIndx = (startIndx + (viewWidth/numPixelsPerIndex)) + 0.5; 
		float prevX = viewX;
		float prevY = convertAmpToPixel (tableData.amps[startIndx]);
		float currY;
		for (int i=startIndx+1; i<=endIndx; i++) {
			currY = convertAmpToPixel (tableData.amps[i]);
			g.drawLine (prevX, prevY, prevX+numPixelsPerIndex, currY, minWaveHeight);
			// For drawing index markers
			if (numPixelsPerIndex > 4)
				g.drawVerticalLine (prevX+numPixelsPerIndex, currY-3, currY+3);
			prevX = prevX + numPixelsPerIndex;
			prevY = currY;
		}
	}

//	g.setColour(Colours::lightblue);
//	envPath.scaleToFit (0, tableTop, getWidth(), tableHeight, false);
//	g.strokePath (envPath, PathStrokeType(2.0f));
	//----- For handles....
	
	Path path;
	for(int i = 0; i < handles.size(); i++) {
		CabbageEnvelopeHandleComponent* handle = handles.getUnchecked(i);
		if(handle->getProperties().getWithDefault(String("shape"), String("")).equals("linear"))
		{	
		//for linear envelopes
		if(i==0) {
			path.startNewSubPath((handle->getX() + handle->getRight()) / 2,
									 (handle->getY() + handle->getBottom()) / 2);
			} else {
				path.lineTo((handle->getX() + handle->getRight()) / 2,
							(handle->getY() + handle->getBottom()) / 2);
			}
		}
		else
		{
		//for bezier envelopes
		if(i==0){
			path.startNewSubPath((handle->getX() + handle->getRight()) / 2,
								 (handle->getY() + handle->getBottom()) / 2);
		} else {
			int curX = handle->getX();
			int curY = handle->getY();
			int prevX = path.getCurrentPosition().getX();
			int prevY = path.getCurrentPosition().getY();
			if(curY>prevY)
			path.quadraticTo(prevX, curY, 
							(curX + handle->getRight()) / 2,
							(curY + handle->getBottom()) / 2);
			else if(curY<prevY){
			path.quadraticTo(curX, prevY,
							(curX + handle->getRight()) / 2,
							(curY + handle->getBottom()) / 2);
			}
		}
		}
		//String coordinate;
		//coordinate = String(handle->getX()) + String(", ") + String(handle->getY());
		//g.setColour(Colours::lime);
		//g.drawFittedText(coordinate, handle->getX(), handle->getY(), 50, 20, Justification::centred, 1); 
		
		g.setColour(Colours::lightblue);
		g.strokePath (path, PathStrokeType(2.0f));
	}
		
	//draw the crubber if needed
	if(scrubberPosition>0){
	g.setColour(currColour);
	scrubberPosition = scrubberPosition*getWidth();
	g.drawLine(scrubberPosition, 0, scrubberPosition, getHeight(), 2);
	}
}