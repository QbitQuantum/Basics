//
/// Paint Text
//
void
TButtonTextGadget::PaintText(TDC& dc, TRect& rect, const tstring& text)
{
  dc.SelectObject(GetFont());

  TColor textColor = TColor::SysBtnText;
  if(!GetEnabled())
    textColor = TColor::Sys3dHilight;
  else if((GetGadgetWindow()->GetFlatStyle()&TGadgetWindow::FlatHotText) && IsHaveMouse())
     textColor = TColor::LtBlue;

   TColor oldTxColor  = dc.SetTextColor(textColor);

  uint format =  DT_SINGLELINE|DT_NOCLIP|DT_END_ELLIPSIS;
  switch(Align){
    case aLeft:
      format |= DT_LEFT;
      break;
    case aRight:
      format |= DT_RIGHT;
      break;
    case aCenter:
      format |= DT_CENTER;
      break;
  }
  switch(LayoutStyle){
    case lTextLeft:
    case lTextRight:
      format |= DT_VCENTER;
      break;
    case lTextTop:
      format |= DT_VCENTER;//DT_BOTTOM;
      break;
    case lTextBottom:
      format |= DT_VCENTER;//DT_TOP;
      break;
  }

  // Create a UI Face object for this button & let it paint the button face
  //
  TPoint  dstPt(rect.TopLeft());

  if (GetButtonState() == Down && GetEnabled() &&
      GetGadgetWindow()->GetFlatStyle()&TGadgetWindow::FlatStandard)
  {
    if(IsHaveMouse())
    {
      if(IsPressed())
      {
        const int dx = (format & DT_CENTER) ? 2 : 1;
        const int dy = (format & DT_VCENTER) ? 2 : 1;
        rect.Offset(dx, dy);
      }
      TUIFace(rect, text, TColor::Sys3dFace,format).Paint(dc, dstPt,
                TUIFace::Normal, true, true);
    }
    else
    {
      TUIFace face(rect, text, TColor::Sys3dFace,format);
      if(GetGadgetWindow()->GadgetGetCaptured()==this)
        face.Paint(dc, dstPt, TUIFace::Normal, true);
      else
        face.Paint(dc, dstPt, TUIFace::Down, IsPressed(), false);
    }
  }
  else
  {
    TUIFace face(rect, text, TColor::Sys3dFace,format);
    if (!GetEnabled())
      face.Paint(dc, dstPt, TUIFace::Disabled, false, false);
    else if (GetButtonState() == Indeterminate)
      face.Paint(dc, dstPt, TUIFace::Indeterm, IsPressed(), false);
    else if (GetButtonState() == Down) // Down and not flat
      face.Paint(dc, dstPt, TUIFace::Down, IsPressed(), false);
    else
      face.Paint(dc, dstPt, TUIFace::Normal, IsPressed(), false);
  }

  dc.SetTextColor(oldTxColor);

  dc.RestoreFont();
}