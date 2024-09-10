void QwtErrorPlotCurve::drawErrorBars(QPainter *painter,
		const QwtScaleMap &xMap, const QwtScaleMap &yMap, int from, int to) const
{
    int sh = 0, sw =0;
    const QwtSymbol symbol = d_master_curve->symbol();
    if (symbol.style() != QwtSymbol::NoSymbol){
        sh = symbol.size().height();
        sw = symbol.size().width();
    }

	double d_xOffset = 0.0;
	double d_yOffset = 0.0;
	if (d_master_curve->type() == Graph::VerticalBars)
		d_xOffset = ((QwtBarCurve *)d_master_curve)->dataOffset();
	else if (d_master_curve->type() == Graph::HorizontalBars)
		d_yOffset = ((QwtBarCurve *)d_master_curve)->dataOffset();

	ScaleEngine *yScaleEngine = (ScaleEngine *)plot()->axisScaleEngine(yAxis());
	bool logYScale = (yScaleEngine->type() == QwtScaleTransformation::Log10) ? true : false;
	
	for (int i = from; i <= to; i++){
		const int xi = xMap.transform(x(i) + d_xOffset);
		const int yi = yMap.transform(y(i) + d_yOffset);

		if (type == Vertical){
			const int yh = yMap.transform(y(i) + err[i]);
			const int yl = yMap.transform(y(i) - err[i]);
			const int yhl = yi - sh/2;
			const int ylh = yi + sh/2;

			if (plus){
				QwtPainter::drawLine(painter, xi, yhl, xi, yh);
				QwtPainter::drawLine(painter, xi - cap/2, yh, xi + cap/2, yh);
			}
			if (minus && (!logYScale || (logYScale && yl > 0))){
				QwtPainter::drawLine(painter, xi, ylh, xi, yl);
				QwtPainter::drawLine(painter, xi - cap/2, yl, xi + cap/2, yl);
			}
			if (through)
				QwtPainter::drawLine(painter, xi, yhl, xi, ylh);
		} else if (type == Horizontal) {
			const int xp = xMap.transform(x(i) + err[i]);
			const int xm = xMap.transform(x(i) - err[i]);
  			const int xpm = xi + sw/2;
  	        const int xmp = xi - sw/2;

			if (plus){
				QwtPainter::drawLine(painter, xp, yi, xpm, yi);
				QwtPainter::drawLine(painter, xp, yi - cap/2, xp, yi + cap/2);
			}
			if (minus){
				QwtPainter::drawLine(painter, xm, yi, xmp, yi);
				QwtPainter::drawLine(painter, xm, yi - cap/2, xm, yi + cap/2);
			}
			if (through)
				QwtPainter::drawLine(painter, xmp, yi, xpm, yi);
		}
	}
}