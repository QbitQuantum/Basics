//
/// Paint the text gadget by painting gadget borders, & then painting text in
/// the InnerRect. Empty or 0 text blanks the gadget.
//
/// Calls TGadget::PaintBorder to paint the border. Calls TGadget::GetInnerRect to
/// calculate the area of the text gadget's rectangle. If the text is left-aligned,
/// Paint calls dc.GetTextExtent to compute the width and height of a line of the
/// text. To set the background color, Paint calls dc.GetSysColor and sets the
/// default background color to face shading (COLOR_BTNFACE). To set the button text
/// color, Paint calls dc.SetTextColor and sets the default button text color to
/// COLOR_BTNTEXT. To draw the text, Paint calls dc.ExtTextOut and passes the
/// parameters ETO_CLIPPED (so the text is clipped to fit the rectangle) and
/// ETO_OPAQUE (so the rectangle is filled with the current background color).
//
void
TTextGadget::Paint(TDC& dc)
{
  PaintBorder(dc);

  TRect  innerRect;
  GetInnerRect(innerRect);

  if (!Font)
    dc.SelectObject(GetGadgetWindow()->GetFont());
  else
    dc.SelectObject(*Font);

  TColor textColor = GetEnabledColor();
  if(!GetEnabled())
    textColor = TColor::Sys3dHilight;

  bool transparent = GetGadgetWindow()->GetFlatStyle() & TGadgetWindow::FlatXPTheme;
  if(!Text){
    if (!transparent)
    {
    TColor color = dc.SetBkColor(TColor::Sys3dFace);
    dc.ExtTextOut(0,0, ETO_OPAQUE, &innerRect, _T(""), 0);
    dc.SetBkColor(color);
  }
  }
  else
  {
    // Create a UI Face object for this button & let it paint the button face
    //
    uint align[] = {DT_LEFT, DT_CENTER, DT_RIGHT};
    uint format =  DT_SINGLELINE | DT_VCENTER | align[Align];
            TUIFace face(innerRect, Text, BkgndColor, format);

     TPoint  dstPt(innerRect.TopLeft());

      dc.SetBkColor(BkgndColor);

     TColor oldTxColor  = dc.SetTextColor(textColor);
    if (!GetEnabled())
      face.Paint(dc, dstPt, TUIFace::Disabled, false, !transparent);
    else
      face.Paint(dc, dstPt, TUIFace::Normal, false, !transparent);
    dc.SetTextColor(oldTxColor);
  }
  dc.RestoreFont();
}