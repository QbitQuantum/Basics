// print title
void PrintTitle(CDrawPort *pdp)
{
  SetFont2(pdp);
  CTString strTitle;
  strTitle.PrintF(TRANS("NETRICSA v2.01 - personal version for: %s"), 
    _ppenPlayer->GetPlayerName());
  pdp->PutText( strTitle, _pixMarginI*3, _pixMarginJ-2*_fScaling2+1, _colMedium);
}