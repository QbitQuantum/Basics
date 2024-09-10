/*
** Draws the meter on the double buffer
**
*/
bool CMeterHistogram::Draw(Graphics& graphics)
{
	if (!CMeter::Draw(graphics) ||
		(m_Measures.size() >= 1 && !m_PrimaryValues) ||
		(m_Measures.size() >= 2 && !m_SecondaryValues)) return false;

	CMeasure* secondaryMeasure = (m_Measures.size() >= 2) ? m_Measures[1] : NULL;

	GraphicsPath primaryPath;
	GraphicsPath secondaryPath;
	GraphicsPath bothPath;

	Bitmap* primaryBitmap = m_PrimaryImage.GetImage();
	Bitmap* secondaryBitmap = m_SecondaryImage.GetImage();
	Bitmap* bothBitmap = m_OverlapImage.GetImage();

	int x = GetX();
	int y = GetY();

	// Default values (GraphStart=Right, GraphOrientation=Vertical)
	int i;
	int startValue = 0;
	int* endValueLHS = &i;
	int* endValueRHS = &m_W;
	int step = 1;
	int endValue = -1; //(should be 0, but need to simulate <=)

	// GraphStart=Left, GraphOrientation=Vertical
	if (!m_GraphHorizontalOrientation)
	{
		if (m_GraphStartLeft)
		{
			startValue = m_W - 1;
			endValueLHS = &endValue;
			endValueRHS = &i;
			step = -1;
		}
	}
	else
	{
		if (!m_Flip)
		{
			endValueRHS = &m_H;
		}
		else
		{
			startValue = m_H - 1;
			endValueLHS = &endValue;
			endValueRHS = &i;
			step = -1;
		}
	}

	// Horizontal or Vertical graph
	if (m_GraphHorizontalOrientation)
	{
		for (i = startValue; *endValueLHS < *endValueRHS; i += step)
		{
			double value = (m_MaxPrimaryValue == 0.0) ?
				  0.0
				: m_PrimaryValues[(i + (m_MeterPos % m_H)) % m_H] / m_MaxPrimaryValue;
			value -= m_MinPrimaryValue;
			int primaryBarHeight = (int)(m_W * value);
			primaryBarHeight = min(m_W, primaryBarHeight);
			primaryBarHeight = max(0, primaryBarHeight);

			if (secondaryMeasure)
			{
				value = (m_MaxSecondaryValue == 0.0) ?
					  0.0
					: m_SecondaryValues[(i + m_MeterPos) % m_H] / m_MaxSecondaryValue;
				value -= m_MinSecondaryValue;
				int secondaryBarHeight = (int)(m_W * value);
				secondaryBarHeight = min(m_W, secondaryBarHeight);
				secondaryBarHeight = max(0, secondaryBarHeight);

				// Check which measured value is higher
				int bothBarHeight = min(primaryBarHeight, secondaryBarHeight);

				// Cache image/color rectangle for the both lines
				{
					Rect& r = m_GraphStartLeft ?
						  Rect(x, y + startValue + (step * i), bothBarHeight, 1)
						: Rect(x + m_W - bothBarHeight, y + startValue + (step * i), bothBarHeight, 1);

					bothPath.AddRectangle(r);  // cache
				}

				// Cache the image/color rectangle for the rest
				if (secondaryBarHeight > primaryBarHeight)
				{
					Rect& r = m_GraphStartLeft ?
						  Rect(x + bothBarHeight, y + startValue + (step * i), secondaryBarHeight - bothBarHeight, 1)
						: Rect(x + m_W - secondaryBarHeight, y + startValue + (step * i), secondaryBarHeight - bothBarHeight, 1);

					secondaryPath.AddRectangle(r);  // cache
				}
				else
				{
					Rect& r = m_GraphStartLeft ?
						  Rect(x + bothBarHeight, y + startValue + (step * i), primaryBarHeight - bothBarHeight, 1)
						: Rect(x + m_W - primaryBarHeight, y + startValue + (step * i), primaryBarHeight - bothBarHeight, 1);

					primaryPath.AddRectangle(r);  // cache
				}
			}
			else
			{
				Rect& r = m_GraphStartLeft ?
					  Rect(x, y + startValue + (step * i), primaryBarHeight, 1)
					: Rect(x + m_W - primaryBarHeight, y + startValue + (step * i), primaryBarHeight, 1);

				primaryPath.AddRectangle(r);  // cache
			}
		}
	}
	else	// GraphOrientation=Vertical
	{
		for (i = startValue; *endValueLHS < *endValueRHS; i += step)
		{
			double value = (m_MaxPrimaryValue == 0.0) ?
				  0.0
				: m_PrimaryValues[(i + m_MeterPos) % m_W] / m_MaxPrimaryValue;
			value -= m_MinPrimaryValue;
			int primaryBarHeight = (int)(m_H * value);
			primaryBarHeight = min(m_H, primaryBarHeight);
			primaryBarHeight = max(0, primaryBarHeight);

			if (secondaryMeasure)
			{
				value = (m_MaxSecondaryValue == 0.0) ?
					  0.0
					: m_SecondaryValues[(i + m_MeterPos) % m_W] / m_MaxSecondaryValue;
				value -= m_MinSecondaryValue;
				int secondaryBarHeight = (int)(m_H * value);
				secondaryBarHeight = min(m_H, secondaryBarHeight);
				secondaryBarHeight = max(0, secondaryBarHeight);

				// Check which measured value is higher
				int bothBarHeight = min(primaryBarHeight, secondaryBarHeight);

				// Cache image/color rectangle for the both lines
				{
					Rect& r = m_Flip ?
						  Rect(x + startValue + (step * i), y, 1, bothBarHeight)
						: Rect(x + startValue + (step * i), y + m_H - bothBarHeight, 1, bothBarHeight);

					bothPath.AddRectangle(r);  // cache
				}

				// Cache the image/color rectangle for the rest
				if (secondaryBarHeight > primaryBarHeight)
				{
					Rect& r = m_Flip ?
						  Rect(x + startValue + (step * i), y + bothBarHeight, 1, secondaryBarHeight - bothBarHeight)
						: Rect(x + startValue + (step * i), y + m_H - secondaryBarHeight, 1, secondaryBarHeight - bothBarHeight);

					secondaryPath.AddRectangle(r);  // cache
				}
				else
				{
					Rect& r = m_Flip ?
						  Rect(x + startValue + (step * i), y + bothBarHeight, 1, primaryBarHeight - bothBarHeight)
						: Rect(x + startValue + (step * i), y + m_H - primaryBarHeight, 1, primaryBarHeight - bothBarHeight);

					primaryPath.AddRectangle(r);  // cache
				}
			}
			else
			{
				Rect& r = m_Flip ?
					  Rect(x + startValue + (step * i), y, 1, primaryBarHeight)
					: Rect(x + startValue + (step * i), y + m_H - primaryBarHeight, 1, primaryBarHeight);

				primaryPath.AddRectangle(r);  // cache
			}
		}
	}

	// Draw cached rectangles
	if (primaryBitmap)
	{
		Rect r(x, y, primaryBitmap->GetWidth(), primaryBitmap->GetHeight());

		graphics.SetClip(&primaryPath);
		graphics.DrawImage(primaryBitmap, r, 0, 0, r.Width, r.Height, UnitPixel);
		graphics.ResetClip();
	}
	else
	{
		SolidBrush brush(m_PrimaryColor);
		graphics.FillPath(&brush, &primaryPath);
	}
	if (secondaryMeasure)
	{
		if (secondaryBitmap)
		{
			Rect r(x, y, secondaryBitmap->GetWidth(), secondaryBitmap->GetHeight());

			graphics.SetClip(&secondaryPath);
			graphics.DrawImage(secondaryBitmap, r, 0, 0, r.Width, r.Height, UnitPixel);
			graphics.ResetClip();
		}
		else
		{
			SolidBrush brush(m_SecondaryColor);
			graphics.FillPath(&brush, &secondaryPath);
		}
		if (bothBitmap)
		{
			Rect r(x, y, bothBitmap->GetWidth(), bothBitmap->GetHeight());

			graphics.SetClip(&bothPath);
			graphics.DrawImage(bothBitmap, r, 0, 0, r.Width, r.Height, UnitPixel);
			graphics.ResetClip();
		}
		else
		{
			SolidBrush brush(m_OverlapColor);
			graphics.FillPath(&brush, &bothPath);
		}
	}

	return true;
}