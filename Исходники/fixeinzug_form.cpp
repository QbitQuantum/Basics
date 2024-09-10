/*-----------------------------------------------------------------*/
void __fastcall TFixeinzugForm::_DrawCursor(TColor _col)
{
    TCanvas* pCanvas = pbFixeinzug->Canvas;
    pCanvas->Pen->Color = _col;
    int x, y;
    if (frm->righttoleft) x = (maxx-1-cx)*dx;
    else x = cx*dx;
    if (frm->toptobottom) y = cy*dy;
    else y = (maxy-1-cy)*dy;
    pCanvas->MoveTo (x, y);
    pCanvas->LineTo (x+dx, y);
    pCanvas->LineTo (x+dx, y+dy);
    pCanvas->LineTo (x, y+dy);
    pCanvas->LineTo (x, y);
}