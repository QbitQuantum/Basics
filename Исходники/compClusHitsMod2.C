TPaveStats* SetStPadPos(TH1* hst,float x1,float x2,float y1,float y2, Int_t stl, Int_t col)
{
  TPaveStats* pad = GetStPad(hst);
  if (!pad) return 0;
  pad->SetX1NDC( x1 );
  pad->SetX2NDC( x2 );
  pad->SetY1NDC( y1 );
  pad->SetY2NDC( y2 );
  if (stl>=0) pad->SetFillStyle(stl);
  if (col>=0) pad->SetTextColor(col);
  pad->SetFillColor(0);
  //
  gPad->Modified();
  return pad;
}