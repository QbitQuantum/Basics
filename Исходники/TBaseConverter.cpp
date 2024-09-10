void __fastcall TfrmBaseConverter::ctlSplitterPaint(TObject *Sender)
{
    TCanvas *oCanvas;
    TRect   oGrabber;

    oCanvas  = this->ctlSplitter->Canvas;
    oGrabber = oCanvas->ClipRect;

    //---------------------------------------------------------------------------
    // Background
    oCanvas->Pen->Color   = (TColor)DEFAULT_SPLITTER_BORDER_COLOR;
    oCanvas->Brush->Color = (TColor)DEFAULT_SPLITTER_BACK_COLOR;
    oCanvas->RoundRect(oGrabber.Left, oGrabber.Top, oGrabber.Right, oGrabber.Bottom, 2, 2);

    // Middle grabber
    oGrabber         = oCanvas->ClipRect;
    oGrabber.Right  -= 1;
    oGrabber.Top     = (int)(oCanvas->ClipRect.Height() / 2.5);
    oGrabber.Bottom  = oGrabber.Bottom - oGrabber.Top;

    oCanvas->Pen->Color = (TColor)DEFAULT_SPLITTER_BORDER_COLOR;

    for (int iItem = oGrabber.Top; iItem < oGrabber.Bottom;)
    {
        oCanvas->MoveTo(oGrabber.Left, iItem);
        oCanvas->LineTo(oGrabber.Right, iItem);

        iItem += 3;
    }

    return;
}