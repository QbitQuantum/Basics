void DialogFunction::onRemovePoint()
{
	QwtArraySeriesData<QPointF>* pSeries = static_cast<QwtArraySeriesData<QPointF>*>(_pCurve->data());
	if (pSeries)
	{
		QPolygonF samples = pSeries->samples();
		if (_indexSelectedPoint>=0 && _indexSelectedPoint<samples.size())
		{
			samples.remove(_indexSelectedPoint);
			_pCurve->setSamples(samples);
			widgetPlot->replot();
		}
	}
}