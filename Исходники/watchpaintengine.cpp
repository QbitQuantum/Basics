void WatchPaintEngine::updateState(const QPaintEngineState &state)
{
	const QPaintEngine::DirtyFlags flags = state.state();

	TRACE(qDebug() << __func__ << flags);

	if (flags & QPaintEngine::DirtyTransform)
	{
		TRACE(qDebug() << " " << "DirtyTransform" << state.transform());
		_transform = state.transform();
		_painter.setTransform(_transform);
	}

	if (flags & QPaintEngine::DirtyBackground)
	{
		_painter.setBackground(state.backgroundBrush());
	}

	if (flags & QPaintEngine::DirtyBackgroundMode)
	{
		_painter.setBackgroundMode(state.backgroundMode());
	}

	if (flags & QPaintEngine::DirtyBrush)
	{
		QBrush brush = state.brush();
		_hasBrush = brush.style() != Qt::NoBrush;
		_painter.setBrush(brush);
	}
	if (flags & QPaintEngine::DirtyBrushOrigin)
	{
		_painter.setBrushOrigin(state.brushOrigin());
	}
	if (flags & QPaintEngine::DirtyClipEnabled)
	{
		TRACE(qDebug() << " " << "DirtyClipEnabled" << state.isClipEnabled());
		_clipEnabled = state.isClipEnabled();
		_painter.setClipping(_clipEnabled);
	}
	if (flags & QPaintEngine::DirtyClipPath)
	{
		TRACE(qDebug() << " " << "DirtyClipPath" << state.clipPath().boundingRect());
		QRegion region = state.clipPath().boundingRect().toAlignedRect();
		updateClipRegion(region, state.clipOperation());
		_painter.setClipPath(state.clipPath(), state.clipOperation());
	}
	if (flags & QPaintEngine::DirtyClipRegion)
	{
		TRACE(qDebug() << " " << "DirtyClipRegion" << state.clipRegion());
		updateClipRegion(state.clipRegion(), state.clipOperation());
		_painter.setClipRegion(state.clipRegion(), state.clipOperation());
	}
	if (flags & QPaintEngine::DirtyCompositionMode)
	{
		TRACE(qDebug() << " " << "DirtyCompositionMode" << state.compositionMode());
		_painter.setCompositionMode(state.compositionMode());
	}
	if (flags & QPaintEngine::DirtyFont)
	{
		_painter.setFont(state.font());
	}
	if (flags & QPaintEngine::DirtyHints)
	{
		_painter.setRenderHints(state.renderHints());
	}
	if (flags & QPaintEngine::DirtyPen)
	{
		QPen pen = state.pen();
		_hasPen = pen.style() != Qt::NoPen;
		_penWidth = pen.widthF();
		_painter.setPen(pen);
	}

	TRACE(qDebug() << __func__ << "end");
}