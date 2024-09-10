bool ChemicalStructureRecognizer::removeMoleculeCaptions(const Settings& vars, Image& img, SegmentDeque& symbols, SegmentDeque& graphics)
{
	logEnterFunction();

	bool result = false;
	
	getLogExt().append("Symbols height", vars.dynamic.CapitalHeight);

	if (vars.dynamic.CapitalHeight < vars.lab_remover.MinCapitalHeight || 
		vars.dynamic.CapitalHeight > vars.lab_remover.MaxCapitalHeight)
	{
		getLogExt().appendText("Unappropriate symbols height");
		return result;
	}

	getLogExt().append("Symbols height max", vars.separator.capHeightMax);
	getLogExt().appendImage("img", img);
	
	const int min_cap_chars = vars.lab_remover.MinLabelChars;
	double minWidth = min_cap_chars * (vars.estimation.MinSymRatio + vars.estimation.MaxSymRatio) / 2.0 * vars.dynamic.CapitalHeight * vars.estimation.CapitalHeightError;
	double maxHeight = maxHeightHelper(vars, vars.lab_remover.MaxLabelLines);
	double minHeight = vars.dynamic.CapitalHeight * vars.separator.capHeightMin;
	double centerShiftMax = vars.lab_remover.CenterShiftMax;
	int borderDistance = round(vars.dynamic.CapitalHeight);
	getLogExt().append("minWidth", minWidth);
	getLogExt().append("maxHeight", maxHeight);
	getLogExt().append("minHeight", minHeight);
	getLogExt().append("borderDistance", borderDistance);

	WeakSegmentator ws(img.getWidth(), img.getHeight());
	ws.appendData(img, WeakSegmentator::getLookupPattern((int)vars.dynamic.CapitalHeight, false));

	if (ws.SegmentPoints.size() < 2)
	{
		getLogExt().appendText("Only one segment, ignoring");
		return result;
	}

	for (WeakSegmentator::SegMap::iterator it = ws.SegmentPoints.begin(); it != ws.SegmentPoints.end(); ++it)
	{
		RectShapedBounding b(it->second);	
		const Rectangle &bounding = b.getBounding();
		getLogExt().appendPoints("segment", it->second);
		getLogExt().append("width", bounding.width);
		getLogExt().append("height", bounding.height);
		if (bounding.height <= maxHeight &&
			bounding.height >= minHeight &&
			bounding.width  >= minWidth &&
			  (bounding.y1() < borderDistance || 
			   bounding.y2() >= img.getHeight() - borderDistance)
			  && 
			  (bounding.x1() < borderDistance ||
			   bounding.x2() >= img.getWidth() - borderDistance ||
			   absolute((bounding.x1() + bounding.x2()) / 2.0 - img.getWidth() / 2.0) <= centerShiftMax * borderDistance
			  )
		    )
		{
			getLogExt().appendPoints("possibly caption", it->second);			
			
			{
				Rectangle badBounding = b.getBounding();
				double value = 0.0;
				int count = 0;
				for (int x = badBounding.x1(); x <= badBounding.x2() && x < img.getWidth(); x++)
				{
					for (int y = badBounding.y1(); y <= badBounding.y2() && y < img.getHeight(); y++)
					{
						if (img.getByte(x, y) == 0)
							value += 1.0;
						count++;
					}
				}
				value /= count;
				getLogExt().append("Average density", value);

				if (value > vars.lab_remover.MinimalDensity)
				{
					getLogExt().appendText("Caption bounding is found, filtering segments");

					std::vector<Segment*> bad_symbols;
					std::vector<Segment*> bad_graphics;

					for (SegmentDeque::iterator it = symbols.begin(); it != symbols.end(); ++it)
						if ((*it)->getX() >= badBounding.x1() - vars.lab_remover.PixGapX && 
							(*it)->getX() < badBounding.x2() &&
							(*it)->getY() >= badBounding.y1() - vars.lab_remover.PixGapY && 
							(*it)->getY() + (*it)->getHeight() <= badBounding.y2() + vars.lab_remover.PixGapY)
						{
							bad_symbols.push_back(*it);
						}
			

					for (SegmentDeque::iterator it = graphics.begin(); it != graphics.end(); ++it)
						if ((*it)->getX() >= badBounding.x1() - vars.lab_remover.PixGapX && 
							(*it)->getX() < badBounding.x2() &&
							(*it)->getY() >= badBounding.y1() - vars.lab_remover.PixGapY && 
							(*it)->getY() + (*it)->getHeight() <= badBounding.y2() + vars.lab_remover.PixGapY)
						{
							bad_graphics.push_back(*it);
						}
			
					if (bad_symbols.size() >= bad_graphics.size())
					{
						getLogExt().appendText("Clearing the image");
						for (int x = badBounding.x1(); x <= badBounding.x2() && x < img.getWidth(); x++)
							for (int y = badBounding.y1(); y <= badBounding.y2() && y < img.getHeight(); y++)
								img.getByte(x,y) = 255;

						result = true;
					} // if letters>graphics

				} // if density
			} // locals
		} // if bounding passes size constraints
	} // for

	return result;
}