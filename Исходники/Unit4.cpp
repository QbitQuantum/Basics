void __fastcall TForm4::PaintBox4Paint(TObject *Sender)
{
        TCanvas *FormCanvas = ((TPaintBox*)Sender)->Canvas;
        int CenterX, CenterY;
        double deg;
	TSize stSize;

	stSize.cx = 0;
	if (ListBox1->ItemIndex < 0) ListBox1->ItemIndex = 0;
	//Пишет
        FormCanvas->Font->Name = "GOST type A";
	FormCanvas->Font->Size = 50;
	FormCanvas->Font->Style = TFontStyles() << fsItalic;
	FormCanvas->TextOut(70, 30, ListBox1->Items->operator [](ListBox1->ItemIndex));

        //Рисует
        //deg = 60*M_PI/180;
        FormCanvas->Pen->Width = 3;
        FormCanvas->MoveTo(20, 50);
	FormCanvas->LineTo(45, 96);
	FormCanvas->LineTo(80, 23);
	//Дополнительная верхняя линия которая зависит от размера текста
	stSize = FormCanvas->TextExtent(ListBox1->Items->operator [](ListBox1->ItemIndex));
	if ( ListBox1->Items->operator [](ListBox1->ItemIndex).Length())
	{
		FormCanvas->LineTo(90 + stSize.cx, 23);
        }
        //Дополнительные значки зависящие от панелей
        if (Panel2->BevelOuter == bvLowered)
        {
                FormCanvas->MoveTo(20, 50);
                FormCanvas->LineTo(67, 50);
        }
        if (Panel3->BevelOuter == bvLowered)
        {
                FormCanvas->Ellipse(30, 48, 60, 78);
        }
        //Полка
        if ((Panel5->BevelOuter == bvLowered) || (Panel6->BevelOuter == bvLowered))
        {
                FormCanvas->MoveTo(80 + stSize.cx, 96);
                FormCanvas->LineTo(30, 96);
                FormCanvas->LineTo(5, 130);
        }
        if (Panel6->BevelOuter == bvLowered)
        {
                FormCanvas->MoveTo(5, 130);
                FormCanvas->LineTo(13, 110);
                FormCanvas->MoveTo(5, 130);
                FormCanvas->LineTo(22, 116);
        }
        //По контуру
        if (Panel7->BevelOuter == bvLowered)
        {
                FormCanvas->MoveTo(80, 23);
                FormCanvas->Brush->Style = bsClear;
                FormCanvas->Ellipse(80-15, 23 - 15, 80+15, 23+15);
        }
}