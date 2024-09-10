//---------------------------------------------------------------------------
void __fastcall TDialogZeroConf::PaintBoxIPPaint(TObject *Sender)
{
  String S = IP.ToString();
  TCanvas *C = PaintBoxIP->Canvas;
  C->Brush->Color = RGB(51, 51, 51);
  C->FillRect(Bounds(0, 0, 32767, 32767));
  C->Font->Color = clLime;
  C->Font->Size = 40;
  C->TextOut(PaintBoxIP->Width / 2 - C->TextWidth(S) / 2, 5, S);
}