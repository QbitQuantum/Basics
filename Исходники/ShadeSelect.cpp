//---------------------------------------------------------------------------
void __fastcall TShadeSelect::DrawItem(int Index, const TRect &Rect, TOwnerDrawState State)
{
  //There seems to be a bug in TBrush, so CreateHatchBrush and CreateSolidBrush
  //are used directly to get a handle
  switch(Index)
  {
    case 0: Canvas->Brush->Handle = CreateSolidBrush(Color); break;
    case 1: Canvas->Brush->Handle = CreateHatchBrush(HS_HORIZONTAL, Color); break;
    case 2: Canvas->Brush->Handle = CreateHatchBrush(HS_VERTICAL, Color); break;
    case 3: Canvas->Brush->Handle = CreateHatchBrush(HS_FDIAGONAL, Color); break;
    case 4: Canvas->Brush->Handle = CreateHatchBrush(HS_BDIAGONAL, Color); break;
    case 5: Canvas->Brush->Handle = CreateHatchBrush(HS_CROSS, Color); break;
    case 6: Canvas->Brush->Handle = CreateHatchBrush(HS_DIAGCROSS, Color); break;
  }
  unsigned OldColor = GetBkColor(Canvas->Handle);
  SetBkColor(Canvas->Handle, clWhite);
  Canvas->FillRect(Rect);
  SetBkColor(Canvas->Handle, OldColor);
}