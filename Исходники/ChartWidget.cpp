void ChartWidget::mousePressEvent(QMouseEvent* e)
{
    //qDebug() << "mousePressEvent";
	QRect rcWaveforms = m_rcPixmap;

	ChartPointInfo info;
	QPoint ptPixmap = e->pos() - m_rcPixmap.topLeft();
	m_pixmap->fillChartPointInfo(ptPixmap, &info);
	m_clickInfo = info;
	ViewWaveInfo* vwi = info.vwi;

	m_ptMouseWidget = e->pos();
	m_ptMousePixmap = ptPixmap;
	m_ptClickWidget = m_ptMouseWidget;
	m_ptClickPixmap = m_ptMousePixmap;
	m_nClickSampleOffset = m_chartS->sampleOffset();
	
	const WaveInfo* wave = NULL;
	if (vwi != NULL)
		wave = vwi->wave();

	if (e->button() == Qt::LeftButton)
	{
		// If the user Ctrl+clicks on the selected FID wave while in peak editing mode:
		if (e->modifiers() == Qt::ControlModifier)
		{
			// If the user Ctrl+clicks on the selected FID wave while in peak editing mode:
			if (wave != NULL && m_chartS->params().peakMode == EadMarkerMode_Edit) {
				if (info.iChosenPeak < 0)
					addMarker(vwi, m_ptClickPixmap.x());
				else if (wave->peaksChosen[info.iChosenPeak].type == MarkerType_EadPeakXY) {
					addEadPeakXYEndPoint(vwi, info.iChosenPeak);
				}
			}
		}
		else {
			bool bIgnore = false;

			// Force no dragging of markers unless in edit mode:
			if (m_chartS->params().peakMode != EadMarkerMode_Edit) {
				if (m_clickInfo.iChosenPeak >= 0)
					bIgnore = true;
			}

			if (bIgnore)
			{
				;
			}
			// Clicked on a chosen peak:
			else if (info.iChosenPeak >= 0)
			{
				m_bDragging = true;
				setCursor(Qt::SizeHorCursor);
			}
			// Clicked on a detected peak:
			else if (info.didxPossiblePeak >= 0)
			{
				vwi->choosePeakAtDidx(info.didxPossiblePeak);
			}
			// Clicked on a wave:
			else if (wave != NULL)
			{
				m_bDragging = true;
				// REFACTOR: remove m_waveDrag and use m_clickInfo instead
				//m_waveDrag = vwi->waveInfo();
				m_nDragOrigDivisionOffset = vwi->divisionOffset();
				setCursor(Qt::SizeVerCursor);
			}
			else if (rcWaveforms.contains(e->pos()))
			{
				m_bDragging = true;
				m_bSelecting = true;
				setCursor(Qt::IBeamCursor);
				updateStatus();
				update();
			}
			else
			{
				m_bDragging = false;
			}
		}
	}
	else if (e->button() == Qt::MidButton)
	{
		m_clickInfo.iChosenPeak = -1;
		m_clickInfo.iMarkerDidx = -1;
		m_clickInfo.vwi = NULL;
		m_bDragging = true;
		setCursor(Qt::SizeHorCursor);
	}

	updateStatus();
}