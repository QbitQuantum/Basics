void __fastcall TfrmRetrievalJobList::sgJobsDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State) {
    LCDbCryoJob * job;
    TColor background = clWindow;
    if (0 == ARow)
        job = NULL;
    else
        job = (LCDbCryoJob *)sgJobs->Objects[0][ARow];
    if (NULL == job) {
        if (0 == ARow) {
            background = clBtnFace; // header row
        } else {
            background = RETRIEVAL_ASSISTANT_ERROR_COLOUR; // error
        }
    } else {
        switch (job->getStatus()) {
        case LCDbCryoJob::Status::NEW_JOB:
            background = RETRIEVAL_ASSISTANT_JOB_NEW_COLOUR; break;
        case LCDbCryoJob::Status::INPROGRESS:
            background = RETRIEVAL_ASSISTANT_JOB_INPROGRESS_COLOUR; break;
        case LCDbCryoJob::Status::DONE:
            background = RETRIEVAL_ASSISTANT_JOB_COMPLETED_COLOUR; break;
        case LCDbCryoJob::Status::DELETED:
            background = RETRIEVAL_ASSISTANT_JOB_DELETED_COLOUR; break;
        default:
            background = RETRIEVAL_ASSISTANT_ERROR_COLOUR;
        }
    }
    TCanvas * cnv = sgJobs->Canvas;
	cnv->Brush->Color = background;
	cnv->FillRect(Rect);
    if (State.Contains(gdSelected)) {
        TFontStyles oldFontStyle = cnv->Font->Style;
        TPenStyle oldPenStyle = cnv->Pen->Style;
        cnv->Pen->Style = psDot;
        cnv->Rectangle(Rect.Left+1, Rect.Top+1, Rect.Right-1, Rect.Bottom-1);
        cnv->Font->Style = TFontStyles() << fsBold; // << fsItalic;
    	cnv->TextOut(Rect.Left+5, Rect.Top+5, sgJobs->Cells[ACol][ARow]);
        cnv->Pen->Style     = oldPenStyle;
        cnv->Font->Style    = oldFontStyle;
	} else {
        cnv->TextOut(Rect.Left+5, Rect.Top+5, sgJobs->Cells[ACol][ARow]);
    }
}