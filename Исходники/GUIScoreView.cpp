void
TGUIScoreView::InvalidateBuffer()
{
    TCanvas *canvas = buffer->Canvas;
    canvas->Font->Height = viewTRect.Height() / 2;

    AnsiString  successTrialsString = IntToStr( successTrials ),
                totalTrialsString = IntToStr( totalTrials );

    int successTrialsWidth = canvas->TextWidth( successTrialsString ),
        totalTrialsWidth = canvas->TextWidth( totalTrialsString ),
        maxWidth = MAX( successTrialsWidth, totalTrialsWidth );

    buffer->Height = viewTRect.Height();
    buffer->Width = maxWidth;

    canvas->FillRect( TRect( 0, 0, buffer->Width, buffer->Height ) );
    canvas->TextOut( maxWidth - successTrialsWidth, 0, successTrialsString );
    canvas->TextOut( maxWidth - totalTrialsWidth, buffer->Height / 2, totalTrialsString );

    TGUIView::InvalidateRect( TRect( viewTRect.Left,
                                     viewTRect.Top,
                                     viewTRect.Left + buffer->Width,
                                     viewTRect.Top + buffer->Height ) );
}