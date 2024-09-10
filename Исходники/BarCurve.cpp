void QwtBarCurve::draw(QPainter *painter,
    const QwtDiMap &xMap, const QwtDiMap &yMap, int from, int to)
{
   if ( !painter || dataSize() <= 0 )
        return;

    if (to < 0)
        to = dataSize() - 1;

    if ( verifyRange(from, to) > 0 )
		{
        painter->save();
        painter->setPen(QwtPlotCurve::pen());
        painter->setBrush(QwtPlotCurve::brush());
			
		int dx,dy,ref,bar_width;
			
		if (bar_style == Vertical)
			ref= yMap.transform(1e-100); //smalest positive value for log scales
		else
			ref= xMap.transform(1e-100);	
				
		int i;
		if (bar_style == Vertical)
			{
			dx = abs(xMap.transform(x(from+1))-xMap.transform(x(from)));
			for (i=from+2; i<to; i++)
				{
				int min = abs(xMap.transform(x(i+1))-xMap.transform(x(i)));
				if (min <= dx)
					dx=min;
				}
			bar_width=int(dx*(1-bar_gap*0.01));
			}
		else
			{
			dy = abs(yMap.transform(y(from+1))-yMap.transform(y(from)));
			for (i=from+2; i<to; i++)
				{
				int min = abs(yMap.transform(y(i+1))-yMap.transform(y(i)));
				if (min <= dy)
					dy=min;
				}
			bar_width=int(dy*(1-bar_gap*0.01));
			}
		
		const int half_width = int((0.5-bar_offset*0.01)*bar_width);
		const int bw1 = bar_width+1;
        for (i=from; i<=to; i++)
			{
            const int px = xMap.transform(x(i));
            const int py = yMap.transform(y(i));
			
			if (bar_style == Vertical)
				{
				if (y(i) < 0)
					painter->drawRect(px-half_width, ref, bw1, (py-ref));
				else
					painter->drawRect(px-half_width, py, bw1, (ref-py+1));	
				}
			else
				{
				if (x(i) < 0)
					painter->drawRect(px, py-half_width, (ref-px), bw1);
				else
					painter->drawRect(ref, py-half_width,(px-ref), bw1);
				}	
			}
		painter->restore();
		}
}