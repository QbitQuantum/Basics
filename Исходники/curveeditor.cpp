int ATOM_CurveEditor::keyValueToCoord (float value) const
{
	unsigned canvasSize = (getClientRect().size.h > getCanvasSize().h) ? getClientRect().size.h : getCanvasSize().h;
	return canvasSize * _originValueAxis - value * _valueAxisUnitResolution - getScrollValue().y;
}