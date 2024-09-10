void MapBG::StatePerformed(dword state, const String& param)
{
	if (_currLevel < 0 || _currLevel >= _levels.GetCount())
		return;

	MipMapLevel& level = _levels[_currLevel];
	Rect pageRect = GetPageRect();

	if (_recalc || !_virtPage.Contains(GetPageRect()))
	{
		_virtPage = pageRect.Inflated(level.GetBlockSize() * _cachePageInitSize);
		_recalc = true;
	}

	Rect currVirtualPage = _virtPage.Inflated(level.GetBlockSize() * _cachePageSize);

	if (!_recalc)
		return;

	for (int i = 0; i < level.GetMipMaps().GetCount(); ++i)
	{
		Point pi = level.GetMipMaps().GetKey(i);
		Rect itemRect(pi, level.GetBlockSize());

		if (!level.GetMipMaps()[i])
			continue;

		if (currVirtualPage.Intersects(itemRect))
		{
			level.GetMipMaps()[i]->Prepare(
				AppendFileName(_mapDir, NFormat("%d-%d-%d.png", _currLevel, pi.x, pi.y)),
				level.GetBlockSize()
			);
		}
		else
			level.GetMipMaps()[i]->Release();
	}

	_recalc = false;
}