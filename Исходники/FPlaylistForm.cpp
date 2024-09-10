 result DrawElement(const Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, CustomListItemStatus itemStatus)
 {
     result r = E_SUCCESS;

     Canvas* pCanvas = const_cast<Canvas*>(&canvas);

     Font textfont;
     textfont.Construct(Osp::Graphics::FONT_STYLE_PLAIN, 28);

     EnrichedText texteel;
     texteel.Construct(Dimension(rect.width, rect.height));
   	 texteel.SetHorizontalAlignment(Osp::Graphics::TEXT_ALIGNMENT_LEFT);
     texteel.SetVerticalAlignment(Osp::Graphics::TEXT_ALIGNMENT_MIDDLE);
     texteel.SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
     texteel.SetTextAbbreviationEnabled(true);
     TextElement textelcol;
     textelcol.Construct(text);
     textelcol.SetTextColor(Color::COLOR_WHITE);
     textelcol.SetFont(textfont);
     texteel.Add(textelcol);
     pCanvas->DrawText(Point(0,0), texteel);

     return r;
 }