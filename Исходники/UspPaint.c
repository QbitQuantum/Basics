//
//	PaintItemRunForeground
//
//	Output a whole ITEM_RUN of text. Use clusterList and attrList 
//	to break the glyphs into whole-cluster runs before calling ScriptTextOut
//
//	We don't attempt to interpolate colours over each cluster. If there
//	is more than one ATTR per cluster then tough - only one gets used and
//	whole clusters (even if they contain multiple glyphs) get painted in
//	a single colour
//
static 
void PaintItemRunForeground (	
		USPDATA		* uspData,
		USPFONT		* uspFont,
		ITEM_RUN	* itemRun,	
		HDC			  hdc,
		int			  xpos,
		int			  ypos,
		RECT		* bounds,
		BOOL		  forcesel
	)
{
	HRESULT hr;

	int  i, lasti, g;
	int  glyphIdx1;
	int  glyphIdx2;
	int  runWidth;
	int	 runDir = 1;
	UINT oldMode;

	// make pointers to the run's various glyph buffers
	ATTR	* attrList		= uspData->attrList			+ itemRun->charPos;
	WORD	* clusterList	= uspData->clusterList		+ itemRun->charPos;
	WORD	* glyphList		= uspData->glyphList		+ itemRun->glyphPos;
	int		* widthList		= uspData->widthList		+ itemRun->glyphPos;
	GOFFSET	* offsetList	= uspData->offsetList		+ itemRun->glyphPos;

	// right-left runs can be drawn backwards for simplicity
	if(itemRun->analysis.fRTL)
	{
		oldMode = SetTextAlign(hdc, TA_RIGHT);
		xpos += itemRun->width;
		runDir = -1;
	}

	// loop over all the logical character-positions
	for(lasti = 0, i = 0; i <= itemRun->len; i++)
	{
		// find a change in attribute
		if(i == itemRun->len || attrList[i].fg != attrList[lasti].fg )
		{
			// scan forward to locate end of cluster (we must always
			// handle whole-clusters because the attr[] might fall in the middle)
			for( ; i < itemRun->len; i++)
				if(clusterList[i - 1] != clusterList[i])
					break;

			// locate glyph-positions for the cluster [i,lasti]
			GetGlyphClusterIndices(itemRun, clusterList, i, lasti, &glyphIdx1, &glyphIdx2);

			// measure the width (in pixels) of the run
			for(runWidth = 0, g = glyphIdx1; g <= glyphIdx2; g++)
				runWidth += widthList[g];

			// only need the text colour as we are drawing transparently
			SetTextColor(hdc, forcesel ? uspData->selFG : attrList[lasti].fg);
			
			//
			//	Finally output the run of glyphs
			//
			hr = ScriptTextOut(
				hdc, 
				&uspFont->scriptCache,
				xpos,
				ypos,
				0,
				NULL,					
				&itemRun->analysis, 
				0,
				0,
				glyphList  + glyphIdx1,
				glyphIdx2  - glyphIdx1 + 1,
				widthList  + glyphIdx1,
				0,
				offsetList + glyphIdx1
			);	
			
			// +ve/-ve depending on run direction
			xpos     += runWidth * runDir;		
			lasti     = i;
		}
	}

	// restore the mapping mode
	if(itemRun->analysis.fRTL)
		oldMode = SetTextAlign(hdc, oldMode);
}