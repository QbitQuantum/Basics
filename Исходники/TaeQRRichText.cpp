void __fastcall TTaeQRRichText::Print(int OfsX, int OfsY){
    TFormatRange        Range;
    int                 LogX,LogY,TextLength,OldMapMode;
    bool                HasExpanded;
    TTaeRichEdit*       ARichEdit;
    Extended            Expanded;

    ARichEdit=ParentRichEdit==NULL?FRichEdit:ParentRichEdit;
    {
        register i=sizeof(TFormatRange);
        register char *c=(char *) &Range;
        while(i--) *c++=0;
    }
    Range.hdc= ParentReport->QRPrinter->Canvas->Handle;
    Range.hdcTarget= Range.hdc;
    LogX= GetDeviceCaps(Range.hdc, LOGPIXELSX);
    LogY= GetDeviceCaps(Range.hdc, LOGPIXELSY);
    Range.rc=Rect(QRPrinter->XPos(OfsX + Size->Left) * 1440 / LogX,
                  QRPrinter->YPos(OfsY + Size->Top) * 1440 / LogY,
                  QRPrinter->XPos(OfsX + Size->Width + Size->Left) * 1440 / LogX,
                  QRPrinter->YPos(OfsY + Size->Height + Size->Top) * 1440 / LogY);
    Range.rcPage=Rect(0,0,
                      QRPrinter->XSize(QRPrinter->PaperWidth) * 1440 / LogX,
                      QRPrinter->YSize(QRPrinter->PaperLength) * 1440 / LogY);

    if(PrintFinished) LastChar= 0;
    HasExpanded=false;
    Expanded=0;
    TextLength=ARichEdit->GetTextLen();
    Range.chrg.cpMax= -1;
    Range.chrg.cpMin= LastChar;
    OldMapMode= SetMapMode(Range.hdc, MM_TEXT);

    SendMessage(ARichEdit->Handle, EM_FORMATRANGE,0,0);

    LastChar= SendMessage(ARichEdit->Handle, EM_FORMATRANGE, 0, (long)&Range);
    if(LastChar<TextLength&&AutoStretch&&TextLength>0&&Parent->InheritsFrom(__classid(TQRCustomBand))){
        PrintFinished=false;
        while(LastChar<=TextLength&&((TQRCustomBand*)Parent)->CanExpand(50)){
          ((TQRCustomBand*)Parent)->ExpandBand(50,Expanded,HasExpanded);
          Range.rc.bottom = QRPrinter->YPos(OfsY+Size->Top+Size->Height+Expanded) * 1440 / LogY;
          LastChar= SendMessage(ARichEdit->Handle, EM_FORMATRANGE, 0, (long)&Range);
        }
        LastChar= SendMessage(ARichEdit->Handle, EM_FORMATRANGE, 1, (long)&Range);
        if(LastChar>=TextLength||LastChar==-1){
            LastChar=TextLength;
            PrintFinished=true;
        }
    } else {
        LastChar= SendMessage(ARichEdit->Handle, EM_FORMATRANGE, 1, (long)&Range);
        PrintFinished=true;
        inherited::Print(OfsX,OfsY);
    }
    SetMapMode(ParentReport->QRPrinter->Canvas->Handle, OldMapMode);
    if(PrintFinished)
      SendMessage(ARichEdit->Handle, EM_FORMATRANGE, 0, 0);
}