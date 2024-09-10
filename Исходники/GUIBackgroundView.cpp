void
TGUIBackgroundView::Paint()
{
    TCanvas *canvas = GetCanvas();
    canvas->Pen->Color = TGUIView::GetElementColor( fbBackground ).cl;
    canvas->Brush->Color = canvas->Pen->Color;
    canvas->FillRect( viewTRect );
}