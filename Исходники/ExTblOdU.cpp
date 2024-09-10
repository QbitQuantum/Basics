//---------------------------------------------------------------------------
void __fastcall TForm1::OvcTCString1OwnerDraw(TObject *Sender,
  TCanvas *TableCanvas, const TRect &CellRect, int RowNum, int ColNum,
  const TOvcCellAttributes &CellAttr, Pointer Data, bool &DoneIt)
{
  bool F;
  TRect R;
  TCanvas* C;
  char Buf[255];

  DoneIt = True;
  R = CellRect;
  C = TableCanvas;

  // paint background
  C->Brush->Style = bsClear;
  C->Pen->Color = clBtnFace;
  C->Rectangle(R.Left, R.Top, R.Right, R.Bottom);

  // draw button
  F = (RowNum == TBL->ActiveRow) && (ColNum == TBL->ActiveCol);
  DrawButtonFace(C, R, 1, bsNew, true, F, F);

  // draw data
  if ((RowNum % 2) == 1)
    C->Font->Color = clRed;
  else
    C->Font->Color = clBlack;
  sprintf(Buf, "%d:%d", RowNum, ColNum);
  DrawText(C->Handle, Buf, StrLen(Buf),
    (RECT*)&R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}