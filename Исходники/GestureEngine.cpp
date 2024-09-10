bool CGestures::IsGesturesEnabled()
{
	if (!_isTabletPC || !_isGestures)
		return false;
	// Финт ушами - считаем, что событие от мыши, если мышиный курсор
	// видим на экране. Если НЕ видим - то событие от тачскрина. Актуально
	// для того, чтобы различать правый клик от мышки и от тачскрина.
	CURSORINFO ci = {sizeof(ci)};
	if (!GetCursorInfo(&ci))
		return false;
	// 0 - курсор скрыт, а 2 - похоже недокументировано (тачскрин)
	if (ci.flags == 0 || ci.flags == 2)
		return true;
	_ASSERTE(ci.flags == CURSOR_SHOWING);
	return false;
}