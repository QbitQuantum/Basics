/*-----------------------------------------------------------------*/
void __fastcall TOverviewForm::SBPrintClick(TObject *Sender)
{
    // Ausdrucken der Geschichte...
    TCursor savecursor = Cursor;
    Cursor = crHourGlass;

    Printer()->Title = (String)APP_TITLE+" - "+ExtractFileName(frm->filename);
    Printer()->BeginDoc();

    CalcPrintDimensions();

    int mx = min(maxi, frm->kette.count());
    int my = min(maxj, frm->schuesse.count());

    TCanvas* canvas = Printer()->Canvas;

    if (frm->GewebeNormal->Checked) {
        for (int i=frm->kette.a; i<frm->kette.a+mx; i++)
            for (int j=frm->schuesse.a; j<frm->schuesse.a+my; j++) {
                int x;
                if (frm->righttoleft) x = (mx+1)*gw - (i-frm->kette.a+1)*gw;
                else x = (i-frm->kette.a)*gw;
                int y = (my+1)*gh - (j-frm->schuesse.a+1)*gh;
                if (frm->gewebe.feld.Get(i, j)>0) {
                    canvas->Brush->Style = bsSolid;
                    canvas->Pen->Color = GetRangeColor(frm->gewebe.feld.Get(i, j));
                    canvas->Brush->Color = GetRangeColor(frm->gewebe.feld.Get(i, j));
                    canvas->Rectangle (mleft+x, mtop+y, mleft+x+gw, mtop+y+gh);
                }
                if (grid) {
                    canvas->Pen->Color = clBlack;
                    canvas->MoveTo (mleft+x, mtop+y);
                    canvas->LineTo (mleft+x, mtop+y+gh);
                    canvas->LineTo (mleft+x+gw, mtop+y+gh);
                    canvas->LineTo (mleft+x+gw, mtop+y);
                    canvas->LineTo (mleft+x, mtop+y);
                }
            }
    } else if (frm->GewebeFarbeffekt->Checked || frm->GewebeSimulation->Checked) {
        // Nach Farben getrennt malen, schneller...
        for (int i=frm->kette.a; i<frm->kette.a+mx; i++)
            for (int j=frm->schuesse.a; j<frm->schuesse.a+my; j++) {
                bool drawhebung = frm->gewebe.feld.Get(i,j)>0;
                if (frm->sinkingshed) drawhebung = !drawhebung;
                canvas->Brush->Style = bsSolid;
                if (drawhebung) {
                    canvas->Brush->Color = GETPALCOL(frm->kettfarben.feld.Get(i));
                    canvas->Pen->Color = GETPALCOL(frm->kettfarben.feld.Get(i));
                } else {
                    canvas->Brush->Color = GETPALCOL(frm->schussfarben.feld.Get(j));
                    canvas->Pen->Color = GETPALCOL(frm->schussfarben.feld.Get(j));
                }
                int x;
                if (frm->righttoleft) x = pwidth - (i-frm->kette.a+1)*gw;
                else x = (i-frm->kette.a)*gw;
                int y = (my+1)*gh - (j-frm->schuesse.a+1)*gh;
                canvas->Rectangle (mleft+x, mtop+y, mleft+x+gw, mtop+y+gh);
                if (grid) {
                    canvas->Pen->Color = clBlack;
                    canvas->MoveTo (mleft+x, mtop+y);
                    canvas->LineTo (mleft+x, mtop+y+gh);
                    canvas->LineTo (mleft+x+gw, mtop+y+gh);
                    canvas->LineTo (mleft+x+gw, mtop+y);
                    canvas->LineTo (mleft+x, mtop+y);
                }
            }
    }

    Printer()->EndDoc();
    Cursor = savecursor;
    ::MessageBeep (-1);
}