//---------------------------------------------------------------------------
void __fastcall TFMain_11011981::lbUnitsDrawItem(
      TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
    char        *s, *pos;
    int         flags, len;
    TColor      _color;
    TListBox    *lb;
    TCanvas     *canvas;
    String      text, str1, str2;

    lb = (TListBox*)Control;
    canvas = lb->Canvas;
    SaveCanvas(canvas);

    if (Index < lb->Count)
    {
        flags = Control->DrawTextBiDiModeFlags(DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
        if (!Control->UseRightToLeftAlignment())
            Rect.Left += 2;
        else
            Rect.Right -= 2;

        text = lb->Items->Strings[Index];
        //lb->ItemHeight = canvas->TextHeight(text);
        canvas->FillRect(Rect);

        s = text.c_str();
        //*XXXXXXXX #XXX XX NAME
        pos = strrchr(s, ' ');
        len = pos - s;
        str1 = text.SubString(2, len - 1);
        str2 = text.SubString(len + 1, text.Length() - len);

        if (!State.Contains(odSelected))
            _color = TColor(0);        //Black
        else
            _color = TColor(0xBBBBBB); //LightGray
        Rect.Right = Rect.Left;
        DrawOneItem(str1, canvas, Rect, _color, flags);

        //Unit name
        //Trivial unit - red
        if (text[1] & TRIV_UNIT)
        {
            if (!State.Contains(odSelected))
                _color = TColor(0x0000B0); //Red
            else
                _color = TColor(0xBBBBBB); //LightGray
        }
        else
        {
            //User unit - green
            if (text[1] & USER_UNIT)
            {
                if (!State.Contains(odSelected))
                {
                	if (text[1] & UNEXP_UNIT)
                    	_color = TColor(0xC0C0FF); //Light Red
                    else
                    	_color = TColor(0x00B000); //Green
                }
                else
                    _color = TColor(0xBBBBBB); //LightGray
            }
            //From knowledge base - blue
            else
            {
                if (!State.Contains(odSelected))
                    _color = TColor(0xC08000); //Blue
                else
                    _color = TColor(0xBBBBBB); //LightGray
            }
        }
        DrawOneItem(str2, canvas, Rect, _color, flags);
    }
    RestoreCanvas(canvas);
}