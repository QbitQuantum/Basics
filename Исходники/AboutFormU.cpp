void __fastcall TAboutForm::FormCreate(TObject *Sender)
{
	HRGN rgn = CreateRoundRectRgn(0, 0, Width, Height, 20, 20);
    SetWindowRgn(Handle, rgn, true);

//    DoubleBuffered = true;

    char str[256-32];
    for (int i=32; i<256; i++)
    	str[i-32] = i;
//    str[256-32] = 0; // -?

    b = new Graphics::TBitmap;
    b->Width = PB->Width;
    b->Height = PB->Height;
    b->PixelFormat = pf24bit;

	CANVAS = b->Canvas;
    CANVAS->Brush->Color = Color;
    CANVAS->Brush->Style = bsSolid;
    CANVAS->Font = PB->Font;

    TH = CANVAS->TextHeight(str)+DELTA;

    Yn = PB->Height;
    Index = 0;

    CANVAS->Brush->Style = bsClear;
    CANVAS->Pen->Color = Color;
}