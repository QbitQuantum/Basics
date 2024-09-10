void __fastcall TClipMaker::ClipPaint(TObject *Sender)
{
	TMxPanel* P 		= dynamic_cast<TMxPanel*>(Sender); VERIFY(P);
    TCanvas* canvas 	= P->Canvas;
    canvas->Font->Name 	= "MS Sans Serif";
    canvas->Font->Style	= TFontStyles();
    canvas->Font->Color = clBlack;
    canvas->Pen->Color 	= clBlack;
    canvas->Pen->Style	= psSolid;
    canvas->Brush->Style= bsSolid;
    for (UIClipIt it=clips.begin(); it!=clips.end(); it++){
        TRect R 		= TRect((*it)->PLeft(), 1, (*it)->PRight()-1, paClips->Height);
        canvas->Pen->Width	= 1;
        canvas->Brush->Color= (*it==sel_clip)?(drag_obj==P->Tag?CLIP_ACTIVE_DRAG_COLOR:CLIP_ACTIVE_COLOR):CLIP_INACTIVE_COLOR;
        canvas->Rectangle	(R);
        R.Top				+= 1;
        R.Bottom			-= 1;
        R.Left				+= 1;
        R.Right				-= 1;
        canvas->TextRect	(R,R.Left,R.Top,*(*it)->name);
    }
}