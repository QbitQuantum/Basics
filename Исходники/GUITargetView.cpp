void
TGUITargetView::DrawBlinkingGoal()
{
    goalState = blinkActive;
    // Draw a "blinking" goal into the goalBuffer.
    if( goalBuffer == NULL )
        return;

    int width = viewTRect.Width(),
        height = viewTRect.Height();
    goalBuffer->Width = width;
    goalBuffer->Height = height;
    TCanvas *canvas = goalBuffer->Canvas;
    int penWidth = TGUIView::GetElementWidth( targetBorderBlinking );
    canvas->Pen->Width = penWidth;
    canvas->Pen->Color = TGUIView::GetElementColor( targetBorderBlinking ).cl;
    canvas->Brush->Color = TGUIView::GetElementColor( targetFillBlinking ).cl;
    canvas->Rectangle( penWidth / 2, penWidth / 2, width - penWidth / 2 + 1, height - penWidth / 2 + 1 );
    DrawLabel( targetTextBlinking );
}