void
LineChartRenderer::Render(BView* view, BRect updateRect)
{
	if (!updateRect.IsValid() || updateRect.left > fFrame.right
		|| fFrame.left > updateRect.right) {
		return;
	}

	if (fDomain.min >= fDomain.max || fRange.min >= fRange.max)
		return;

	if (!_UpdateSamples())
		return;

	// get the range to draw (draw one more sample on each side)
	int32 left = (int32)fFrame.left;
	int32 first = (int32)updateRect.left - left - 1;
	int32 last = (int32)updateRect.right - left + 1;
	if (first < 0)
		first = 0;
	if (last > fFrame.IntegerWidth())
		last = fFrame.IntegerWidth();
	if (first > last)
		return;

	double minRange = fRange.min;
	double sampleRange = fRange.max - minRange;
	if (sampleRange == 0) {
		minRange = fRange.min - 0.5;
		sampleRange = 1;
	}
	double scale = (double)fFrame.IntegerHeight() / sampleRange;

	// draw
	view->SetLineMode(B_ROUND_CAP, B_ROUND_JOIN);
	for (int32 i = 0; DataSourceInfo* info = fDataSources.ItemAt(i); i++) {

		float bottom = fFrame.bottom;
		BShape shape;
		shape.MoveTo(BPoint(left + first,
			bottom - ((info->samples[first] - minRange) * scale)));

		for (int32 i = first; i <= last; i++) {
			shape.LineTo(BPoint(float(left + i),
				float(bottom - ((info->samples[i] - minRange) * scale))));
		}
		view->SetHighColor(info->config.Color());
		view->MovePenTo(B_ORIGIN);
		view->StrokeShape(&shape);
	}
}