void DrawingClass::FDrawTextToCanvas(Osp::Graphics::Canvas * oncanvas, Osp::Graphics::Rectangle destdim, String text, int fontsize, int fontstyle, bool wordwrap, Osp::Graphics::Color fontcolor, Osp::Graphics::TextHorizontalAlignment halign, Osp::Graphics::TextVerticalAlignment valign) {
	Font font_;
	font_.Construct(fontstyle, fontsize);
	EnrichedText texteel;
	texteel.Construct(Dimension(destdim.width, destdim.height));
	texteel.SetHorizontalAlignment(halign);
	texteel.SetVerticalAlignment(valign);
	if (wordwrap) {
		texteel.SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
	}
	TextElement textel;
	textel.Construct(text);
	textel.SetTextColor(fontcolor);
	textel.SetFont(font_);
	texteel.Add(textel);
	oncanvas->DrawText(Point(destdim.x,destdim.y), texteel);
}