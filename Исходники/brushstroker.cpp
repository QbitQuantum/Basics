void BrushStroker::end()
{
	if (_smoothed)
	{
		lineTo(_dataEnd);
	}
}