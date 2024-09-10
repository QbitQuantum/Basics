void FullColorBrushTool::leftButtonDown(const TPointD &pos, const TMouseEvent &e)
{
	m_brushPos = m_mousePos = pos;

	Viewer *viewer = getViewer();
	if (!viewer)
		return;

	TRasterImageP ri = (TRasterImageP)getImage(true);
	if (!ri)
		ri = (TRasterImageP)touchImage();

	if (!ri)
		return;

	TRasterP ras = ri->getRaster();
	TDimension dim = ras->getSize();

	if (!(m_workRaster && m_backUpRas))
		setWorkAndBackupImages();

	m_workRaster->lock();

	double maxThick = m_thickness.getValue().second;
	double thickness = m_pressure.getValue() ? computeThickness(e.m_pressure, m_thickness) : maxThick;
	double opacity = (m_pressure.getValue() ? computeThickness(e.m_pressure, m_opacity) : m_opacity.getValue().second) * 0.01;
	TPointD rasCenter = TPointD(dim.lx * 0.5, dim.ly * 0.5);
	TThickPoint point(pos + rasCenter, thickness);
	TPointD halfThick(maxThick * 0.5, maxThick * 0.5);
	TRectD invalidateRect(pos - halfThick, pos + halfThick);

	m_points.clear();
	m_points.push_back(point);

	m_tileSet = new TTileSetFullColor(ras->getSize());
	m_tileSaver = new TTileSaverFullColor(ras, m_tileSet);
	double hardness = m_hardness.getValue() * 0.01;

	m_brush = new BluredBrush(m_workRaster, maxThick, m_brushPad, hardness == 1.0);
	m_strokeRect = m_brush->getBoundFromPoints(m_points);
	updateWorkAndBackupRasters(m_strokeRect);
	m_tileSaver->save(m_strokeRect);
	m_brush->addPoint(point, opacity);
	m_brush->updateDrawing(ras, m_backUpRas, m_currentColor, m_strokeRect, m_opacity.getValue().second * 0.01);
	m_oldOpacity = opacity;
	m_lastRect = m_strokeRect;

	invalidate(invalidateRect.enlarge(2));
}