/*--------------------------------------------------------------------------*/
void PegChart::RecalcLayout(BOOL bRedraw /*=TRUE*/)
{
    mChartRegion = mClient;
    
    if(mwExStyle & CS_DRAWXTICS)
    {
        mChartRegion.wBottom -= mwMajorTicSize;
    }

    if(mwExStyle & CS_DRAWYTICS)
    {
        mChartRegion.wLeft += mwMajorTicSize;

		if(mwExStyle & CS_DUALYTICS)
		{
			mChartRegion.wRight -= mwMajorTicSize;
		}
    }

    if (mwExStyle & CS_DRAWYLABELS)
    {
		SIGNED iSkipHeight = TextHeight(lsTEST, mpFont);
		iSkipHeight++;
		iSkipHeight >>= 1;
		mChartRegion.wTop += iSkipHeight;

		if(!(mwExStyle & CS_DRAWXLABELS))
		{
			mChartRegion.wBottom -= iSkipHeight;
		}
        
        if(mwYLabelWidth == 0)
		{
			PEGCHAR cBuffer[20];
			_ltoa(mlMinY, cBuffer, 10);
			SIGNED iMinWidth = TextWidth(cBuffer, mpFont);
			//_ltoa(mlMinY,cBuffer,10);
			_ltoa(mlMaxY, cBuffer, 10);
			SIGNED iMaxWidth = TextWidth(cBuffer, mpFont);
			/*_ltoa(mlMinY,cBuffer,10);*/
			/*_ltoa(mlMaxY,cBuffer,10);*/
			mChartRegion.wLeft += 
                iMinWidth > iMaxWidth ? iMinWidth : iMaxWidth;
            mChartRegion.wLeft += 2;

            if(mwExStyle & CS_DUALYLABELS)
            {
                mChartRegion.wRight -= 
                    iMinWidth > iMaxWidth ? iMinWidth : iMaxWidth;
                mChartRegion.wRight -= 2;
            }
		}
		else
		{
			mChartRegion.wLeft += mwYLabelWidth;
		}
    }