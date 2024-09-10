void ScaleDraw::drawBreak(QPainter *painter) const
{
	ScaleEngine *sc_engine = (ScaleEngine *)d_plot->axisScaleEngine(axis());
    if (!sc_engine->hasBreak() || !sc_engine->hasBreakDecoration())
        return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

	QPen pen = painter->pen();
	pen.setColor(d_plot->axisWidget(axis())->palette().color(QPalette::Active, QColorGroup::Foreground));
	painter->setPen(pen);

	int len = d_plot->majorTickLength();

    QwtScaleMap scaleMap = map();
    const QwtMetricsMap metricsMap = QwtPainter::metricsMap();
    QPoint pos = this->pos();

	if (!d_plot->isPrinting()){
		QwtPainter::resetMetricsMap();
		pos = metricsMap.layoutToDevice(pos);

		if ( orientation() == Qt::Vertical ){
			scaleMap.setPaintInterval(
				metricsMap.layoutToDeviceY((int)scaleMap.p1()),
				metricsMap.layoutToDeviceY((int)scaleMap.p2()));
			len = metricsMap.layoutToDeviceX(len);
		} else {
			scaleMap.setPaintInterval(
				metricsMap.layoutToDeviceX((int)scaleMap.p1()),
				metricsMap.layoutToDeviceX((int)scaleMap.p2()));
			len = metricsMap.layoutToDeviceY(len);
		}
	}

	int lval = scaleMap.transform(sc_engine->axisBreakLeft());
	int rval = scaleMap.transform(sc_engine->axisBreakRight());
	switch(alignment()){
		case LeftScale:
		case RightScale:
			QwtPainter::drawLine(painter, pos.x() + len, lval - len, pos.x() - len, lval + len);
			QwtPainter::drawLine(painter, pos.x() + len, rval - len, pos.x() - len, rval + len);
		break;
		case TopScale:
		case BottomScale:
			QwtPainter::drawLine(painter, lval + len, pos.y() - len, lval - len, pos.y() + len);
			QwtPainter::drawLine(painter, rval + len, pos.y() - len, rval - len, pos.y() + len);
		break;
	}

	if (!d_plot->isPrinting())
		QwtPainter::setMetricsMap(metricsMap); // restore metrics map
	painter->restore();
}