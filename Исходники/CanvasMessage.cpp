status_t
CanvasMessage::ReadViewState(BView& view, ::pattern& pattern)
{
	bool subPixelPrecise;
	float penSize, miterLimit;
	drawing_mode drawingMode;
	source_alpha sourceAlpha;
	alpha_function alphaFunction;
	cap_mode capMode;
	join_mode joinMode;
	rgb_color highColor, lowColor;

	Read(penSize);
	Read(subPixelPrecise);
	Read(drawingMode);
	Read(sourceAlpha);
	Read(alphaFunction);
	Read(pattern);
	Read(capMode);
	Read(joinMode);
	Read(miterLimit);
	Read(highColor);
	status_t result = Read(lowColor);
	if (result != B_OK)
		return result;

	uint32 flags = view.Flags() & ~B_SUBPIXEL_PRECISE;
	view.SetFlags(flags | (subPixelPrecise ? B_SUBPIXEL_PRECISE : 0));
	view.SetPenSize(penSize);
	view.SetDrawingMode(drawingMode);
	view.SetBlendingMode(sourceAlpha, alphaFunction);
	view.SetLineMode(capMode, joinMode, miterLimit);
	view.SetHighColor(highColor);
	view.SetLowColor(lowColor);
	return B_OK;
}