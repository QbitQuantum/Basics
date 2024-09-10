void BoxCurve::drawBox(QPainter *painter, const QwtDiMap &xMap, const QwtDiMap &yMap, double *dat, int size)
{
const int px = xMap.transform(x(0));
const int px_min = xMap.transform(x(0) - 0.5);
const int px_max = xMap.transform(x(0) + 0.5);
const int box_width = 1+(px_max - px_min)*b_width/100;
const int hbw = box_width/2;
const int median = yMap.transform(gsl_stats_median_from_sorted_data (dat, 1, size));
int b_lowerq, b_upperq;
double sd, se, mean;
if(w_range == SD || w_range == SE || b_range == SD || b_range == SE)
	{
	sd = gsl_stats_sd(dat, 1, size);
	se = sd/sqrt((double)size);
	mean = gsl_stats_mean(dat, 1, size);
	}

if(b_range == SD)
	{
	b_lowerq = yMap.transform(mean - sd*b_coeff);
	b_upperq = yMap.transform(mean + sd*b_coeff);
	}
else if(b_range == SE)
	{
	b_lowerq = yMap.transform(mean - se*b_coeff);
	b_upperq = yMap.transform(mean + se*b_coeff);
	}
else
	{
	b_lowerq = yMap.transform(gsl_stats_quantile_from_sorted_data (dat, 1, size, 1-0.01*b_coeff));
	b_upperq = yMap.transform(gsl_stats_quantile_from_sorted_data (dat, 1, size, 0.01*b_coeff));
	}

//draw box
if (b_style == Rect)
	{
	const QRect r = QRect(px - hbw, b_upperq, box_width, b_lowerq - b_upperq + 1);
	painter->fillRect(r, QwtPlotCurve::brush());
	painter->drawRect(r);
	}
else if (b_style == Diamond)
	{
	const QPointArray pa(4);	
	pa[0] = QPoint(px, b_upperq);	
	pa[1] = QPoint(px + hbw, median);
	pa[2] = QPoint(px, b_lowerq);
	pa[3] = QPoint(px - hbw, median);

	painter->setBrush(QwtPlotCurve::brush());
	painter->drawPolygon(pa);
	}
else if (b_style == WindBox)
	{
	const int lowerq = yMap.transform(gsl_stats_quantile_from_sorted_data (dat, 1, size, 0.25));
	const int upperq = yMap.transform(gsl_stats_quantile_from_sorted_data (dat, 1, size, 0.75));
	const QPointArray pa(8);	
	pa[0] = QPoint(px + hbw, b_upperq);	
	pa[1] = QPoint(int(px + 0.4*box_width), upperq);
	pa[2] = QPoint(int(px + 0.4*box_width), lowerq);
	pa[3] = QPoint(px + hbw, b_lowerq);
	pa[4] = QPoint(px - hbw, b_lowerq);
	pa[5] = QPoint(int(px - 0.4*box_width), lowerq);
	pa[6] = QPoint(int(px - 0.4*box_width), upperq);
	pa[7] = QPoint(px - hbw, b_upperq);	

	painter->setBrush(QwtPlotCurve::brush());
	painter->drawPolygon(pa);
	}
else if (b_style == Notch)
	{
	int j = (int)ceil(0.5*(size - 1.96*sqrt((double)size)));
	int k = (int)ceil(0.5*(size + 1.96*sqrt((double)size)));
	const int lowerCI = yMap.transform(dat[j]);
	const int upperCI = yMap.transform(dat[k]);

	const QPointArray pa(10);	
	pa[0] = QPoint(px + hbw, b_upperq);	
	pa[1] = QPoint(px + hbw, upperCI);
	pa[2] = QPoint(int(px + 0.25*hbw), median);
	pa[3] = QPoint(px + hbw, lowerCI);
	pa[4] = QPoint(px + hbw, b_lowerq);
	pa[5] = QPoint(px - hbw, b_lowerq);
	pa[6] = QPoint(px - hbw, lowerCI);
	pa[7] = QPoint(int(px - 0.25*hbw), median);
	pa[8] = QPoint(px - hbw, upperCI);
	pa[9] = QPoint(px - hbw, b_upperq);	

	painter->setBrush(QwtPlotCurve::brush());
	painter->drawPolygon(pa);
	}

if (w_range)
	{//draw whiskers
	const int l = int(0.1*box_width);
	int w_upperq, w_lowerq;
	if(w_range == SD)
		{
		w_lowerq = yMap.transform(mean - sd*w_coeff);
		w_upperq = yMap.transform(mean + sd*w_coeff);
		}
	else if(w_range == SE)
		{
		w_lowerq = yMap.transform(mean - se*w_coeff);
		w_upperq = yMap.transform(mean + se*w_coeff);
		}
	else
		{
		w_lowerq = yMap.transform(gsl_stats_quantile_from_sorted_data (dat, 1, size, 1-0.01*w_coeff));
		w_upperq = yMap.transform(gsl_stats_quantile_from_sorted_data (dat, 1, size, 0.01*w_coeff));
		}

	painter->drawLine(px - l, w_lowerq, px + l, w_lowerq);
	painter->drawLine(px - l, w_upperq, px + l, w_upperq);

	if (b_style)
		{
		if (w_upperq != b_upperq)
			painter->drawLine(px, w_upperq, px, b_upperq);
		if (w_lowerq != b_lowerq)
			painter->drawLine(px, w_lowerq, px, b_lowerq);
		}
	else
		painter->drawLine(px, w_upperq, px, w_lowerq);
	}

//draw median line
if (b_style == Notch || b_style == NoBox)
	return;
if (b_style == WindBox)
	painter->drawLine(int(px - 0.4*box_width), median, int(px + 0.4*box_width), median);
else
	painter->drawLine(px - hbw, median, px + hbw, median);
}